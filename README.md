scheudle
--------------------------------------------------------
This is a program that simulates computer scheduling (FCFS | SRTF | RR | PPA).This program comes with a Makefile that user can type make directly into the console window to get the executable file "scheduler".

---------------------------------------------------------
requirements:
This is a c program that can be compiled and run in a Linux environment.
The user can either get the executable through the Makiefile or get an executable named "a.out" by typing gcc scheduler.c myqueue.c function.c directly.
--------------------------------------------------------
Usage:
Usage: ./scheduler [FCFS | RR | SRTF | PPA] quantum/increaser 
Case issues can be ignored, such as FCFS can be entered fcfs.user will be prompted when an inappropriate number is entered and the program will stop
--------------------------------------------------------
Problem description:
1>In PPA mode, I don't know if all programs have a zero priority after a process finishs.In this program, the end of a process does not make the priority of all processes 0.
---------------------------------------------------------
Run example:
1>FCFS
./scheduler fcfs 
1 2 3
2 2 2
0 0 0
0 CPU being idle
1 CPU being idle
2 1 arriving
2 2 arriving
2 1 running
3 1 running
4 1 running
5 1 finish
5 2 running
6 2 running
7 2 finish
Average waiting time:1.50
Average responese time:1.50
Average turnaround time:4.00
Average CPU usage:71.43%

2>RR
./scheduler RR 2
1 0 5 
2 0 3
3 3 1
0 0 0
0 1 arriving
0 2 arriving
0 1 running
1 1 running
2 2 running
3 3 arriving
3 2 running
4 1 running
5 1 running
6 3 running
7 3 finish
7 2 running
8 2 finish
8 1 running
9 1 finish
Average waiting time:4.00
Average responese time:1.67
Average turnaround time:7.00
Average CPU usage:100.00%

3>SRTF
./scheduler srtf
1 2 6
2 2 5
3 3 1
0 0 0
0 CPU being idle
1 CPU being idle
2 1 arriving
2 2 arriving
2 2 running
3 3 arriving
3 3 running
4 3 finish
4 2 running
5 2 running
6 2 running
7 2 running
8 2 finish
8 1 running
9 1 running
10 1 running
11 1 running
12 1 running
13 1 running
14 1 finish
Average waiting time:2.33
Average responese time:2.00
Average turnaround time:6.33
Average CPU usage:85.71%

4>PPA
./scheduler PPA 2
1 0 7 
2 0 2
0 0 0
0 1 arriving
0 2 arriving
0 1 running
1 1 running
2 1 running
3 1 running
4 1 running
5 2 running
6 2 running
7 2 finish
7 1 running
8 1 running
9 1 finish
Average waiting time:3.50
Average responese time:2.50
Average turnaround time:8.00
Average CPU usage:100.00%
