//
// Created by Lorenz Gerber on 15/11/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list_2cell.h"

// Axiome 1
void testForEmtpyQueue() {
    printf("Axiome 1\nTesting for empty queue...");

    // make emtpy queue
    queue *que = queue_empty();
    queue_setMemHandler(que, free);

    // test if queue empty
    if (queue_isEmpty(que)){
        printf("...pass\n\n");
        queue_free(que);
    } else {
        printf("...fail\n\n");
        queue_free(que);
        exit(1);
    }
}

// Axiome 2
void testQueueNotEmptyOnEnque(){
    printf("Axiome 2\nTesting whether queue not empty after enqueue...");

    // make empty queue
    queue *que = queue_empty();
    queue_setMemHandler(que, free);

    // allocate memory and set a value
    int val = 10;
    int *value = malloc(sizeof(int));
    *value = val;

    // enqueue and test if empty
    queue_enqueue(que, value);
    if ( !queue_isEmpty(que)){
        printf("...pass\n\n");
        queue_free(que);
    } else {
        printf("...fail\n\n");
        free(value);
        queue_free(que);
        exit(1);
    }
}

// Axiome 3
void testQueueEmptyOnEnqueueDequeue(){
    printf("Axiome 3\nTesting whether empty queue is empty again after enqueue/dequeue");

    // make emtpy queue
    queue *que = queue_empty();
    queue_setMemHandler(que, free);

    // allocate memory and set value
    int val = 10;
    int *value = malloc(sizeof(int));
    *value = val;

    // enqueue/dequeue and test if empty
    queue_enqueue (que, value);
    queue_dequeue (que);
    if ( queue_isEmpty(que)){
        printf("...pass\n\n");
        queue_free(que);
    } else {
        printf("...fail\n\n");
        queue_free(que);
        exit(1);
    }
}


// Axiome 4
void testQueueCommutativeEnDeQueue(){
    printf("Axiome 4\nTesting commutative property of enqueue/dequeue on non-empty queue");

    // construct two identical empty queues: que1 and que2
    queue *que1 = queue_empty();
    queue_setMemHandler(que1, free);
    queue *que2 = queue_empty();
    queue_setMemHandler(que2, free);

    // define and assign two sets of
    // initial value and test value
    int ini = 15;
    int val = 10;
    int *initial1 = malloc(sizeof(int)); //&ini;
    int *initial2 = malloc(sizeof(int));
    int *value1 = malloc(sizeof(int)); //&val;
    int *value2 = malloc(sizeof(int));
    *initial1 = ini;
    *initial2 = ini;
    *value1 = val;
    *value2 = val;

    // enqueue que1, que2 with same initial value
    queue_enqueue(que1, initial1);
    queue_enqueue(que2, initial2);


    // enqueue and dequeue que1 with test value
    queue_enqueue(que1, value1);
    queue_dequeue(que1);

    // dequeue and enqueue que2 with test value
    queue_dequeue(que2);
    queue_enqueue(que2, value2);

    // check the commutative property of enqueue and dequeue
    // by comparing the front value of que1 and que2
    if (*(int*) queue_front(que1) == *(int*) queue_front(que2)){
        printf("...pass\n\n");
        queue_free(que1);
        queue_free(que2);

    } else {
        printf("...fail\n\n");
        queue_free(que1);
        queue_free(que2);
        exit (1);
    }

}

// Axiome 5
void testQueueEnqueueFrontOnEmpty(){
    printf("Axiome 5\nTesting Enqueue/Front on an empty Queue returns value");

    // make emtpy queue
    queue *que = queue_empty();
    queue_setMemHandler(que, free);

    // allocate memory and set value
    int val = 10;
    int *value = malloc(sizeof(int));
    *value = val;

    // check enqueue/front returns the
    // value
    queue_enqueue (que, value);
    if (*(int*) queue_front(que) == val){
        printf("...pass\n\n");
        queue_free(que);
    } else {
        printf("...fail\n\n");
        queue_free(que);
        exit (1);
    }

}

// Axiome 6
void testQueueEnqueueFrontOnNonEmpty(){
    printf("Axiome 6\nTesting Enqueue/Front on non-empty Queue is equal Front on queue");

    // construct two identical empty queues: que1 and que2
    queue *que1 = queue_empty();
    queue_setMemHandler(que1, free);
    queue *que2 = queue_empty();
    queue_setMemHandler(que2, free);


    // define and assign initial value and test value
    int ini = 15;
    int val = 10;
    int *initial1 = malloc(sizeof(int));
    int *initial2 = malloc(sizeof(int));
    int *value1 = malloc(sizeof(int));
    *initial1 = ini;
    *initial2 = ini;
    *value1 = val;

    // enqueue que1, que2 with same initial value
    queue_enqueue(que1, initial1);
    queue_enqueue(que2, initial2);



    // test enqueue/front on non-empty queue q returns the
    // same as just front on q
    queue_enqueue(que1, value1);
    if ( *(int*) queue_front(que1) == *(int*) queue_front(que2)) {
        printf("...pass\n\n");
        queue_free(que1);
        queue_free(que2);
    } else {
        printf("...fail\n\n");
        queue_free(que1);
        queue_free(que2);
        exit (1);
    }
}


int main (void){
    //testing data type queue
    testForEmtpyQueue();
    testQueueNotEmptyOnEnque();
    testQueueEmptyOnEnqueueDequeue();
    testQueueCommutativeEnDeQueue();
    testQueueEnqueueFrontOnEmpty();
    testQueueEnqueueFrontOnNonEmpty();
    printf("All tests passed!\n");
    return 0;
}
