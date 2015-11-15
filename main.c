//
// Created by Lorenz Gerber on 15/11/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list_2cell.h"

int main (void){
    // make a empty list
    queue *que = queue_empty();
    //queue_setMemHandler(que, free);
    int val = 10;
    int *value = malloc(sizeof(int));
    *value = val;
    queue_enqueue(que, value);
    queue_dequeue(que);
    if (queue_isEmpty(que)){
        printf("TRUE, queue is empty");
    }

    // Check isEmpty(Empty)

    // Check FALSE(Isempty(Enqueue(v, q))
    queue_free(que);
    return 0;
}
