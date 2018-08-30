Student Information
-------------------
<Student 1 Information>
Paul F. Kim
pfk273@vt.edu

<Student 2 Information>
Chiwon Song
kevins14@vt.edu


How to execute the shell
------------------------
<describe how to execute from the command line>
First of all, we checked if the command is a built-in command.
If it is a built-in command, the command does the built-in job and it does not go to job list and give the control to the terminal after done with the job.
If it is an executable command, we set the jid and status of the pipeline. Then, we check if the pipeline needs to be piped. If it need, set the pipe. Then we block the signal and fork.
In child process we set the pgid of the pipeline and redirect pipe for the multi-pipe. Then, we redirect io if it is needed. After that, we give the control to the pgid of the current job and execute the command.
In parent process we set the pid of the current command, and set the pgid of the current pipeline. Then, we close the previous pipe and set the previous pipe to the next pipe. If the command is the last command in the pipeline, we close all the pipes.
Then, we push the current pipeline to the job list and waif for the job is the job is in foreground. After that, we give the control back to the shell and unblock the signal which is blocked previously.


Important Notes
---------------
<Any important notes about your system>
We made a c and h file for built-in commands.


Description of Base Functionality
---------------------------------
<describe your IMPLEMENTATION of the following commands:
jobs, fg, bg, kill, stop, \ˆC, \ˆZ >
For jobs, we iterate through the job list and print out the pipeline's jid, status and job command.
For fg, we check if the job list is empty at first. Then, if there is no argument we change the status of the job which is located in the back of the job list. And we send continue signal. When the job is done, we give the control back to the terminal. If there is an argument, we do the same thing to the job whose jid is matching with the argument.
For bg, the all process is same but the terminal does not wait for the job done.
For kill and stop, we check if there is an argument. If there is no aregument, we send a kill or stop signal. If there is an argument, we send a kill or stop signal to kill or stop the job whose jid is matching with the argument. When the signal is sent, signal handler catches the signal and it stops or kills the job in the child status change method. If the signal is stop it changes the job's status, and if the signal is kill it removes the job in the job list.
For ^C and ^Z, it sends signal according to the command. And signal handler catches the corresponding signal.


Description of Extended Functionality
-------------------------------------
<describe your IMPLEMENTATION of the following functionality:
I/O, Pipes, Exclusive Access >
For I/O, we checked if iored_input and iored_output are null. If it not null, open the file for reading only and put the file in the standard input, then close it. For the output, if the command's append_to_output is not null, open the file for reading only and set the file offset to the end of the file prior to eah write and create the file if the file is not exist. Then gives write and read permission to the user and group.
We checked if the pipline has more than one command. If there are more than one command in the pipeline, set the pipe in int array and fork. In child process, close the output pipe for the previous job and duplicate the previous input to the standard input and close the previous job's input file decriptior. Then, if the job is not the last job in the pipeline, close the next job's input file decriptor and duplicate the next job's output file descriptor to the standard output. And close the pipe.
At the beginning, give the terminal access to the shell. And before executing a command, give terminal access to the pipeline in which the command executing is located. If the command is executing in foreground, wait till the command is done. And if the command is executing in background, give terminal access to the shell not waiting for the command terminated.

List of Plugins Implemented
---------------------------
(Written by Your Team)
<plugin name>
calo
<description>
this plug-in calculates total calories for the correnponding grams of carb, protein and fat.

<plugin name>
lbtokg
<description>
This plug-in converts lb to kg or kg to lb.

<plugin name>
second
<description>
This plug-in converts second to day hour min second.
