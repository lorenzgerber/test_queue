//
// Created by Lorenz Gerber on 15/11/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list_2cell.h"


void testForEmtpyQueue() {
    queue *que = queue_empty();
    if (queue_isEmpty(que)){
        printf("TRUE, queue is empty\n\n");
    } else {
        exit(1);
    }
}


void testQueueNotEmptyOnEnque(){
    queue *que = queue_empty();
    queue_setMemHandler(que, free);

    int val = 10;
    int *value = malloc(sizeof(int));
    *value = val;
    queue_enqueue(que, value);
    if ( !queue_isEmpty(que)){
        printf("TRUE, queue is NOT EMPTY\n\n");
        queue_free(que);
    } else {
        exit(1);
    }
}

void testQueueEmptyOnEnqueueDequeue(){
    queue *que = queue_empty();
    queue_setMemHandler(que, free);

    int val = 10;
    int *value = malloc(sizeof(int));
    *value = val;
    queue_enqueue (que, value);
    queue_dequeue (que);
    if ( queue_isEmpty(que)){
        printf("TRUE, queue EMPTY\n\n");
        queue_free(que);
    } else {
        exit(1);
    }
}

void testQueueCommutativeEnDeQueue(){

    // construct two identical empty queues: que1 and que2
    queue *que1 = queue_empty();
    //queue_setMemHandler(que1, free);
    queue *que2 = queue_empty();
    //queue_setMemHandler(que2, free);

    // define and assign initial value and test value
    int ini = 15;
    int val = 10;

    int *initial = malloc(sizeof(int)); //&ini;
    int *value = malloc(sizeof(int)); //&val;
    *initial = ini;
    *value = val;

    // enqueue que1, que2 with same initial value
    queue_enqueue(que1, initial);
    queue_enqueue(que2, initial);

    // Check pre-condition, queue is not empty
    printf("Check pre-condition, queue NOT empty\n");
    if(!queue_isEmpty(que1) && !queue_isEmpty(que2)){
        printf("Queue is NOT empty\n");
    } else {
        exit(1);
    }

    // enqueue and dequeue que1 with test value
    queue_enqueue(que1, value);
    queue_dequeue(que1);

    // dequeue and enqueue que2 with test value
    queue_dequeue(que2);
    queue_enqueue(que2, value);

    // check the commutative property of enqueue and dequeue
    // by comparing the front value of que1 and que2
    if (*(int*) queue_front(que1) == *(int*) queue_front(que2)){
        printf("Queues are the same\n");
    } else {
        exit (1);
    }
    printf("%d\n", *value);
    printf("%d\n", *initial);
    free (value);
    free (initial);

}


void testo(){

    // construct two identical empty queues: que1 and que2
    queue *que1 = queue_empty();
    queue_setMemHandler(que1, free);


    // define and assign initial value and test value
    int ini = 15;
    int val = 10;

    int *initial = malloc(sizeof(int)); //&ini;
    int *value = malloc(sizeof(int)); //&val;
    *initial = ini;
    *value = val;

    // enqueue que1, que2 with same initial value
    queue_enqueue(que1, initial);

    // enqueue and dequeue que1 with test value
    queue_enqueue(que1, value);
    queue_dequeue(que1);
    queue_dequeue(que1);

    printf("%d\n", *value);
    printf("%d\n", *initial);
    //free (value);
    //free (initial);

}



int main (void){

    //int out;
    printf("Testing for empty queue...\n");
    testForEmtpyQueue();

    printf("Testing whether queue not empty after enqueue...\n");
    testQueueNotEmptyOnEnque();

    printf("Testing whether queue is empty after enqueue/dequeue\n");
    testQueueEmptyOnEnqueueDequeue();

    printf("Testing commutative property of en/dequeue\n");
    testQueueCommutativeEnDeQueue();

    testo();



    return 0;
}
