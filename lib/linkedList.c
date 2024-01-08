#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

// Total length of the list
int g_length = 0;

// Prints single Node
extern void print_node(Node* node)
{
    int fullLen = strlen(node->name) + 3 + strlen(node->surname) + 3 + strlen(node->email) + 3 + strlen(node->phoneNumber) + 4;

    for(int i = 0; i < fullLen; i++)
        putc('-', stdout);
    putc('\n', stdout);

    printf("| %s | %s | %s | %s |\n", node->name, node->surname, node->email, node->phoneNumber);

    for(int i = 0; i < fullLen; i++)
        putc('-', stdout);
    putc('\n', stdout);
}

// Prints Nodes from the linked list
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

/*  Adds new `Node*` to the end of the linked list.
    Returns 0 on success, -1 otherwise.  */
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

/*  Adds new `Node*` to the specified index of the linked list.
    Returns 0 on success, -1 otherwise.  */
extern int add_new_by_index(Node* node, int idx, Node** head)
{
    if (node == NULL) return -1;
    if (idx < 0 || idx > g_length + 1) return -1;

    if (idx == 0){
        node->next = *head;
        *head = node;
        g_length++;
        return 0;
    }

    Node* curr = *head;
    
    for (int i = 0; curr != NULL && i < idx - 1; i++)
        curr = curr->next;

    if (curr == NULL) return -1;

    node->next = curr->next;
    curr->next = node;

    g_length++;

    return 0;
}

/*  Deletes Node by the specified index.
    Returns 0 on success, -1 otherwise. */
extern int delete_by_index(int idx, Node** head)
{
    if (*head == NULL) return -1;
    if (idx < 0 || idx >= g_length + 1) return -1;

    Node* temp = *head;

    if (idx == 0){
        *head = temp->next;
        free(temp);

        g_length--;

        return 0;
    }

    for (int i = 0; temp != NULL && i < idx - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) return -1;

    Node* nextNodes = temp->next->next;

    free(temp->next);

    temp->next = nextNodes;

    g_length--;

    return 0;
}

// Deletes all Nodes from the linked list
extern void delete_all(Node** head)
{
    while(*head){
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    g_length = 0;
}

/*  Finds `Node*` by index.
    Returns the `Node*` on success, `NULL` otherwise.  */
extern Node* find_by_pos(int idx, Node* head)
{
    if (head == NULL) return NULL;
    if (idx < 0 || idx > g_length) return NULL;

    int currIdx = 0;

    Node* curr = head;

    while(currIdx < idx){
        curr = curr->next;
        currIdx++;
    }

    return curr;
}

/*  Finds `Node*` by name property.
    Returns the `Node*` on success, `NULL` otherwise.  */
extern void find_by_name(char* name, Node* head)
{
    Node* curr = head;

    while(curr != NULL){
        if (strcmp(name, curr->name) == 0){
            print_node(curr);
        }
        curr = curr->next;
    }
}

/*  Creates a new `Node*` with the given params.
    Returns the `Node*` on success, `NULL` otherwise.  */
extern Node* create_new_node(char* name, char* surname, char* email, char* phoneNumber)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) return NULL;

    strncpy(newNode->name, name, sizeof(newNode->name));
    newNode->name[sizeof(newNode->name) - 1] = '\0';

    strncpy(newNode->surname, surname, sizeof(newNode->surname));
    newNode->name[sizeof(newNode->surname) - 1] = '\0';

    strncpy(newNode->email, email, sizeof(newNode->email));
    newNode->email[sizeof(newNode->email) - 1] = '\0';

    strncpy(newNode->phoneNumber, phoneNumber, sizeof(newNode->phoneNumber));
    newNode->name[sizeof(newNode->phoneNumber) - 1] = '\0';

    newNode->next = NULL;

    return newNode;
}