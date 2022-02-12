#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 256

int get_q_num(char *path, char *exam_name); // build and return the number of question in the exam
void write_file(char *path, int q_num); // create the exam solve file
void print_error(char *msg);    // print an error message and exit the program

// main function
int main(int argc, char *argv[])
{
    int i, fd_w, wbytes, q_num, input;
    char buff[MAX], path[MAX];
    sprintf(path, "%s.txt", argv[1]);   // create the file name of the exam
    q_num = get_q_num(path, argv[1]);   // get the number of questions in the exam
    sprintf(path, "Sol_%s.txt", argv[1]);   // // create the file name of the solve of the exam
    write_file(path, q_num);    // create the exam solve file
    return 0;
}

// build and return the number of question in the exam
int get_q_num(char* path, char *exam_name)
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
    close(fd);
    return q_num;
}

// create the exam solve file
void write_file(char *path, int q_num)
{
    int i, fd, wbytes, input;
    char buff[MAX];
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        print_error("Open file error!");
    for (i = 0; i < q_num; i++) // insert the answer number to the file
    {
        printf("Insert True Sol for Question %d:\n", i + 1);
        scanf("%d", &input);
        sprintf(buff, "%d\n", input);
        wbytes = write(fd, buff, strlen(buff));
        if (wbytes == -1 || wbytes < strlen(buff))
            print_error("Write file error!");
    }
    close(fd);
}

// print an error message and exit the program
void print_error(char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
