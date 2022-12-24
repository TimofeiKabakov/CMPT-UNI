#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* statically allocated arrays of pointers to the NODE and LIST structures */
LIST lists[MAX_LISTS];
NODE nodes[MAX_NODES];

/* arrays that store indices of free positions in 'lists' and 'nodes' arrays */
int lists_free[MAX_LISTS];
int nodes_free[MAX_NODES];

/* Indices used in cooperation with arrays above.
Positions greater than the index are FREE.
Positions less that the index are OCCUPIED */
int list_idx = -1;
int node_idx = -1;

/* Creates an empty list, returns reference to this
list if successfully created, NULL otherwise */
LIST* ListCreate() {
    /* printf("Got to procedure ListCreate \n"); */
    struct LIST* newList;

    /* Check whether we have reached the maximum amount
    of lists allowed in the library */
    if (list_idx == MAX_LISTS - 1){
       printf("Error: the maximum number of nodes " 
	"in the library has already been reached! \n");
        return NULL;
    }

    if(list_idx == -1) {
        int i;
        for(i = 0; i < MAX_LISTS; i++) {
            lists_free[i] = i;
        }
    }

    list_idx++;
    newList = &(lists[lists_free[list_idx]]);
    newList->index = lists_free[list_idx];

    newList->current = NULL;
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;

    return newList;
}

/* Adds the new item to list directly after the current item,
and makes the new item the current item. If the current pointer
is at the end of the list, the item is added at the end.
Returns 0 on success, -1 on failure. */
int ListAdd(LIST* list, void* item) {
    /* printf("Got to procedure ListAdd \n"); */
    struct NODE* newNode;

    /* Check for the null pointer since it might cause
    a segmentation error */
    if(list == NULL) {
        printf("Error: a null pointer was passed as a list argument \n");
        exit(1);
        return -1;
    }
    /* Check whether we have reached the maximum amount
    of nodes allowed in the library */
    if(node_idx == MAX_NODES - 1) {
        printf("Error: the maximum number of nodes in the " 
	"library has already been reached! \n");
        exit(1);
        return -1;
    }

    if(node_idx == -1) {
        int i;
        for(i = 0; i < MAX_NODES; i++) {
            nodes_free[i] = i;
        }
    }

    node_idx++;
    newNode = &(nodes[nodes_free[node_idx]]);
    newNode->item = item;
    newNode->index = nodes_free[node_idx];

    /* if the list is empty */
    if (list->length == 0){
        list->current = newNode;
        list->head = newNode;
        list->tail = newNode;
    } else if (list->current == list->tail) {
        /* Basically, list Append */
        list->tail->nextNode = newNode;
        newNode->prevNode = list->tail;
        list->current = newNode;
        list->tail = newNode;
    } else {
        /* if the current item is somewhere in between the
        first and the last node in the list*/
        newNode->nextNode = list->current->nextNode;
        newNode->prevNode = list->current;
        list->current->nextNode->prevNode = newNode;
        list->current->nextNode = newNode;
        list->current = newNode;
    }

    list->length++;

    return 0;
}

/* Adds item to list directly before the current item, and makes
the new item the current one. If the current pointer is at the start
of the list, the item is added at the start.  
Returns 0 on success, -1 on failure. */
int ListInsert(LIST* list, void* item){
    /* printf("Got to procedure ListInsert \n"); */
    struct NODE* newNode;

    /* Check for the null pointer since it might cause
    a segmentation error */
    if(list == NULL) {
        printf("Error: a null pointer was passed as a list argument \n");
        exit(1);
        return -1;
    }
    /* Check whether we have reached the maximum amount
    of nodes allowed in the library */
    if(node_idx == MAX_NODES - 1) {
        printf("Error: the maximum number of "
	" nodes in the library has already been reached! \n");
        exit(1);
        return -1;
    }

    if(node_idx == -1) {
        int i;
        for(i = 0; i < MAX_NODES; i++) {
            nodes_free[i] = i;
        }
    }

    node_idx++;
    newNode = &(nodes[nodes_free[node_idx]]);
    newNode->item = item;
    newNode->index = nodes_free[node_idx];

    /* if the list is empty */
    if (list->length == 0){
        list->head = newNode;
        list->tail = newNode;
    } else if (list->current == list->head){
        /* Basically, list Prepend */
        list->head->prevNode = newNode;
        newNode->nextNode = list->head;
        list->head = newNode;
    } else {
        /* Set the previous node of the current node to a temporary variable
        then we would set the previous Node of the current node to a new node
        set the next node of the new node to the current node
        set the previous node of the new node to the temporary variable
        set the next node of the temporary variable to the new node
        set current to point to the new node */
        struct NODE* temp = list->current->prevNode;
        newNode->prevNode = temp;
        temp->nextNode = newNode;
        newNode->nextNode = list->current;
        list->current->prevNode = newNode;
    }

    /* make the new item the current one */
    list->current = newNode;
    list->length++;

    return 0;
}

/*Adds item to the end of list, and makes the new item the
current one. Returns 0 on success, -1 on failure.*/
int ListAppend(LIST* list, void* item) {
    /* printf("Got to procedure ListAppend \n"); */
    struct NODE *newNode;

    /* Check for the null pointer since it might cause
    a segmentation error */
    if(list == NULL) {
        printf("Error: a null pointer was passed as a list argument \n");
        exit(1);
        return -1;
    }
    /* Check whether we have reached the maximum amount
    of nodes allowed in the library */
    if(node_idx == MAX_NODES - 1) {
        printf("Error: the maximum number of "
	" nodes in the library has already been reached! \n");
        exit(1);
        return -1;
    }

    if(node_idx == -1) {
        int i;
        for(i = 0; i < MAX_NODES; i++) {
            nodes_free[i] = i;
        }
    }

    node_idx++;
    newNode = &(nodes[nodes_free[node_idx]]);
    newNode->item = item;
    newNode->index = nodes_free[node_idx];

    /* if the list is empty */
    if (list->length == 0){
        list->current = newNode;
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->nextNode = newNode;
        newNode->prevNode = list->tail;
        list->current = newNode;
        list->tail = newNode;
    }

    list->length++;

    return 0;
}

/* Adds item to the front of list, and makes the new item
the current one. Returns 0 on success, -1 on failure.*/
int ListPrepend(LIST* list, void* item){
    /* printf("Got to procedure ListPrepend \n"); */
    struct NODE* newNode;

    /* Check for the null pointer since it might cause
    a segmentation error */
    if(list == NULL) {
        printf("Error: a null pointer was passed as a list argument \n");
        exit(1);
        return -1;
    }
    /* Check whether we have reached the maximum amount
    of nodes allowed in the library */
    if(node_idx == MAX_NODES - 1) {
        printf("Error: the maximum number of nodes"
	" in the library has already been reached! \n");
        exit(1);
        return -1;
    }

    if(node_idx == -1) {
        int i;
        for(i = 0; i < MAX_NODES; i++) {
            nodes_free[i] = i;
        }
    }

    node_idx++;
    newNode = &(nodes[nodes_free[node_idx]]);
    newNode->item = item;
    newNode->index = nodes_free[node_idx];

    /* if the list is empty */
    if (list->length == 0){
        list->current = newNode;
        list->head = newNode;
        list->tail = newNode;
    } else {
        /* Set the previous node of the head to the new node
        then set the next node of the new node to the head node
        make the new node the head and current of the list */
        list->head->prevNode = newNode;
        newNode->nextNode = list->head;
        list->current = newNode;
        list->head = newNode;
    }

    list->length++;

    return 0;
}
