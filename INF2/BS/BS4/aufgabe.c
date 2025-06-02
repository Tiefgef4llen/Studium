#include <malloc.h>

typedef struct node {
    node_t* next;
    int data;
} node_t;

node_t* addFront(node_t* anchor, int data) {
    node_t* newNode = malloc(sizeof(node_t));
    newNode->data = data;

    newNode->next = anchor;

    return newNode;
}

void removeEnd(node_t* anchor) {
    if(anchor == NULL) return;

    node_t* pNode = anchor;
    while(pNode->next != NULL) {
        pNode = pNode->next;
    }
    pNode = NULL;
    free(pNode);
}

