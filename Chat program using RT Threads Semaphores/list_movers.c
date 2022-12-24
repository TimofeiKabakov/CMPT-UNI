#include <stdio.h>
#include "list.h"

void* ListFirst(LIST* list) {
    /* Returns a pointer to the first item in list 
 * and makes the first item the current item */
    if(list == NULL) {  
        printf("Error in procedure ListFirst: invalid parameter list");
        return NULL;
    }
    list->current = list->head;
    return list->head->item;
}

/* Returns a pointer to the last item in list 
 * and makes the last item the current one */
void* ListLast(LIST* list) {
    if(list == NULL || list->length == 0) {  
        printf("Error in procedure ListLast: invalid parameter list");
        return NULL;
    }
    list->current = list->tail;
    return list->tail->item;
}

/* Advances the list's current node by one,
 * and returns a pointer to the new current item. 
If this operation attempts to advances the 
current item beyond the end of the list, a NULL pointer is returned */
void* ListNext(LIST* list) {
    if(list == NULL || list->current == list->tail) {  
        printf("Error in procedure ListNext: invalid parameter list");
        return NULL;
    }
    list->current = list->current->nextNode;
    return list->current->item;
}

/* Backs up the list's current node by one, and 
 * returns a pointer to the new current item. 
If this operation attempts to back up the 
current item beyond the start of the list, a NULL pointer is returned */
void* ListPrev(LIST* list) {
    if(list == NULL || list->current == list->head) { 
        printf("Error in procedure ListPrev: invalid parameter list");
        return NULL;
    }
    list->current = list->current->prevNode;
    return list->current->item;
}

/* Returns a pointer to the current item in list */
void* ListCurr(LIST* list) {
    if(list == NULL) {  
        printf("Error in procedure ListCurr: invalid parameter list");
        return NULL;
    }
    return list->current->item;
}

/* Returns the number of items in list */
int ListCount(LIST* list) {
    if(list == NULL) { 
        printf("Error in procedure ListCount: invalid parameter list");
        return 0;
    }
    return list->length;
}


/* Searches list starting at the current item until the end is 
 * reached or a match is found. In this context, a match is 
determined by the comparator parameter. This parameter is a 
pointer to a routine that takes as its first argument an item pointer, 
and as its second argument comparisonArg. Comparator returns 0 
if the item and comparisonArg don't match (i.e. didn't find it), or 1 
if they do (i.e. found it). Exactly what constitutes a 
match is up to the implementor of comparator. If a match is found, the current
pointer is left at the matched item and the pointer 
to that item is returned. If no match is found, 
the current pointer is left at 
the end of the list and a NULL pointer is returned.*/
void* ListSearch(LIST* list, 
int (*comparator)(void*, void*), void* comparisonArg){
    if(list == NULL) {  
        printf("Error in procedure ListSearch: invalid parameter list");
        return NULL;
    }

    while(list->current != NULL) {
        if((*comparator)(list->current->item, comparisonArg) == 1) {
            return list->current;
        }
        /* move forvard */
        list->current = list->current->nextNode;
    }

    list->current = list->tail;
    return NULL;
}
