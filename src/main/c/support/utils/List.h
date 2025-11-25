#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct Node * List;

typedef struct Node {
    void * data;
    struct Node * next;
} Node;

int addToList(List * list, void * data, int (*cmp)(void *, void *));
void freeList(List list);

#endif