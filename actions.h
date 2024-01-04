#include "linkedList.h"

#ifndef ACTIONS_H
#define ACTIONS_H
    int exec_action(const char* action, Node** addressBook);
    int action_delete(Node** addressBook);
    int action_add(Node** addressBook);
    int action_find(Node** addressBook);
    void print_actions_table();
#endif