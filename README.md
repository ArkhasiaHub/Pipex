42 Project - Pipex

Pipex is a project from the 42 coding school that aims to replicate a simplified version of shell piping and redirection. The goal is to recreate how the shell processes commands connected by pipes, redirecting the output of one command as the input to the next. This project serves as an introduction to system calls and inter-process communication, particularly focusing on fork, pipe, dup2, and execve.

Objectives
The main objective of the pipex project is to:

Implement a program that mimics the shell behavior with simple piping.
Understand and correctly use system calls related to file descriptors, pipes, and process creation.
Manage inter-process communication and I/O redirection.
Handle error cases and create a robust, reliable program.
Mandatory Requirements
The program takes the following arguments:

shell - Copie paste code
./pipex infile "cmd1" "cmd2" outfile
Where:

infile is the name of the input file.
cmd1 is the first command to execute, reading from infile.
cmd2 is the second command to execute, which takes the output from cmd1 as its input.
outfile is the file where the output of cmd2 will be written.
The program should behave as if running the following command in a shell:

shell - shell - Copie paste code
< infile cmd1 | cmd2 > outfile
