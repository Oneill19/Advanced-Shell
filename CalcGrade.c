#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 256

void conv(char *path, int *fd, int *sol_num, int *q_num);	// convert the number of correct answers and number of question from the file to int
float calc_final(int sol_num, int q_num);	// calculate the final grade in n/100 format
void write_file(int *fd, float final);	// write the final grade to the file
void print_error(char* msg);	// print an error message and exit the program

// main function
int main(int argc, char *argv[])
{
    int sol_num, q_num, fd;
    float final;
    char path[MAX];
    sprintf(path, "Grade_%s_%s.txt", argv[2], argv[1]);	// create a string with the name of the file
	fd = open(path, O_RDWR, 0);	// open the file
	if (fd == -1)	// if the file did not opened or not exist print an error message and exit the program
	{
		fprintf(stderr, "%s not found!\n", argv[1]);	// if the file does not exist
		exit(1);
	}	
	conv(path, &fd, &sol_num, &q_num);	// convert the grade in the file to int
	final = calc_final(sol_num, q_num);	// calculate the final grade
	printf("%s\n%s\nFinal Grade: %.4g\n", argv[2], argv[1], final);	// print the final grade
	write_file(&fd, final);	// write to file
	close(fd);	// close the file
    return 0;
}

// convert the number of correct answers and number of question from the file to int
void conv(char *path, int *fd, int *sol_num, int *q_num)
{
	int prev_sum = 0, sum = 0, rbytes;
	char buff[1];
	while ((rbytes = read(*fd, buff, 1)) != 0)	// read one char every time
	{
		if (rbytes == -1)
			print_error("Read file error!");
		if (buff[0] == '/')	// if finished to build the number of correct answers
		{;
			prev_sum = sum;
			sum = 0;
		}
		else if (buff[0] < '0' || buff[0] > '9')	// if the char is not a number (except '/') break the loop
			break;
		else	// build the number manually
		{
			sum *= 10;
			sum += buff[0] - 48;
		}
	}
	*sol_num = prev_sum;	// number of correct answers
	*q_num = sum;	// number of question
}

// calculate the final grade in n/100 format
float calc_final(int sol_num, int q_num)
{
	float final = (float) sol_num / q_num;
	return final * 100;
}

// write the final grade to the file
void write_file(int *fd, float final)
{
	int wbytes;
	char buff[MAX];
	sprintf(buff, "Final Grade: %.4g/100\n", final);	// create the string to put in the file
	wbytes = write(*fd, buff, strlen(buff));
	if (wbytes == -1 || wbytes < strlen(buff))
		print_error("Write file error!");
}


// print an error message and exit the program
void print_error(char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
