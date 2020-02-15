/**************************************************************
#  * scheduler.c: This file contains main() fucntion          *                                          
#  * Name: Shangxuan Xie                                      *
#  * Homework  ProgHw04 CPU scheduler                         *
#  * Email: sxie@coastal.edu                                  *
#  * Date: 11/30/2019                                         *
#  ************************************************************/





#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

void getData(struct PCB pcbs[25],int* count);
int main(int argc,char *argv[]){
  char* RR="RR";
  char* FCFS="FCFS";
  char* SRTF="SRTF";
  char* PPA="PPA";
  struct PCB pcbs[25];
  int size=0;
  int argument2;
  if(argc<2){
     printf("Usage: scheduler [FCFS | RR | SRTF] [PPA] quantum/increaser\n");
     exit(1);
  }
  char* alg=argv[1];
  //Check to see if the name of argument1 is valid
  if(strcasecmp(alg,RR)!=0&&strcasecmp(alg,FCFS)!=0&&strcasecmp(alg,SRTF)!=0&&strcasecmp(alg,PPA)!=0){
     printf("Usage: scheduler [FCFS | RR | SRTF] [PPA] quantum/increaser\n");
     exit(1);
  }
  //If argument1 is "RR" or "PPA",Gets the value of argument2.
  if(strcasecmp(alg,RR)==0||strcasecmp(alg,PPA)==0){
    if(argc<3){
      printf("please enter quantum or increaser!\n");
      exit(1);
    }
    argument2=atoi(argv[2]);
    if(argument2<=0){//ensure arugument 2 is postive
      printf("please input a postive quantum or increaser!\n");
      exit(1);
    }
  }

  // get Data from standard in
  getData(pcbs,&size);


  if(strcasecmp(alg,FCFS)==0){
    FCFS_simulation(pcbs,size);
  }else if(strcasecmp(alg,SRTF)==0){
    SRTF_simulation(pcbs,size);
  }else if(strcasecmp(alg,RR)==0){
    RR_simulation(pcbs,size,argument2);
  }else if(strcasecmp(alg,PPA)==0){
    PPA_simulation(pcbs,size,argument2);
  }
  return 0;
}




