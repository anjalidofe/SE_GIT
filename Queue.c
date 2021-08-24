#include<stdio.h>
#include<string.h>
#include "Queue.h"
void initq(queue *q, int len){
    q->size = len;
    q->front = -1;
    q->rear = -1;
    q->Q = (int*)malloc(sizeof(int)*len);
}

int isFullq(queue q) {
    return (q.rear == q.size-1);
}

// Queue is empty when size is 0
int isEmptyq(queue q) {
    return (q.rear == -1);
}

void enqueue(queue *q, int item) {
    if (isFullq(*q))
        return;
    if (q->front = -1)
        q->front = 0;
    q->rear += 1;
    q->Q[q->rear] = item;
    return ;
}

int dequeue(queue *q){
    if (isEmptyq(*q))
        return ;
    int item = q->Q[q->front];
    q->front += 1;
    return item;
}

