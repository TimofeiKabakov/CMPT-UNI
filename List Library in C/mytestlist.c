#include <stdio.h>
#include "list.h"
#include <stdlib.h>

void testParamFunct(void* param) {
    printf("Delete an item %d \n", *(int*)param);
}

void traverseArray(LIST* list) {
    if(list == NULL) {
        printf("Error: cannot traverse NULL");
        exit(1);
    } else {
        list->current = list->head;
        printf("The head of the list is %d \n",*(int*) list->head->item);
        while(list->current != list->tail) {
            printf("%d -> ", *(int*) list->current->item);
            /* move forvard */
            list->current = list->current->nextNode;
        }
        printf("%d -> ", *(int*) list->current->item);
    }
    printf("\n");
}

int main() {
    /*int iter;*/
    int item1 = 100;
    int item2 = 50;
    int item3 = 7;
    int item4 = 35;
    int item5 = 27;
    int item6 = 92;
    int item7 = 59;
    int item8 = 0;
    int item9 = 999;
    int item10 = 333;
    void* currentItem;
    LIST *newList, *newList2, *newList3, *newList4, *newList5,
 *newList6, *newList7, *newList8, *newList9, *newList10;


    newList = ListCreate();
    newList2 = ListCreate();
    newList3 = ListCreate();
    newList4 = ListCreate();
    newList5 = ListCreate();
    newList6 = ListCreate();
    newList7 = ListCreate();
    newList8 = ListCreate();
    newList9 = ListCreate();
    newList10 = ListCreate();

    ListAdd(newList, &item1);
    ListAdd(newList2, &item2);
    ListAdd(newList3, &item3);
    ListAdd(newList4, &item4);
    ListAdd(newList5, &item5);
    ListAdd(newList6, &item6);
    ListAdd(newList7, &item7);
    ListAdd(newList8, &item8);
    ListAdd(newList9, &item9);
    ListAdd(newList10, &item10);

    ListAdd(newList, &item1);
    ListAdd(newList2, &item2);
    ListAdd(newList3, &item3);
    ListAdd(newList4, &item4);
    ListAdd(newList5, &item5);


    printf("newList length is %d \n", newList->length);
    printf("newList2 length is %d \n", newList2->length);
    printf("newList3 length is %d \n", newList3->length);
    printf("newList4 length is %d \n", newList4->length);
    printf("newList5 length is %d \n", newList5->length);
    printf("newList6 length is %d \n", newList6->length);
    printf("newList7 length is %d \n", newList7->length);
    printf("newList8 length is %d \n", newList8->length);
    printf("newList9 length is %d \n", newList9->length);
    printf("newList10 length is %d \n", newList10->length);

    /* CHECK ALL ARRAYS */
    printf("\nTRAVERSE ARRAYS \n");
    traverseArray(newList);
    traverseArray(newList2);
    traverseArray(newList3);
    traverseArray(newList4);
    traverseArray(newList5);
    traverseArray(newList6);
    traverseArray(newList7);
    traverseArray(newList8);
    traverseArray(newList9);
    traverseArray(newList10);
    printf("END TRAVERSING ARRAYS \n\n");

    printf("list_idx is %d \n", list_idx);
    /*for (iter = 0; iter < MAX_LISTS; iter++) {
        printf("position at index %d is %d \n", iter, lists_free[iter]);
    }
    printf("\n");*/

    printf("node_idx is %d \n", node_idx);
    /*for (iter = 0; iter < MAX_NODES; iter++) {
        printf("position at index %d is %d \n", iter, nodes_free[iter]);
    }
    printf("\n");*/


    /* CLEAR ALL LISTS */
    ListFree(newList, testParamFunct);
    ListFree(newList2, testParamFunct);
    ListFree(newList3, testParamFunct);
    ListFree(newList4, testParamFunct);
    ListFree(newList5, testParamFunct);
    ListFree(newList6, testParamFunct);
    ListFree(newList7, testParamFunct);
    ListFree(newList8, testParamFunct);
    ListFree(newList9, testParamFunct);
    ListFree(newList10, testParamFunct);

    newList = ListCreate();
    newList2 = ListCreate();
    newList3 = ListCreate();
    newList4 = ListCreate();
    newList5 = ListCreate();
    newList6 = ListCreate();


    /* ListAdd() test cases*/
    printf("\nThis are the test cases for ListAdd(): \n");
    /* when the list is empty */
    ListAdd(newList, &item1);
printf("Head of the list is : %d, expected: 100\n",
 *(int*)newList->head->item);
    printf("Current item of the list is : %d, expected: 100\n",
 *(int*)newList->current->item);
    printf("Tail of the list is : %d, expected: 100\n",
 *(int*)newList->tail->item);

    /*when there's already an item in the list */
    ListAdd(newList, &item2);
    ListAdd(newList, &item3);
    ListAdd(newList, &item4);
    /* order should be 100 -> 50 -> 7 -> 35*/
    printf("Head of the list is : %d, expected: 100\n", 
*(int*)newList->head->item);
    printf("Current item of the list is : %d, expected: 35\n", 
*(int*)newList->current->item);
    printf("Tail of the list is : %d, expected: 35\n", 
*(int*)newList->tail->item);
    printf("The prev node of the current node is  %d, expected: 7\n", 
*(int*)newList->current->prevNode->item);


    /* ListInsert() test cases */
    printf("\nThis are the test cases for ListInsert(): \n");

    /* when the list is empty */
    ListInsert(newList2, &item1);
    printf("Head of the list is : %d, expected: 100\n", 
*(int*)newList2->head->item);
    printf("Current item of the list is : %d, expected: 100\n", 
*(int*)newList2->current->item);
    printf("Tail of the list is : %d, expected: 100\n", 
*(int*)newList2->tail->item);
    /*when there's already an item in the list */
    ListInsert(newList2, &item2);
    ListInsert(newList2, &item3);
    ListInsert(newList2, &item4);
    /* order should be 35 -> 7 -> 50 -> 100 */
    printf("Head of the list is : %d, expected: 35\n", 
*(int*)newList2->head->item);
    printf("Current item of the list is : %d, expected: 35\n", 
*(int*)newList2->current->item);
    printf("Tail of the list is : %d, expected: 100\n", 
*(int*)newList2->tail->item);
    printf("The next node of the current node is  : %d, expected: 7\n ", 
*(int*)newList2->current->nextNode->item);


    /* ListAppend() test cases */
    printf("\nThis are the test cases for ListAppend(): \n");
    ListAppend(newList, &item5);
    /* order should be 100 -> 50 -> 7 -> 35 -> 27*/
    printf("Current item of the list is : %d, expected: 27\n", 
*(int*)newList->current->item);
    printf("Tail of the list is : %d, expected: 27 \n", 
*(int*)newList->tail->item);
    printf("The prev node of the current node is  : %d, expected: 35 \n", 
*(int*)newList->current->prevNode->item);


    /* List Prepend() test cases */
    printf("\nThis are the test cases for ListPrepend(): \n");
    ListPrepend(newList, &item6);
    /* order should be 92->100 -> 50 -> 7 -> 35 -> 27*/
    printf("Current item of the list is : %d, expected: 92\n", 
*(int*)newList->current->item);
    printf("Head of the list is : %d, expected: 92 \n", 
*(int*)newList->head->item);
    printf("Tail of the list is : %d, expected: 27 \n", 
*(int*)newList->tail->item);
    printf("The next node of the current node is  : %d, expected: 100 \n", 
*(int*)newList->current->nextNode->item);


    /*Additional test cases for ListAdd() and ListInsert() now that the 
 * there are enough item in the list to manipulate */
  printf("\nThis are additional test cases for ListAdd() and ListInsert() \n");
    ListAdd(newList, &item7);
    /* order should be 92-> 59 -> 100 -> 50 -> 7 -> 35 -> 27*/
    printf("Current item of the list is : %d, expected: 59\n", 
*(int*)newList->current->item);
    printf("The next node of the current node is  : %d, expected: 100 \n", 
*(int*)newList->current->nextNode->item);
    printf("The prev node of the current node is  : %d, expected: 92 \n", 
*(int*)newList->current->prevNode->item);

    ListInsert(newList, &item8);
    /* order should be 92-> 0 -> 59 -> 100 -> 50 -> 7 -> 35 -> 27*/
    printf("Current item of the list is : %d, expected: 0\n", 
*(int*)newList->current->item);
    printf("Head of the list is : %d, expected: 92 \n", 
*(int*)newList->head->item);
    printf("The next node of the current node is  : %d, expected: 59 \n", 
*(int*)newList->current->nextNode->item);
    printf("The prev node of the current node is  : %d, expected: 92 \n", 
*(int*)newList->current->prevNode->item);



    ListAdd(newList3, &item1);
    ListAdd(newList3, &item2);
    ListAdd(newList3, &item3);
    ListAdd(newList3, &item4);
    ListAdd(newList3, &item4);
    ListAdd(newList3, &item4);

    /* ListRemove() test cases*/
    printf("\nThese are the test cases for ListRemove(): \n");
    currentItem = ListRemove(newList3);
    printf("Removed item from the list is: %d, expected: 35\n", 
*(int*)currentItem);
    currentItem = ListRemove(newList3);
    printf("Removed item from the list is: %d, expected: 35\n", 
*(int*)currentItem);
    /* order should be 100 -> 50 -> 7 -> 35 */
    ListPrev(newList3);
    ListPrev(newList3);
    currentItem = ListRemove(newList3);
    /* order should be 100 -> 7 -> 35 */
    printf("Removed item from the list is: %d, expected: 50\n", 
*(int*)currentItem);
    ListNext(newList3);
    currentItem = ListRemove(newList3);
    /* order should be 100 -> 7 */
    printf("Removed item from the list is: %d, expected: 35\n", 
*(int*)currentItem);
    printf("Head of the list is: %d, expected: 100\n", 
*(int*)newList3->head->item);
    printf("Current item of the list is: %d, expected: 7\n", 
*(int*)newList3->current->item);
    printf("Tail of the list is: %d, expected: 7\n", 
*(int*)newList3->tail->item);
    printf("The prev node of the current node is  %d, expected: 100\n", 
*(int*)newList3->current->prevNode->item);

    printf("\n");
    currentItem = ListRemove(newList3);
    /* order should be 100  */
    printf("Removed item from the list is: %d, expected: 7\n", 
*(int*)currentItem);
    printf("Head of the list is: %d, expected: 100\n", 
*(int*)newList3->head->item);
    printf("Current item of the list is: %d, expected: 100\n", 
*(int*)newList3->current->item);
    printf("Tail of the list is: %d, expected: 100\n", 
*(int*)newList3->tail->item);
    printf("Length of the list is: %d, expected: 1 \n", newList3->length);
    printf("\n");

    currentItem = ListRemove(newList3);
    /* order should be: empty list  */
    printf("Length of the list is: %d, expected: 0 \n", newList3->length);
    printf("\n");

    ListAdd(newList3, &item6);
    ListInsert(newList3, &item7);
    ListRemove(newList3);
    printf("Head of the list is: %d, expected: 92\n", 
*(int*)newList3->head->item);
    printf("Current item of the list is: %d, expected: 92\n", 
*(int*)newList3->current->item);
    printf("Tail of the list is: %d, expected: 92\n", 
*(int*)newList3->tail->item);
    printf("Length of the list is: %d, expected: 1 \n", newList3->length);

    /* Test case */
    printf("\n");
    ListRemove(newList3);
    ListAdd(newList3, &item6);
    ListInsert(newList3, &item7);
    ListNext(newList3);
    ListRemove(newList3);
    printf("Head of the list is: %d, expected: 59\n", 
*(int*)newList3->head->item);
    printf("Current item of the list is: %d, expected: 59\n", 
*(int*)newList3->current->item);
    printf("Tail of the list is: %d, expected: 59\n", 
*(int*)newList3->tail->item);
    printf("Length of the list is: %d, expected: 1 \n", newList3->length);

    /* Test cases for ListTrim */
    printf("\nThese are the test cases for ListTrim(): \n");

    ListAdd(newList4, &item6);
    ListAdd(newList4, &item7);
    currentItem = ListTrim(newList4);
    printf("Removed item from the list is: %d, expected: 59\n", 
*(int*)currentItem);
    currentItem = ListTrim(newList4);
    printf("Removed item from the list is: %d, expected: 92\n", 
*(int*)currentItem);

    /* Test cases for ListFree */
    printf("\nThese are the test cases for ListFree(): \n");
    ListAdd(newList4, &item6);
    ListAdd(newList4, &item7);
    ListAdd(newList4, &item7);
    ListAdd(newList4, &item7);
    ListAdd(newList4, &item7);
    ListAdd(newList4, &item7);

    printf("node_idx is %d \n", node_idx);
    ListFree(newList4, testParamFunct);
    printf("node_idx is %d \n", node_idx);

    /* Test cases for ListConcat */
    printf("\nThese are the test cases for ListConcat(): \n");

    ListInsert(newList5, &item7);
    ListInsert(newList5, &item6);
    ListInsert(newList5, &item9);
    ListAdd(newList6, &item7);
    ListAdd(newList6, &item7);
    ListAdd(newList6, &item2);

    printf("length list 5 %d \n", newList5->length);
    printf("length list 6 %d \n", newList6->length);

    traverseArray(newList5);
    traverseArray(newList6);
    ListConcat(newList5, newList6);

    printf("\nTraverse list 5 %d \n", newList5->index);
    traverseArray(newList5);
    printf("Head of the list is: %d, expected: 999\n", 
*(int*)newList5->head->item);
    printf("Current item of the list is: %d, expected: 333\n", 
*(int*)newList5->current->item);
    printf("Tail of the list is: %d, expected: 333\n", 
*(int*)newList5->tail->item);
    printf("Length of the list is: %d, expected: 6 \n", newList5->length);


    newList4 = ListCreate();
    printf("\nReinitialize list 4 %d \n", newList4->index);
    printf("length list 4 %d \n", newList4->length);
    ListAdd(newList4, &item10);
    traverseArray(newList4);
    printf("Head of the list is: %d, expected: 333\n", 
*(int*)newList4->head->item);
    printf("Current item of the list is: %d, expected: 333\n", 
*(int*)newList4->current->item);
    printf("Tail of the list is: %d, expected: 333\n", 
*(int*)newList4->tail->item);
    printf("Length of the list is: %d, expected: 1 \n", newList4->length);

    printf("\nTraverse list 5 %d \n", newList5->index);
    traverseArray(newList5);
    printf("Head of the list is: %d, expected: 999\n", 
*(int*)newList5->head->item);
    printf("Current item of the list is: %d, expected: 999\n", 
*(int*)newList5->current->item);
    printf("Tail of the list is: %d, expected: 333\n", 
*(int*)newList5->tail->item);
    printf("Length of the list is: %d, expected: 6 \n", newList5->length);

    printf("\nConcat list 5 and 4 \n");
    ListConcat(newList5, newList4);
    printf("Head of the list is: %d, expected: 999\n", 
*(int*)newList5->head->item);
    printf("Current item of the list is: %d, expected: 333\n", 
*(int*)newList5->current->item);
    printf("Tail of the list is: %d, expected: 333\n", 
*(int*)newList5->tail->item);
    printf("Length of the list is: %d, expected: 7 \n", newList5->length);

    return 0;
}
