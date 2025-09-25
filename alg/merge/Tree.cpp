#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Falha ao alocar memória!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void print_tree_in_order(Node* root) {
    if (root == NULL) {
        return;
    }
    print_tree_in_order(root->right);
    printf("%d ", root->data);
    print_tree_in_order(root->left);
}

void free_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    Node *root = create_node(10);

    root->left = create_node(5);
    root->right = create_node(15);
    root->left->left = create_node(2);
    root->left->right = create_node(7);

    printf("Percorrendo a árvore (em-ordem): ");
    print_tree_in_order(root);
    printf("\n");

    free_tree(root);
    printf("Memória da árvore liberada.\n");

    return 0;
}
