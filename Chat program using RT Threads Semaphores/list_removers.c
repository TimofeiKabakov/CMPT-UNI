#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Return current item and take it out of list.
 * Make the next item the current one. */
void* ListRemove(LIST* list){
    NODE *previous, *next;
    void* currentItem;
    int currentIndex;

    /* check for the null pointer since it might cause a segmentation error */
    if(list == NULL || node_idx == -1) {
        printf("Error in procedure ListRemove: invalid parameter list");
        exit(1);
        return NULL;
    } else if (list->length == 0) {
        printf("Error: can not remove from an empty list");
        exit(1);
        return NULL;
    }

    currentItem = list->current->item;
    currentIndex = list->current->index;

    if(list->length == 1) {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    } else if (list->current == list->head){
        list->head = list->head->nextNode;
        list->head->prevNode = NULL;
        list->current = list->head;
    } else if (list->current == list->tail){
        list->tail = list->tail->prevNode;
        list->tail->nextNode = NULL;
        list->current = list->tail;
    } else {
        previous = list->current->prevNode;
        next = list->current->nextNode;
        previous->nextNode = next;
        next->prevNode = previous;
        list->current = next;
    }


    nodes_free[node_idx] = currentIndex;
    node_idx = node_idx - 1;
    list->length = list->length - 1;

    return currentItem;
}

/* Adds list2 to the end of list1. The current pointer 
 * is set to the current pointer of 
 * list1. List2 no longer exists after the operation */
void ListConcat(LIST* list1, LIST* list2){
    if(list1 == NULL) {
        printf("Error in procedure ListConcat: invalid parameter list1");
        exit(1);
    } else if(list2 == NULL) {
        printf("Error in procedure ListConcat: invalid parameter list2");
        exit(1);
    } else {
        list1->tail->nextNode = list2->head;
        list2->head->prevNode = list2->tail;
        list1->tail = list2->tail;

        list1->length = list1->length + list2->length;

        /* free a list from the global array of lists */

        lists_free[list_idx] = list2->index;
        list_idx = list_idx - 1;
    }
}

/* Delete list. itemFree is a pointer to a routine 
 * that frees an item. It should be invoked 
 * (within ListFree) as: (*itemFree)(itemToBeFreed) */
void ListFree(LIST* list, void (*itemFree)(void*)){
    int currentIndex;
    if(list == NULL || list_idx == -1) {
        printf("Error in procedure ListFree: invalid parameter list");
        exit(1);
    }

    list->current = list->head;
    while(list->current != NULL) {
        /* call the itemFree function */
        (*itemFree)(list->current->item);

        /* free a node from the global array of nodes */
        currentIndex = list->current->index;

        nodes_free[node_idx] = currentIndex;
        node_idx = node_idx - 1;

        /* move forvard */
        list->current = list->current->nextNode;
    }

    list->current = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    /* free a list from the global array of lists */

    lists_free[list_idx] = list->index;
    list_idx = list_idx - 1;
}

/* Return last item and take it out of list. 
 * The current pointer shall be the new last item in the list */
void* ListTrim(LIST* list){
    void* currentItem;
    int currentIndex;

    if(list == NULL) {
        printf("Error in procedure ListTrim: invalid parameter list");
        exit(1);
        return NULL;
    } else if (list->length == 0) {
        printf("Error: can not remove from an empty list");
        exit(1);
        return NULL;
    }

    currentItem = list->current->item;
    currentIndex = list->current->index;

    if(list->length == 1) {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    } else {
        list->tail = list->tail->prevNode;
        list->tail->nextNode = NULL;
        list->current = list->tail;
    }

    nodes_free[node_idx] = currentIndex;
    node_idx = node_idx - 1;
    list->length = list->length - 1;

    return currentItem;
}
