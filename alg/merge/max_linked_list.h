#ifndef max_linked_list_H
#define max_linked_list_H

typedef struct Node {
    char* nota1;
    struct Node* next;
    struct Node* prev;
} Node;

Node* removerNodePorPosicao(Node* head);

#endif

