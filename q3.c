#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

// Linked list node structure
typedef struct Node {
    char line[BUFFER_SIZE];
    struct Node* next;
} Node;

// Function to add a line to the linked list
Node* addToList(Node* head, const char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->line, line);
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return head;
}

// Function to print the contents of the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s", current->line);
        current = current->next;
    }
}

// Function to free the memory allocated for the linked list
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Invalid value of n\n");
        return 1;
    }

    Node* head = NULL;
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, stdin) != NULL) {
        head = addToList(head, line);

        // Remove the first node if the list becomes longer than n
        if (n > 0) {
            Node* current = head;
            Node* prev = NULL;
            int count = 0;
            while (current != NULL) {
                count++;
                if (count > n) {
                    if (prev == NULL) {
                        head = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    free(current);
                    break;
                }
                prev = current;
                current = current->next;
            }
        }
    }

    printList(head);

    freeList(head);

    return 0;
}
