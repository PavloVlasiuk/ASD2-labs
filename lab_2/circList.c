#include <stdio.h>
#include <stdlib.h>
#include "generateRandom.c"


typedef struct node { // structure for creating a node of circular linked list
    double data;
    struct node *next;
} node;

node *circListInit(double item) {
    node *head = malloc(sizeof(struct node));
    head->data = item;
    head->next = head;
    return head;
}

node *addItem(node *head, node *prevNode, double item) {
    node *newNode = malloc(sizeof(struct node));
    newNode->data = item;
    newNode->next = head;
    prevNode->next = newNode;
    return newNode;
}

node *createCircList(unsigned int n) {
    node *head = circListInit(generateRandom());
    node *prev = head;

    for (int i = 1; i < n; i++) {
        prev = addItem(head, prev, generateRandom());
    }

    node *tail = prev;
    return tail;
}

void printList(node *head) {
    node *current;
    current = head;

    do {
        printf("%.1lf\t", current->data);
        current = current->next;
    } while (current != head);

    printf("\n");
}

node *popFront(node *head, node *tail) {
    tail->next = head->next;
    head->next = NULL;
    return head;
}

node *push(struct node *node, struct node *tail) {
    node->next = tail->next;
    tail->next = node;
    return node;
}

node *displaceElements(struct node *tail, unsigned int k) {
    node *temp;
    node *newHead = tail->next;
    node *newTail = tail;

    for (int i = 0; i < k; i++) {
        temp = popFront(newHead, newTail);
        newTail = push(temp, newTail);
        newHead = newTail->next;
    }

    return newHead;
}

void listFree(node *head) {
    node *current = head;
    node *next;

    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);
}






