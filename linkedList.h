#include "node.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
    extern void print_node(Node* node);
    extern void print_records(Node* head);
    extern int add_new_to_end(Node* node, Node** head);
    extern int add_new_by_index(Node* node, int idx, Node** head);
    extern int delete_by_index(int idx, Node** head);
    extern void delete_all(Node** head);
    extern Node* find_by_pos(int idx, Node* head);
    extern void find_by_name(char* name, Node* head);
    extern Node* create_new_node(char name[], char surname[], char email[], char phoneNumber[]);
#endif