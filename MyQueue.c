/**************************************************************
#  * MyQueue.c: Implementation of a queue                     *                                           
#  * Name: Shangxuan Xie                                      *
#  * Homework ProgHw04 CPU scheduler                          *
#  * Email: sxie@coastal.edu                                  *
#  * Date: 11/30/2019                                         *
#  ************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "MyQueue.h"


Queue newQueue(){
  Queue rqueue;
  rqueue=(Queue)malloc(sizeof(Queue));
  if(!rqueue){//check if rqueue is NULL
    printf(" Out of memory\n"); 
    return NULL;
  }
  rqueue->front=NULL;
  rqueue->rear=NULL;
  return rqueue;
}

int isempty(Queue q){
  int result=0;
  if(q!=NULL){
    if(q->front!=0){
      return -1;
    }else{//if there is no element in q
      result=1;
    }
  }else{
    printf("queue q does not exist!\n");
  }
  return result;
}

void enQueue(Queue q,void* item){
  if(q!=NULL){
    element *el=(element*)malloc(sizeof(element));
    el->contents=item;
    if(q->rear==NULL||q->front==NULL){
      q->front=el;
      q->rear=el;
      el->next=NULL;
    }
    q->rear->next=el;
    q->rear=el;
    el->next=NULL;
  }else{
    printf("Queue q does not exist\n");
  }
}

void* deQueue(Queue q){
  void* temp;
  if(q!=NULL){
    if((isempty(q))==1){
      printf("queue is empty\n");
    }else{
      temp=q->front->contents;
      element *temp1=q->front;
      q->front=q->front->next;
      free(q);
      if (q->front == NULL){ 
        q->rear = NULL; 
      }
    }
  }else{
    printf("queue does not exist\n");
  }
  return temp;
}

int getSize(Queue q){
  int result=0;
  element *temp=q->front;
  while(temp!=NULL){
    result++;
    temp=temp->next;
  }
  return result;
}

void free_queue(Queue q){
  while(q->front!=NULL){
    element *temp=q->front->next;
    free(q->front);
    q->front=temp;
  }
  free(q);
}


