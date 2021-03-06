/**
* Unit Test for datatype queue
* - the header of the datatype to be tested
*   shall be mentioned as include below
* - the unit tests follow the axiomatic specifications
*   given in the book 'Datatyper och algoritmer'
*   (Janlert and Wibert, 2000)
* - the unit tests don't check for memory leaks
*   due to wrong implemented memory handler
*
*
* Created 2015-11-19 by Lorenz Gerber, dv15lgr@cs.umu.se
* Revised 2015-11-25
* Licensed under GNU LGPL3
**/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list_2cell.h"

// Test 1,  Applying isEmpty() on emtpy(). This tests partly
// the isEmpty() and partly the empty() function
// Succeeds when isEmpty() returns TRUE
// Fails when isEmpty() returns FALSE
void testForEmtpyQueue() {
    printf("Test 1/6\nTesting for empty queue...");

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

// Test 2, applying enqueue() on empty() and test
// with isEmpty()
// Succeeds when isEmpty returns FALSE
// Fails when isEmpty returns TRUE
void testQueueNotEmptyOnEnque(){
    printf("Test 2/6\nTesting whether queue not empty after enqueue...");

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

// Test 3, applying enqueue(dequeue(empty())) and check for
// isEmpty()
// Succeeds when isEmpty returns TRUE
// Fails when isEmpty returns FALSE
void testQueueEmptyOnEnqueueDequeue(){
    printf("Test 3/6\nTesting whether empty queue is empty again after enqueue/dequeue");

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


// Test 4, check the equality front(enqueue(dequeue(queue)) ==
// front(dequeue(enqueue(queue)) where queue is a non-emtpy queue.
// succeeds when equality is TRUE
// fails when the equality is FALSE
void testQueueCommutativeEnDeQueue(){
    printf("Test 4/6\nTesting commutative property of enqueue/dequeue on non-empty queue");

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

    // pre-check, que1/que2 must not be empty
    // otherwise front() will result in a seg fault
    if(queue_isEmpty(que1) || queue_isEmpty(que2)){
        printf("...fail\n\n");
        queue_free(que1);
        queue_free(que2);
        exit(1);
    }

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

// Test 5 check the equality front(enqueue(val, empty()))==val
// succeeds when equality is TRUE
// fails when the equality is FALSE
void testQueueEnqueueFrontOnEmpty(){
    printf("Test 5/6\nTesting Enqueue/Front on an empty Queue returns value");

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

// Test 6, check equality of the expression
// front(enqueue(val, non-empty queue) == front(non-empty queue)
// succeeds when the equality is TRUE
// fails when the equality is FALSE
void testQueueEnqueueFrontOnNonEmpty(){
    printf("Test 6/6\nTesting Enqueue/Front on non-empty Queue is equal Front on queue");

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

// Main unit testprogram, calls 6 tests in sequence. If a test fails
// main is terminated (exit(1)).
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
