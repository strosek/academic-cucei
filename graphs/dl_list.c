/*  Doubly linked list function implementation */

#include "dl_list.h"

#include <stdio.h>

static size_t g_listSize;

size_t size() {
    return g_listSize;
}

Data front(List list) {
    return list->data;
}

Data back(List list) {
    return list->prev->data;
}

Node* at(List list, size_t position) {
    if (position < g_listSize) {
        Node* temp = list;
        size_t nodeNo = 0;
        while (nodeNo < position) {
            temp = temp->next;
            ++nodeNo;
        }
        return temp;
    }
    return NULL;
}

Node* search(List list, const Data* element) {
    Node* temp = list;

    while (temp->data != *element) {
        temp = temp->next;
    }
    return temp;
}

int isEmpty(List list) {
    return list == NULL;
}

void print(List list) {
    Node* temp = list;
    size_t nodeNo = 0;
    while (temp->next != list && nodeNo != 0) {
        printf("%lu: %d", nodeNo, temp->data);
        ++nodeNo;
    }
}

/* Modifiers */
List initialize() {
    g_listSize = 0;
    return NULL;
}

List clear(List list) {
    Node* temp = list;
    Node* tempNext = temp->next;
    while (temp != list) {
        free(temp);
        temp = tempNext;
        tempNext = tempNext->next;
        --g_listSize;
    }
    return NULL;
}

List pushFront(List list, const Data* element) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = *element;

    if (isEmpty(list)) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }
    else {
        list->next->prev = newNode;
        newNode->next = list->next;
        list->next = newNode;
        newNode->prev = list;
    }

    return list;
}

List pushBack(List list, const Data* element) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = *element;

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

List popFront(List list) {
    Node* temp = list->next;
    list->next->prev = list->prev;
    list->prev->next = list->next;
    free(list);
    return temp;
}

List popBack(List list) {
    Node* temp = list->prev;
    list->prev->prev->next = list;
    list->prev = list->prev->prev;
    free(temp);
    return list;
}

List insert(List list, Node* position, const Data* element) {
    Node* temp = list;

    if (position == list) {
        pushFront(list, element);
    }
    while (temp != position && temp != list) {
        temp = temp->next;
    }
    return list;
}

List insertAt(List list, size_t position, const Data* element) {
    return list;
}

List erase(List list, Node* position) {
    return list;
}

List eraseAt(List list, size_t position) {
    return list;
}

List removeNode(List list, const Data* key) {
    return list;
}

List sort(List list) {
    return list;
}

