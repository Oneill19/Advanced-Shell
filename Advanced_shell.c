#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TRUE 1
#define FALSE 0
#define MAX 256

int start_command(char *comm, char *argv[]);    // function to create a child process and execute an executable file in the child process
int args_num(char* input);  // function to count the number of args in the input
char** split_command(char *input, int args);    // function to return an array of strings with the command and arguments
void print_error(char *msg);    // function to print an error message and exit the program

// main function
int main()
{
	int i, flag = TRUE, pid;
    char **commands;
    while(flag) // loop until the user input GoodBye or there is a problem with the child process
    {
        int args;
        char input[MAX];
        printf("AdvShell> ");
        scanf(" %[^\n]s", input);   // take the command input from the user
        rewind(stdin);
        args = args_num(input); // count the number of arguments
        if (args > 4)   // if there are more than 4 arguments
        {
            printf("Too much arguments... Try again!\n");
            continue;
        }
        commands  = split_command(input, args); // split the commands to an array of words
        if (!strcmp("CreateExam", commands[0])) // CreateExam
        {
            if (args != 4)  // max 4 arguments for this command
                printf("Arguments error.. Try again!\n");
            else
                if (start_command("CreateExam", commands) == -1)    // create a process and start the command, returns -1 if failed
					flag = FALSE;   // exit the loop in the child process
        }
        else if (!strcmp("SolExam", commands[0]))   //SolExam
        {
            if (args != 2)  // max 2 arguments for this command
                printf("Arguments error... Try again!\n");
            else
                if (start_command("SolExam", commands) == -1)   // create a process and start the command, returns -1 if failed
					flag = FALSE;   // exit the loop in the child process
        }
		else if (!strcmp("StartExam", commands[0])) // StartExam
        {
            if (args != 3)  // max 3 arguments for this command
                printf("Arguments error.. Try again!\n");
            else
                if (start_command("StartExam", commands) == -1) // create a process and start the command, returns -1 if failed
					flag = FALSE;   // exit the loop in the child process
        }
        else if (!strcmp("CheckExam", commands[0])) // CheckExam
        {
            if (args != 3)  // max 3 arguments for this command
                printf("Arguments error... Try again!\n");
            else
                if (start_command("CheckExam", commands) == -1) // create a process and start the command, returns -1 if failed
					flag = FALSE;   // exit the loop in the child process
        }
		else if (!strcmp("CalcGrade", commands[0])) // CalcGrade
        {
            if (args != 3)  // max 3 arguments for this command
                printf("Arguments error... Try again!\n");
            else
                if (start_command("CalcGrade", commands) == -1) // create a process and start the command, returns -1 if failed
					flag = FALSE;   // exit the loop in the child process
        }
        else if (!strcmp("GoodBye", commands[0]))   // if the input is GoodBye free the memory and end the program
            flag = FALSE;
        else    // if it's a regular shell command or it's a not supported command
        {
            pid = fork();   // create a process
            if (pid == -1)  // if the process creating failed print an error message
                print_error("Fork failed!");
            if (pid == 0)   // if it's the child process
            {
                execvp(commands[0], commands);  // try to execute the command as regular shell command
                printf("Not Supported!\n"); // if the exec failed print that the input command not supported
				flag = FALSE;   // exit the loop in the child process
            }
        }
        wait(NULL); // wait until the child process finish
        free(commands); // free the memory of the string array
    }
    return 0;
}

// function to create a child process and execute an executable file in the child process
int start_command(char *comm, char *argv[])
{
    int pid = fork();   // create child process
    if (pid == -1)  // if the process creating failed print an error message
        print_error("Fork failed!");
    else if (pid == 0)  // if it's the child process
	{
        execv(comm, argv);  // exectute the command
		return -1;  // if failed return -1
	}
	return 1;   // if succeed
}

// function to count the number of args in the input
int args_num(char* input)
{
	int args = 1, i;
	for (i = 0; input[i] != '\0'; i++)  // iterate over all char and count the number of spaces
        if (input[i] == ' ')
            args++;
	return args;
}

// function to return an array of strings with the command and arguments
char** split_command(char *input, int args)
{
    int i;
    char** commands;
    commands = (char**)malloc((args + 1) * sizeof(char*));  // allocate memory for the array
    if (commands == NULL)
            print_error("Error allocating memory!");
	commands[0] = strtok(input, " ");   // use strtok() to split the input
    for (i = 1; i < args; i++)
    	commands[i] = strtok(NULL, " ");
	commands[args] = NULL;  // put NULL in the end of the arguments array
    return commands;
}

// function to print an error message and exit the program
void print_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
