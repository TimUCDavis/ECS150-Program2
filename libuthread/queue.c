#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"

struct queue {
    struct Node *front;
    struct Node *last; 
    int length;
};

//create a node struct since it is useful for queue struct
struct Node {
	  void* value;
	  struct Node *next;
};


queue_t queue_create(void)
{

	struct queue *queue = malloc(sizeof(struct queue));
	if ( queue == NULL){
        //if malloc failed return -1
		return NULL;
	}
    else{
	    queue->front = NULL;
	    queue->last = NULL;
	    queue->length = 0;
	    return queue;
	}

}

int queue_destroy(queue_t queue)
{
	if (queue == NULL || queue->last != NULL || queue->front != NULL){
        //if queue dne or is not empty return -1
	    return -1;
	}
	else{
		free(queue);
		return 0; 
	}

}

int queue_enqueue(queue_t queue, void* data){

	//create new node to add
    struct Node *newNode = malloc(sizeof(struct Node));

    if(newNode == NULL){
        //if malloc failed, no more space
        return -1;
    }
    //initialized newNode
    newNode->value = data;
    newNode->next = NULL;

    if(queue == NULL || data == NULL){
        //check if queue or data exist
    	return -1; 
    }else if (queue->front == NULL || queue->last == NULL){
        //if it is the first node to be added
        queue->front = newNode;
        queue->last = newNode;
    }
    else{
        //general add node
         queue->last->next = newNode;
         queue->last = newNode;
    }
    queue->length += 1;
    return 0;
}

int queue_dequeue(queue_t queue, void **data){

    if ( data == NULL || queue == NULL || queue->front == NULL || queue->last == NULL){
        //check if queue or data exist or queue is empty
        return -1;
    }
    // store previous front into temp and dequeue
    struct Node *temp = queue->front;
    queue->front = queue->front->next;
 

    if (queue->front == NULL){
        // if queue now is empty
    	queue->last = NULL;
    }
    *data = temp->value;
    queue->length -= 1;
    free(temp);
    return 0;
}

int queue_delete(queue_t queue, void *data){
    

    if (queue == NULL || data == NULL){
        //check if queue or data is null
        return -1;
    }
    bool findData = false;
    //add a dummy node for the purpose of combine cases
    struct Node *dummyNode = malloc(sizeof(struct Node));
    dummyNode->value = 0;
    dummyNode->next = queue->front;
    //check if data exist in queue
    struct Node* temp = queue->front;
    while(temp->next != NULL) {
        if (&(temp->next) == data) {  //!!!!!!!! equality of memory pointers or value?
            findData = true;
            break;
        }
        temp = temp->next;
    }
    if(!findData){
        return -1;
    }else if(temp->next->next == NULL){
        temp->next = NULL;
    }else{
        struct Node* tempNode = malloc(sizeof(struct Node));
        tempNode = temp->next->next;
        temp->next->next = NULL;
        temp->next = tempNode;
    }

    if(queue->front->next == NULL){
        //if nothing is after the dummy node set queue to empty
        queue->front = NULL;
        queue->last = NULL;
    }else{
        //else delete dummy node
        queue->front = queue->front->next;
    }
    free(temp->next);
    queue->length -= 1;
    return 0;

}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data){

    if(func == NULL || queue == NULL){
        //if either is null return -1
        return -1;
    }else{
        //iterate through the queue
        struct Node *node = queue->front;
        while(node->next != NULL){
            if((*func)(node->value, (void*)arg) == 1){
                //if func equal 0 break
                if(data != NULL){
                    //if data is not null set it to node
                    *data = node;
                }
                break;
            }else{
                //if func not equal to 1 keep iterating
                node = node->next;
            }
        }
        return 0;
    }
}

int queue_length(queue_t queue)
{
	if(queue == NULL){
	    return -1;
	}else{
	    return queue->length;
	}

}

