/**************************************************************
#  * MyQueue.h: protocol of a MyQueu.c                        *                                           
#  * Name: Shangxuan Xie                                      *
#  * Homework  ProgHw04 CPU scheduler                         *
#  * Email: sxie@coastal.edu                                  *
#  * Date: 11/30/2019                                         *
#  ************************************************************/



#ifndef MYQUEUE_H_
#define MYQUEUE_H_

struct queueElementS {
  void* contents;				// the queue item
  struct queueElementS* next; // pointer to the next item in queue
};

typedef struct queueElementS element;


struct queueQ { 
  element  *front,*rear; 
}; 

typedef struct queueQ* Queue;
int isempty(Queue q);
Queue newQueue();
void enQueue(Queue q,void* item);
void* deQueue(Queue q);
int getSize(Queue q);
void free_queue(Queue q);
#endif /* MYQUEUE_H_ */
