#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Binary tree node
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* newNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// Parallel sum with step printing
int parallelSum(Node* root) {
    if (root == NULL) return 0;

    int sumLeft = 0, sumRight = 0;

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            if (root->left) {
                #pragma omp task shared(sumLeft)
                {
                    int thread = omp_get_thread_num();
                    printf("Thread %d visiting left child %d\n", thread, root->left->value);
                    sumLeft = parallelSum(root->left);
                }
            }

            if (root->right) {
                #pragma omp task shared(sumRight)
                {
                    int thread = omp_get_thread_num();
                    printf("Thread %d visiting right child %d\n", thread, root->right->value);
                    sumRight = parallelSum(root->right);
                }
            }
        }
    }

    int total = root->value + sumLeft + sumRight;
    int thread = omp_get_thread_num();
    printf("Thread %d computed sum at node %d = %d\n", thread, root->value, total);
    return total;
}

int main() {
    omp_set_num_threads(4); // set number of threads

    Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(20);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(15);
    root->right->right = newNode(25);

    int result = parallelSum(root);
    printf("\nFinal sum of all nodes = %d\n", result);
    return 0;
}