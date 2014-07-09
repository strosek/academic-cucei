/*  Doubly linked list function implementation */

#include "dl_list.h"

#include <stdio.h>


Data_t front(Node_t * list) {
  return list->data;
}

Data_t back(Node_t * list) {
  return list->prev->data;
}

Node_t * at(Node_t * list, size_t position) {
  if (list != NULL) {
    Node_t * temp = list;
    size_t nodeNo = 0;
    while (nodeNo <= position && temp->next != NULL) {
      temp = temp->next;
      ++nodeNo;
    }

    return temp;
  }
  return NULL;
}

Node_t * search(Node_t * list, Data_t element) {
  Node_t * temp = list;

  while (temp->data != element) {
    temp = temp->next;
  }

  return temp;
}

int isEmpty(Node_t * list) {
  return list == NULL;
}

void print(Node_t * list) {
  if (list != NULL) {
    Node_t * temp = list;
    size_t nodeNo = 0;
    while (temp->next != list && nodeNo != 0) {
      printf("%lu: %d", nodeNo, temp->data);
      ++nodeNo;
    }
  }
}


/* Modifiers */
Node_t * initialize() {
  return NULL;
}

Node_t * clear(Node_t * list) {
  if (list != NULL) {
    Node_t * temp = list;
    Node_t * tempNext = temp->next;
    while (temp != list) {
      free(temp);
      temp = tempNext;
      tempNext = tempNext->next;
    }
  }

  return NULL;
}

Node_t * pushFront(Node_t * list, Data_t element) {
  Node_t * newNode = (Node_t *)malloc(sizeof(Node_t));
  newNode->data = element;

  if (isEmpty(list)) {
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
  }
  else {
    newNode->next = list;
    newNode->prev = list->prev;
    newNode->next->prev = newNode;
    newNode->prev->next = newNode;
  }

  return newNode;
}

Node_t * pushBack(Node_t * list, Data_t element) {
  Node_t * newNode = (Node_t *)malloc(sizeof(Node_t));
  newNode->data = element;

  if (isEmpty(list)) {
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
  }
  else {
    list->prev->next = newNode;
    newNode->next = list;
    newNode->prev = list->prev;
    list->prev = newNode;
  }

  return list;
}

Node_t * popFront(Node_t * list) {
  Node_t * temp = list->next;
  list->next->prev = list->prev;
  list->prev->next = list->next;
  free(list);
  return temp;
}

Node_t * popBack(Node_t * list) {
  Node_t * temp = list->prev;
  list->prev->prev->next = list;
  list->prev = list->prev->prev;
  free(temp);
  return list;
}

Node_t * insert(Node_t * list, Node_t * position, Data_t element) {
  Node_t * temp = list;

  if (position == list) {
    pushFront(list, element);
  }
  while (temp != position && temp != list) {
    temp = temp->next;
  }
  return list;
}

Node_t * insertAt(Node_t * list, size_t position, Data_t element) {
  return list;
}

Node_t * erase(Node_t * list, Node_t * position) {
  return list;
}

Node_t * eraseAt(Node_t * list, size_t position) {
  return list;
}

Node_t * removeNode(Node_t * list, Data_t key) {
  return list;
}

Node_t * sort(Node_t * list) {
  return list;
}

