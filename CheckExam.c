#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 256

int get_q_num(char *path, char *exam_name); // build and return the number of question in the exam
int sol_num(char* sol_path, char* stud_sol_path, char *exam_name, char *stud_name); // return the number of correct answers
void create_file(char *path, int q_num, int a_num); // create the grade file
void print_error(char* msg);    // print an error message and exit the program

// main function
int main(int argc, char *argv[])
{
	int q_num, a_num;
	char exam_path[MAX], sol_path[MAX], stud_sol_path[MAX], output_path[MAX];
	sprintf(exam_path, "%s.txt", argv[1]);  // create the file name of the exam
	sprintf(sol_path, "Sol_%s.txt", argv[1]);   // create the file name of solve of the exam
	sprintf(stud_sol_path, "%s_%s.txt", argv[2], argv[1]);  // create the file name of the student solve
	sprintf(output_path, "Grade_%s_%s.txt", argv[2], argv[1]);  // create the file name of the grade file
	q_num = get_q_num(exam_path, argv[1]);  // get the number of questions in the exam
	a_num = sol_num(sol_path, stud_sol_path, argv[1], argv[2]); // get the number of correct answers in the exam
	create_file(output_path, q_num, a_num); // create the grade file
    return 0;
}

// build and return the number of question in the exam
int get_q_num(char *path, char *exam_name)
{
    int fd, rbytes, q_num = 0;
    char buff[1];
    fd = open(path,O_RDONLY, 0);  // open the exam file
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

// return the number of correct answers
int sol_num(char* sol_path, char* stud_sol_path, char *exam_name, char *stud_name)
{
	int solved = 0, fd_sol, fd_stud, rbytes_sol, rbytes_stud;
	char buff1[1], buff2[1];
	fd_sol = open(sol_path, O_RDONLY, 0);   // open the exam solve file
	if (fd_sol == -1)
	{
    	fprintf(stderr, "%s solve not found!\n", exam_name);
    	exit(1);
    }
	fd_stud = open(stud_sol_path, O_RDONLY, 0); // open the student solve file
	if (fd_stud == -1)
	{
    	fprintf(stderr, "%s\'s %s not found!\n", stud_name, exam_name);
    	exit(1);
    }
	while ((rbytes_sol = read(fd_sol, buff1, 1)) != 0 && (rbytes_stud = read(fd_stud, buff2, 1)) != 0)  // read 1 char from both files
	{
		if (rbytes_sol == -1 || rbytes_stud == -1)
			print_error("Read file error!");
		if (buff1[0] != '\n' && buff2[0] != '\n')   // if both chars are numbers
			if (buff1[0] == buff2[0])   // if both are the same number count as correct answer
				solved++;
	}
    close(fd_sol);
    close(fd_stud);
	return solved;
}

// create the grade file
void create_file(char *path, int q_num, int a_num)
{
	int i, fd, wbytes;
    char buff[MAX];
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        print_error("Open file error!");
    sprintf(buff, "%d/%d\n", a_num, q_num); // create the string for the file
    wbytes =  write(fd, buff, strlen(buff));
    if (wbytes == -1 || wbytes < strlen(buff))
    	print_error("Write file error!");
    close(fd);
}

// print an error message and exit the program
void print_error(char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
