/*  Doubly linked list definition */
/*
 *  Copyright (c) 2013 Erick Daniel Corona <edcoronag@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <limits.h>

typedef struct n {
    int       data;
    struct n* next;
    struct n* prev;
} Node_t;

typedef Node_t* List_t;

const int NOT_FOUND_ERROR = INT_MAX;

int      front(List_t list);
int      back(List_t list);
Node_t*  at(List_t list, size_t position);
Node_t*  searchLeft(List_t list, int key);
Node_t*  searchRight(List_t list, int key);
int      isEmpty(List_t list);
void     print(List_t list);

/* Modifiers */
List_t initialize(List_t list);
List_t clear(List_t list);
List_t pushFront(List_t list, int element);
List_t pushBack(List_t list, int element);
List_t popFront(List_t list);
List_t popBack(List_t list);
List_t insert(List_t list, Node_t* position, int element);
List_t insertAt(List_t list, size_t position, int element);
List_t erase(List_t list, Node_t* position);
List_t eraseAt(List_t list, size_t position);
List_t removeLeft(List_t list, int key);
List_t removeRight(List_t list, int key);
List_t removeNode_t(List_t list, int key);
List_t sort(List_t list);

