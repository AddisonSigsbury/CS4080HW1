#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *prev;
    struct Node *next;
};

struct Node* createNode(const char *str) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Can't allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->data = (char*)malloc(strlen(str) + 1);
    if (newNode->data == NULL) {
        perror("Can't allocate memory for string");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->data, str);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node **head, struct Node *prevNode, const char *str) {
    struct Node *newNode = createNode(str);

    if (prevNode == NULL) {
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        newNode->next = *head;
        *head = newNode;
    } else {
        newNode->next = prevNode->next;
        if (prevNode->next != NULL) {
            prevNode->next->prev = newNode;
        }
        prevNode->next = newNode;
        newNode->prev = prevNode;
    }
}

struct Node* find(struct Node *head, const char *str) {
    struct Node *current = head;
    while (current != NULL) {
        if (strcmp(current->data, str) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void delete(struct Node **head, struct Node *nodeToDelete) {
    if (nodeToDelete == NULL) {
        return;
    }

    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    } else {
        
        *head = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }

    free(nodeToDelete->data);
    free(nodeToDelete);     
}


void dump(struct Node *head) {
    struct Node *current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%s <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}


void freeList(struct Node **head) {
    struct Node *current = *head;
    while (current != NULL) {
        struct Node *nextNode = current->next;
        free(current->data);
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

int main(int argc, const char* argv[]) {
    printf("Hello, World!\n");

    struct Node* list = NULL;
    insert(&list, NULL, "four");
    insert(&list, NULL, "one");
    insert(&list, find(list, "one"), "two");
    insert(&list, find(list, "two"), "three");

    dump(list);

    printf("-- delete three --\n");
    delete(&list, find(list, "three"));
    dump(list);

    printf("-- delete one --\n");
    delete(&list, find(list, "one"));
    dump(list);
    
    freeList(&list);

    return 0;
}