#ifndef MAX_SIZE
#define MAX_SIZE 64
#endif

#ifndef NODE_H
#define NODE_H
    typedef struct Node{
        char name[MAX_SIZE];
        char surname[MAX_SIZE];
        char email[MAX_SIZE * 2];
        char phoneNumber[MAX_SIZE];

        struct Node* next;
    } Node;
#endif