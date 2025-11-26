#include "List.h"
#include <stdlib.h>

int addToList(List * list, void * data, int (*cmp)(void *, void *)) {
    Node * newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
        return 1;
    }

    Node * curr = *list;
    Node * prev = NULL;
    while (curr != NULL) {
        if(cmp(curr->data, data) == 0) {
            free(newNode);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = newNode;
    return 1;
}

void freeList(List list) {
    if(list != NULL) {
        Node * curr = list;
        Node * aux;
        while (curr->next != NULL) {
            free(curr->data);
            aux = curr->next;
            free(curr);
            curr = aux;
        }
        free(curr->data);
        free(curr);
    }
}