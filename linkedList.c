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

Node* g_head = NULL;
int g_length = 0;

// Prints single node
extern void print_node(Node* node)
{
    printf("| %s | %s | %s | %s |\n", node->name, node->surname, node->email, node->phoneNumber);
}

// Prints records from the linked list
extern void print_records()
{
    if (g_head == NULL){
        printf("No records in the address book found.\n");
        return;
    }
    
    Node* curr = g_head;

    while(curr != NULL){
        print_node(curr);
        curr = curr->next;
    }
}

// Adds new node to the end of the linked list
extern int add_new_to_end(Node* node)
{
    if (node == NULL) return -1;

    if (g_head == NULL){
        g_head = node;

        g_length++;

        return 0;
    }

    Node* curr = g_head;

    while(curr->next != NULL){
        curr = curr->next;
    }

    curr->next = node;
    g_length++;

    return 0;
}

// Adds new Node to the specified index of the linked list
extern int add_new_by_index(Node* node, int idx)
{
    if (node == NULL) return -1;
    if (idx < 0 || idx > g_length + 1) return -2;

    if (idx == 0){
        node->next = g_head;
        g_head = node;
        return 0;
    }

    Node* curr = g_head;
    int currIdx = 0;

    while(currIdx < idx - 1)
    {
        g_head = g_head->next;
        currIdx++;
    }

    node->next = g_head->next;
    g_head->next = node;

    g_head = curr;
    g_length++;

    return 0;
}

// Deletes node by the specified index
extern int delete_by_index(int idx)
{
    if (idx < 0 || idx > g_length + 1) return -2;

    if (idx == 0){
        Node* nextNodes = g_head->next;
        free(g_head);
        g_head = nextNodes;
        return 0;
    }

    int currIdx = 0;

    while(currIdx < idx - 1){
        g_head = g_head->next;
        currIdx++;
    }

    Node* nextNodes = g_head->next->next;
    free(g_head->next);
    g_head->next = nextNodes;

    return 0;
}

// Deletes all nodes from the linked list
extern void delete_all()
{
    while(g_head){
        Node* temp = g_head;
        g_head = g_head->next;
        free(temp);
    }
}

// Finds node by index
extern Node* find_by_pos(int idx)
{
    if (idx < 0 || idx > g_length + 1) return NULL;

    int currIdx = 0;

    Node* curr = g_head;

    while(currIdx < idx){
        curr = curr->next;
        currIdx++;
    }

    return curr;
}

// Finds node by name property
extern Node* find_by_name(char* name)
{
    Node* curr = g_head;

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