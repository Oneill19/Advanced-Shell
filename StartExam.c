#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 256

void print_exam(char *path, char *exam_name);   // print the exam
int* get_ans(int size); // get the student answers
void create_file(char *path, int* ans, int q_num);  // create the student solve file
int get_q_num(char *path, char *exam_name); // build and return the number of question in the exam
void print_error(char *msg);    // print an error message and exit the program

// main function
int main(int argc, char *argv[])
{
    int i, j, q_num, q_indx, q_ans , *ans;
    char input[MAX], path[MAX];
    sprintf(path, "%s.txt", argv[1]);   // create the file name of the exam
    q_num = get_q_num(path, argv[1]);   // get the number of questions in the exam
    print_exam(path, argv[1]);  // print the exam
    printf("Insert number of Question and sol:\n");
    ans = get_ans(q_num);   // get the student answers
    sprintf(path, "%s_%s.txt", argv[2], argv[1]);   // create the file name of the student solve
    create_file(path, ans, q_num);  // create the student solve file
    free(ans);
    return 0;
}

// print the exam
void print_exam(char *path, char *exam_name)
{
    int fd, rbytes;
    char buff[MAX];
    fd = open(path, O_RDONLY, 0); // open the exam file
    if (fd == -1)
    {
    	fprintf(stderr, "%s not found!\n", exam_name);
    	exit(1);
    }
    while ((rbytes = read(fd, buff, sizeof(buff) - 1)) != 0)    // print the content of the file
    {
        if (rbytes == -1)
            print_error("Read file error");
        buff[rbytes] = '\0';
        printf("%s", buff);
    }
    close(fd);
}

// get the student answers
int* get_ans(int size)
{
	int i, q_indx, q_ans;
	int *ans = (int*)malloc(size * sizeof(int));    // allocate memory for the answers array
	if (ans == NULL)
		print_error("Error allocating memory!");
	for (i = 0; i < size; i++)  // insert the students answers to the array
	{
		scanf("%d %d", &q_indx, &q_ans);
		ans[q_indx - 1] = q_ans;
	}
	return ans;
}

// create the student solve file
void create_file(char *path, int* ans, int q_num)
{
    int i, fd, wbytes;
    char buff[MAX];
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        print_error("Open file error!");
    for (i = 0; i < q_num; i++) // enter the student answers by order
    {
        sprintf(buff, "%d\n", ans[i]);
        wbytes =  write(fd, buff, strlen(buff));
        if (wbytes == -1 | wbytes < strlen(buff))
            print_error("Write file error!");
    }
    close(fd);
}

// build and return the number of question in the exam
int get_q_num(char *path, char *exam_name)
{
    int fd, rbytes, q_num = 0;
    char buff[1];
    fd = open(path,O_RDONLY, 0);    // open the exam file
    if (fd == -1)
    {
    	fprintf(stderr, "%s not found!\n", exam_name);
    	exit(1);
    }
    while (1)   // skip the first line in the exam
    {
        rbytes = read(fd, buff, 1);
        if (rbytes == -1)
            print_error("Read file error!");
        if (buff[0] == '\n')
            break;
    }
    while(1)    // build the number
    {
        rbytes = read(fd, buff, 1); // read one char
		if (rbytes == -1)
            print_error("Read file error!");
        if (buff[0] == '\n')    // if finished to build the number
            break;
        q_num *= 10;
        q_num += buff[0] - 48;
    }
    close(fd);  // close the file
    return q_num;
}

// print an error message and exit the program
void print_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
