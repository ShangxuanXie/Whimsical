/**************************************************************
#  * functions.h: Protocol of functions,c                     *                                         
#  * Name: Shangxuan Xie                                      *
#  * Homework  ProgHw04 CPU scheduler                         *
#  * Email: sxie@coastal.edu                                  *
#  * Date: 11/30/2019                                         *
#  ************************************************************/


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "MyQueue.h"
struct PCB{
  int pid;
  int arrival_time;
  int cpu_time;
  int rtime;//Record how long the process has been running,default as 0
};
void FCFS_simulation(struct PCB pcbs[25],int size);
void SRTF_simulation(struct PCB pcbs[25],int size);
void RR_simulation(struct PCB pcbs[25],int size,int  quantum);
void PPA_simulation(struct PCB pcbs[25],int size,int increaser);
void sortArray(int **arr1,int **arr2,int size);
void compareAndMove(int **arr1,int **arr2,int **arr3,int size,int isf);
void shiftArray(int **arr1,int size);
void initArray(int **arr1,int size);
void getData(struct PCB pcbs[25],int* count);

#endif
