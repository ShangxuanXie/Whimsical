/**************************************************************
#  * functions: implementation of functions,include(FCFS||RR  *
#  * |SRTF|PPA)                                               *                                           
#  * Name: Shangxuan Xie                                      *
#  * Homework  ProgHw04 CPU scheduler                         *
#  * Email: sxie@coastal.edu                                  *
#  * Date: 11/30/2019                                         *
#  ************************************************************/





#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"
void FCFS_simulation(struct PCB pcbs[25],int size){
    Queue q=newQueue();
    struct PCB *currentP;
    int CPUWaitting=0;//Record the time of CPU idle
    int waitingTime=0;//Total waitting time,In FCFS waiting time = response time
    int turnaroundT=0;//Total turnaround time 
    int arriveC=0;
    int finishedC=0;
    int isRun=0;//Check to see if a process is running
    int restT=0;//The rest of the current process's CPU time
    int time=0;	
    
    //When processes is not over
    while(finishedC<size){
      int i=arriveC;
      for(i;i<size;i++){
	if(pcbs[i].arrival_time==time){	
	  arriveC++;
	  printf("%d %d arriving\n",time,pcbs[i].pid);
	  enQueue(q,&(pcbs[i]));
	  
	}
      }
       
      //if q is not empty

      if(isempty(q)==-1&&isRun==0){
	currentP=deQueue(q);
	restT=currentP->cpu_time;
       	isRun=1;
	
      }
      
      if(isRun==1){
	restT=restT-1;
	printf("%d %d running\n",time,pcbs[finishedC].pid);
	if(restT<=0){
	  printf("%d %d finish\n",time+1,pcbs[finishedC].pid);
	  turnaroundT+=time-pcbs[finishedC].arrival_time+1;//T+=end time-start time
	  finishedC++;
	  isRun=0;
	}
      }else{
	printf("%d CPU being idle\n",time);
	CPUWaitting++;
      }
      waitingTime+=getSize(q);
      time++;    
  }
    printf("Average waiting time:%.2f\n",(double)waitingTime/size);
    //In FCFS, waitting time equals to responese time
    printf("Average responese time:%.2f\n",(double)waitingTime/size);
    printf("Average turnaround time:%.2f\n",(double)turnaroundT/size);
    printf("Average CPU usage:%.2f%\n",((double)(time-CPUWaitting)/time)*100);
    free_queue(q);
}


void SRTF_simulation(struct PCB pcbs[25],int size){
  int sizeR=0;// true size of remainT array.
  int *remainT=(int*)malloc(sizeof(int)*size);
  int *index=(int*)malloc(sizeof(int)*size);// parallel with reaminT,store index of item in pcbs[25].
  int arriveC=0;//The number of processes that have arrived
  int finishedC=0;//The number of processes that have finished.
  int CPUWaitting=0;//Record the time of CPU idle
  int waitingTime=0;//Total waitting time,In FCFS waiting time = response time
  int turnaroundT=0;//Total turnaround time 
  int responseT=0;//Total responese time
  int time=0;	
  
  while(finishedC<size){
    int i=arriveC;
      for(i;i<size;i++){
	if(pcbs[i].arrival_time==time){	
	  printf("%d %d arriving\n",time,pcbs[i].pid);
	  remainT[sizeR]=pcbs[i].cpu_time;
          index[sizeR]=i;
	  arriveC++;
	  sizeR++;
	  sortArray(&remainT,&index,sizeR);
	}
      }
      if(arriveC>finishedC){
	//calculate total response time
	if(remainT[0]==pcbs[index[0]].cpu_time){
	  responseT+=time-pcbs[index[0]].arrival_time;
	}
	remainT[0]=remainT[0]-1;
	printf("%d %d running\n",time,pcbs[index[0]].pid);
	waitingTime+=sizeR-1;// waittingTime=waitingTime+(how many process in array -1);
	if(remainT[0]==0){
	  finishedC++;
	  printf("%d %d finish\n",time+1,pcbs[index[0]].pid);
	  turnaroundT+=time-pcbs[index[0]].arrival_time+1;//T+=end time-start time
	  shiftArray(&remainT,sizeR);
	  shiftArray(&index,sizeR);
	  sizeR--;
	}
      }else{
	printf("%d CPU being idle\n",time);
	CPUWaitting++;
      }
     time++; 
  }
    printf("Average waiting time:%.2f\n",(double)waitingTime/size);
    //In FCFS waitting time = responese time
    printf("Average responese time:%.2f\n",(double)responseT/size);
    printf("Average turnaround time:%.2f\n",(double)turnaroundT/size);
    printf("Average CPU usage:%.2f%\n",((double)(time-CPUWaitting)/time)*100);
  free(remainT);
  free(index);
}



