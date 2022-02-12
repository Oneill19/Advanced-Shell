# Advanced-Shell
UNIX shell upgrade build during my 3rd year Operating System class.

Created in UNIX enviornment (CentOS 7)
This program create 6 more commands to the existing shell.  
The 6 command added are for building exams,  creating solution for the exam, answer them, check and grade them.
The program demonstrate the use of processes and the use of System Calls like open, read, write and exec
To run the program, run ```Advanced_shell.sh``` in the terminal.  
The original shell commands will work with up to 4 parameters.  
```Advanced_shell.c``` is the main program that get the user input and use exec to run the commands.

#

### Commands
- **CreateExam** - This command will take 3 parameters, the name of the exam, the subject and the writer. The command will run the ```CreateExam.c``` file and will ask the user to input the number of questions, after that the user write the question and 4 answers. all the questions and the answers will be written to a text file called ```nameofexam.txt```.

- **SolExam** - This command will take 1 parameter, the name of the exam. The command will run the ```SolExam.c``` file and will ask the user to input the number of the correct answer for that exam by order. The program create a text file called ```SOL_nameofexam.txt``` that will contain the correct answer number for every question in order.

- **StartExam** - This command will take 2 parameters, the name of the exam and the name of the student. The command will run the ```StartExam.c``` file and print the exam to the shell, after that the student will write the number of the question and the number of the question, the student input will be written to a text file called ```nameofexam_nameofstudent.txt```.

- **CheckExam** - This command will take 2 parameters, the name of the exam and the name of the student. The command will run the ```CheckExam.c``` file and will compare the student answers to the correct answers using the solution file created earlier. The program write to a text file called ```Grade_nameofstudent.txt``` the number of the currect answers of the students and the number of questions.

- **CalcGrade** - This command will take 2 parameters, the name of the exam and the name of the student. The command will run the ```CalcGrade.c``` file and open the the file created in CheckExam command, it will calculate the final grade and add it to the file of the grade.

- **Goodbye** - This command will exit Advanced shell program and will return to the original shell.
