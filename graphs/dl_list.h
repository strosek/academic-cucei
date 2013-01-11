/*  Doubly linked list */
/*
    Copyright (c) 2013 Erick Daniel Corona <edcoronag@gmail.com>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdlib.h>

const int k_dataSize = sizeof(int) / sizeof(char);


typedef struct n {
    char data[k_dataSize];
    struct n* next;
    struct n* prev;
} Node;

typedef Node * List;

size_t size();
Data   front(List list);
Data   back(List list);
Node*  at(List list, size_t position);
Node*  search(List list, const Data* element);
int    isEmpty(List list);
void   print();

/* Modifiers */
List   initialize();
List   clear(List list);
List   pushFront(List list, const Data* element);
List   pushBack(List list, const Data* element);
List   popFront(List list);
List   popBack(List list);
List   insert(List list, Node* position, const Data* element);
List   insertAt(List list, size_t position, const Data* element);
List   erase(List list, Node* position);
List   eraseAt(List list, size_t position);
List   removeNode(List list, const Data* key);
List   sort(List list);