void RR_simulation(struct PCB pcbs[25],int size,int  quantum){
  Queue q=newQueue();
  int arriveC=0;//The number of processes that have arrived
  int finishedC=0;//The number of processes that have finished.
  int CPUWaitting=0;//Record the time of CPU idle
  int waitingTime=0;//Total waitting time
  int turnaroundT=0;//Total turnaround time 
  int responseT=0;//Total responese time
  int isRun=0;//Check to see if a process is running
  int runTime=0;//store run time
  int time=0;
  struct PCB *currentP;
  while(finishedC<size){
    int i=arriveC;
    for(i;i<size;i++){
      if(pcbs[i].arrival_time==time){	
	arriveC++;
	printf("%d %d arriving\n",time,pcbs[i].pid);
	enQueue(q,&(pcbs[i]));
      }
    }
    if(isRun==1){
     if(runTime>=quantum&&currentP->rtime < currentP->cpu_time){
	enQueue(q,currentP);
	runTime=0;
	isRun=0;
      }
    }
    if(isempty(q)==-1&&isRun==0){
	currentP=deQueue(q);
	isRun=1;
      }

    if(isRun==1){
      if(currentP->rtime==0){
	responseT+=time-currentP->arrival_time;
      }
      currentP->rtime++;
      runTime++;
      	printf("%d %d running\n",time,currentP->pid);
      
      if(currentP->rtime >= currentP->cpu_time){
	finishedC++;
	printf("%d %d finish\n",time+1,currentP->pid);
	turnaroundT+=time-currentP->arrival_time+1;//T+=end time-start time
	runTime=0;
	isRun=0;
      }
    }else{
      printf("%d CPU being idle\n",time);
      CPUWaitting++;
    }
    waitingTime+=getSize(q);
    time++;
  }
    printf("Average waiting time:%.2f\n",(double)waitingTime/size);
    printf("Average responese time:%.2f\n",(double)responseT/size);
    printf("Average turnaround time:%.2f\n",(double)turnaroundT/size);
    printf("Average CPU usage:%.2f%\n",((double)(time-CPUWaitting)/time)*100);

}



void PPA_simulation(struct PCB pcbs[25],int size,int increaser){
    int sizeP=0;//size of priorityArray. 
    int currentIndex=0;
    int isIncreased=0;
    int isFinishOne=0;
    int *priorityArray=(int*)malloc(sizeof(int)*size);
    int *sWaiting=(int*)malloc(sizeof(int)*size);
    int *index=(int*)malloc(sizeof(int)*size);// parallel with priorityArray,store index of item in pcbs[25].
    int arriveC=0;//The number of processes that have arrived
    int finishedC=0;//The number of processes that have finished.
    int CPUWaitting=0;//Record the time of CPU idle
    int waitingTime=0;//Total waitting time
    int turnaroundT=0;//Total turnaround time 
    int responseT=0;//Total responese time
    int time=0;
    while(finishedC<size){
      int i=arriveC;
      for(i;i<size;i++){
	if(pcbs[i].arrival_time==time){	
	  printf("%d %d arriving\n",time,pcbs[i].pid);
	  priorityArray[sizeP]=0;
	  sWaiting[sizeP]=0;
	  index[sizeP]=i;
	  arriveC++;
	  sizeP++;
	}
      }
      int j=1;
      for(j;j<sizeP;j++){
	//Increase the priority of processes based on the time they arrive
	if(sWaiting[j]==5){
	  priorityArray[j]+=increaser;
	  isIncreased=1;
	}
	sWaiting[j]++;
      }
      if(isIncreased==1){
	compareAndMove(&priorityArray,&index,&sWaiting,sizeP,isFinishOne);
	isFinishOne=0;
	isIncreased=0;
	int z=0;
	for(z;z<sizeP;z++){
	  printf(" index %d priority %d sw %d\n",index[z],priorityArray[z],sWaiting[z]);
	}
      }
      currentIndex=index[0];
      if(arriveC>finishedC){
	if(pcbs[currentIndex].rtime==0){
	  responseT+=time-pcbs[currentIndex].arrival_time;
	}
	pcbs[currentIndex].rtime+=1;
	waitingTime+=sizeP-1;
	printf("%d %d running\n",time,pcbs[currentIndex].pid);
	if(pcbs[index[0]].rtime >=pcbs[currentIndex].cpu_time){
	    finishedC++;
	    printf("%d %d finish\n",time+1,pcbs[currentIndex].pid);
	    turnaroundT+=time-pcbs[currentIndex].arrival_time+1;
	    shiftArray(&priorityArray,sizeP);
	    shiftArray(&index,sizeP);
	    shiftArray(&sWaiting,sizeP);
	    sizeP--;
	    isFinishOne=1;
	}
      }else{
	printf("%d CPU being idle\n",time);
	CPUWaitting++;
      }
      time++;
    }
    printf("Average waiting time:%.2f\n",(double)waitingTime/size);
    printf("Average responese time:%.2f\n",(double)responseT/size);
    printf("Average turnaround time:%.2f\n",(double)turnaroundT/size);
    printf("Average CPU usage:%.2f%\n",((double)(time-CPUWaitting)/time)*100);
    free(priorityArray);
    free(index);
    free(sWaiting);
 }



