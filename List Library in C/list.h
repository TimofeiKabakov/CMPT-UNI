# define MAX_LISTS 100  /* max amount of lists in the library */
# define MAX_NODES 1024  /* max amount of nodes in a list */

/*define the structure for the node objects*/
typedef struct NODE {
    void*  item;
    struct NODE* nextNode;
    struct NODE* prevNode;
    int index;
} NODE;

/*define the structure fot the list (double-linked list) object*/
typedef struct LIST {
    int length;
    struct NODE* current; /*a pointer to a current*/
    struct NODE* head; /*a pointer to the head of the list*/
    struct NODE* tail; /*a pointer to the tail of the list*/
    int index;
} LIST;

/*define all the function headers*/
LIST* ListCreate();
int ListCount(LIST* list);
void* ListFirst(LIST* list);
void* ListLast(LIST* list);
void* ListNext(LIST* list);
void* ListPrev(LIST* list);
void* ListCurr(LIST* list);
int ListAdd(LIST* list, void* item);
int ListInsert(LIST* list, void* item);
int ListAppend(LIST* list, void* item);
int ListPrepend(LIST* list, void* item);
void* ListRemove(LIST* list);
void ListConcat(LIST* list1,LIST* list2);
void ListFree(LIST* list, void (*itemFree)(void*));
void* ListTrim(LIST* list);
void* ListSearch(LIST* list, 
int (*comparator)(void*, void*), void* comparisonArg);

extern LIST lists[MAX_LISTS];
extern NODE nodes[MAX_NODES];
extern int lists_free[MAX_LISTS];
extern int nodes_free[MAX_NODES];
extern int list_idx;
extern int node_idx;
