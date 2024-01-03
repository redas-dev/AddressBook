#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
    char* name;
    char* surname;
    char* email;
    char* phoneNumber;

    struct Node* next;
} Node;

int g_length = 0;

// Prints single node
extern void print_node(Node* node)
{
    printf("| %s | %s | %s | %s |\n", node->name, node->surname, node->email, node->phoneNumber);
}

// Prints records from the linked list
extern void print_records(Node* head)
{
    if (head == NULL){
        printf("No records in the address book found.\n");
        return;
    }
    
    Node* curr = head;

    while(curr != NULL){
        print_node(curr);
        curr = curr->next;
    }
}

// Adds new node to the end of the linked list
extern int add_new_to_end(Node* node, Node** head)
{
    if (node == NULL) return -1;

    if (*head == NULL){
        *head = node;

        g_length++;

        return 0;
    }

    Node* curr = *head;

    while(curr->next != NULL){
        curr = curr->next;
    }

    curr->next = node;
    g_length++;

    return 0;
}

// Adds new Node to the specified index of the linked list
extern int add_new_by_index(Node* node, int idx, Node** head)
{
    if (node == NULL) return -1;
    if (idx < 0 || idx > g_length + 1) return -2;

    if (idx == 0){
        node->next = *head;
        *head = node;
        return 0;
    }

    Node* curr = *head;
    int currIdx = 0;

    while(currIdx < idx - 1)
    {
        curr = curr->next;
        currIdx++;
    }

    node->next = curr->next;
    curr->next = node;

    g_length++;

    return 0;
}

// Deletes node by the specified index
extern int delete_by_index(int idx, Node** head)
{
    if (idx < 0 || idx > g_length + 1) return -2;

    if (idx == 0){
        Node* nextNodes = (*head)->next;
        free(*head);
        *head = nextNodes;
        return 0;
    }

    int currIdx = 0;

    while(currIdx < idx - 1){
        *head = (*head)->next;
        currIdx++;
    }

    Node* nextNodes = (*head)->next->next;
    free((*head)->next);
    (*head)->next = nextNodes;

    return 0;
}

// Deletes all nodes from the linked list
extern void delete_all(Node** head)
{
    while(*head){
        Node* temp = *head;
        *head = (*head)->next;
        free(temp->name);
        free(temp->email);
        free(temp->surname);
        free(temp->phoneNumber);
        free(temp);
    }
}

// Finds node by index
extern Node* find_by_pos(int idx, Node* head)
{
    if (idx < 0 || idx > g_length + 1) return NULL;

    int currIdx = 0;

    Node* curr = head;

    while(currIdx < idx){
        curr = curr->next;
        currIdx++;
    }

    return curr;
}

// Finds node by name property
extern Node* find_by_name(char* name, Node* head)
{
    Node* curr = head;

    while(curr != NULL){
        if (strcmp(name, curr->name) == 0){
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

extern Node* create_new_node(char* name, char* surname, char* email, char* phoneNumber)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) return NULL;

    newNode->name = name;
    newNode->surname = surname;
    newNode->email = email;
    newNode->phoneNumber = phoneNumber;
    newNode->next = NULL;

    return newNode;
}