void sortArray(int **arr1,int **arr2,int size){
  int i=0;
  for(i;i<size-1;i++){
    int j=0;
    for(j=0;j<size-1-i;j++){
      if((*arr1)[j]>(*arr1)[j+1]){
	int temp1=(*arr1)[j+1];
	int temp2=(*arr2)[j+1];
	(*arr1)[j+1]=(*arr1)[j];
	(*arr2)[j+1]=(*arr2)[j];
	(*arr1)[j]=temp1;
	(*arr2)[j]=temp2;
      }
    }
  }
}

void compareAndMove(int **arr1,int **index,int **arr3,int size,int isf){
  int i=0;
  for(i;i<size-1;i++){
    int j=0;
    for(j=0;j<size-1-i;j++){
      if((*arr1)[j]<(*arr1)[j+1]){
	int temp2=(*arr1)[j+1];
	int temp1=(*index)[j+1];
	(*arr1)[j+1]=(*arr1)[j];
	(*index)[j+1]=(*index)[j];
	(*index)[j]=temp1;
	(*arr1)[j]=temp2;
      }
    }
  }
 
  if(isf==0){
  int i1=1;
  int temp2=(*index)[1];
  for(i1;i1<size-1;i1++){
    (*index)[i1]=(*index)[i1+1];
  }
  (*index)[size-1]=temp2;
  }
  int i2=0;
  for(i2;i2<size;i2++){
    (*arr1)[i2]=0;
    (*arr3)[i2]=1;
  }

}


 void shiftArray(int **arr1,int size){
   int i=0;
   for(i;i<size-1;i++){
     (*arr1)[i]=(*arr1)[i+1];
   }

 }

void initArray(int **arr1,int size){
int i=0;
   for(i;i<size;i++){
     (*arr1)[i]=0;
   }

 }

void getData(struct PCB pcbs[25],int* count){
  *count=0;
  int *array=(int*)malloc(sizeof(int)*25);
  int lastArrival=0;//When did the last process arrive
  while(1){
    int pid,arrive_time,cpu_time;
    scanf("%d%d%d",&pid,&arrive_time,&cpu_time);
    if(pid==0&&arrive_time==0&&cpu_time==0){
      break;
    }
    
    //Make sure each pid is unique
    int isExist=0;
    int j=0;
    for(j;j<*count;j++){
      if(pid==array[j]){//If the pid is repeated
	printf("please ensure pid is unique!\n");
	isExist=1;
	exit(1);
      }
    }
    if(isExist==0){
      array[*count]=pid;
    }
    //Make sure the arrival time is increasing
    if(arrive_time<lastArrival){
      printf("arrival time need to be incremented\n");
      exit(1);
    }else {
      lastArrival=arrive_time;
    }
    //Make sure arrive_time>=0, and cpu_time>0
    if(arrive_time<0||cpu_time<=0){
      printf("Please enter the appropriate integer for arrival time and cpu time \n");
      exit(1);
    }
    pcbs[*count].pid=pid;
    pcbs[*count].arrival_time=arrive_time;
    pcbs[*count].cpu_time=cpu_time;
    pcbs[*count].rtime=0;
    *count=*count+1;
    if(*count>=25){
      printf("Input terminated, up to 25 tasks can be input!\n");
    }
  }
  free(array);
}
