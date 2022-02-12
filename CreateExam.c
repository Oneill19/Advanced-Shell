#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 256

// struct for question and 4 answers
typedef struct Question
{
    char que[MAX];
    char ans[4][MAX];
}Question;

Question* get_questions(int q_num); // get the questions and answers for the exam
void write_file(Question *q, char *exam_name, char *exam_subject, char *writer_name, int q_num);    // create the exam file
void print_error(char* msg);    // print an error message and exit the program

// main function
int main(int argc, char *argv[])
{
	int i, j, q_num;
    Question *q;
    printf("Insert Number of Question:\n");
    scanf("%d", &q_num);    // get the number of questions from the user
    q = get_questions(q_num);   // get the questions and answers for the exam
    write_file(q, argv[1], argv[2], argv[3], q_num);    // create the exam file
    free(q);
    return 0;
}

// get the questions and answers for the exam
Question* get_questions(int q_num)
{
    int i, j;
    Question *q = (Question*)malloc(q_num * sizeof(Question));  // allocate memory for the array of questions and answers
    if (q == NULL)
        print_error("Error allocating memory!");
    for (i = 0; i < q_num; i++)
    {
        printf("Insert Question %d:\n", i + 1); // get the question from the user
        scanf(" %[^\n]s", q[i].que);
        rewind(stdin);
        printf("Insert 4 Answers:\n");
        for (j = 0; j < 4; j++) // get the 4 answers from the user
        {
            printf("\t%d. ", j + 1);
            scanf(" %[^\n]s", q[i].ans[j]);
            rewind(stdin);
        }
    }
    return q;
}

// create the exam file
void write_file(Question *q, char *exam_name, char *exam_subject, char *writer_name, int q_num)
{
    int i, j, fd, wbytes;
    char buff[MAX];
    sprintf(buff, "%s.txt", exam_name); // create the file name of the exam
    fd = open(buff, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        print_error("Open file error!");
    sprintf(buff, "%s\n%d\n", exam_subject, q_num); // insert the subject and number of questions to the exam file
    wbytes = write(fd, buff, strlen(buff));
    if (wbytes == -1 || wbytes < strlen(buff))
        print_error("Write file error!");
    for (i = 0; i < q_num; i++) // insert the questions and their 4 answers to the file
    {
        sprintf(buff, "Question %d:\n%s\n", i + 1, q[i].que);
        wbytes = write(fd, buff, strlen(buff));
        if (wbytes == -1 || wbytes < strlen(buff))
            print_error("Write file error!");
        for (j = 0; j < 4; j++)
        {
            sprintf(buff, "\t%d. %s\n", j + 1, q[i].ans[j]);
            wbytes = write(fd, buff, strlen(buff));
            if (wbytes == -1 || wbytes < strlen(buff))
                print_error("Write file error!");
        }
    }
    sprintf(buff, "Successfully\n%s\n", writer_name);   // insert "Successfully" and the exam writer name to the exam file
    wbytes = write(fd, buff, strlen(buff));
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
