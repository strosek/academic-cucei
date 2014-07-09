/*  Doubly linked list */

#include <stdlib.h>


typedef int Data_t;

typedef struct n {
  Data_t data;
  struct n* next;
  struct n* prev;
} Node_t;



Data_t   front(Node_t * list);
Data_t   back(Node_t * list);
Node_t * at(Node_t * list, size_t position);
Node_t * search(Node_t * list, Data_t element);
int      isEmpty(Node_t * list);
void     print();


/* Modifiers */
Node_t * initialize();
Node_t * clear(Node_t * list);
Node_t * pushFront(Node_t * list, Data_t element);
Node_t * pushBack(Node_t * list, Data_t element);
Node_t * popFront(Node_t * list);
Node_t * popBack(Node_t * list);
Node_t * insert(Node_t * list, Node_t* position, Data_t element);
Node_t * insertAt(Node_t * list, size_t position, Data_t element);
Node_t * erase(Node_t * list, Node_t* position);
Node_t * eraseAt(Node_t * list, size_t position);
Node_t * removeNode(Node_t * list, Data_t key);
Node_t * sort(Node_t * list);

