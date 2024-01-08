#include "actions.h"
#include "helpers.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*  Executes given address book action.
    Returns 0 on success, -1 otherwise.  */
int exec_action(const char* action, Node** addressBook)
{
    if (strcmp(action, "display\n") == 0){
        print_records(*addressBook);
        return 0;
    }
    else if (strcmp(action, "add") == 0){
        return action_add(addressBook);
    }
    else if (strcmp(action, "delete") == 0){
        return action_delete(addressBook);
    }
    else if (strcmp(action, "find") == 0){
        return action_find(addressBook);
    }
    else if (strcmp(action, "exit\n") == 0){
        delete_all(addressBook);
        exit(0);
    }

    return -1;
}

/*  Executes delete action.
    Returns 0 on success, -1 otherwise.  */
int action_delete(Node** addressBook)
{
    char* param = strtok(NULL, " ");
    param[strlen(param) - 1] = '\0';

    if (strcmp(param, "all") == 0){
        delete_all(addressBook);
        return 0;
    }

    if(is_index(param) == -1){
        printf("Incorrect index.\n");
        return -1;
    }

    return delete_by_index(atoi(param), addressBook);
}

/*  Executes find action.
    Returns 0 on success (or if there were no matches), -1 otherwise.  */
int action_find(Node** addressBook)
{
    char* param = strtok(NULL, " ");
    param[strlen(param) - 1] = '\0';

    if (is_index(param) == -1){
        find_by_name(param, *addressBook);
        return 0;
    }

    Node* tmp = find_by_pos(atoi(param), *addressBook);

    if (tmp == NULL){
        printf("Index out of bounds.\n");
        return -1;
    }

    print_node(tmp);

    return 0;
}

/*  Executes add action.
    Returns 0 on success, -1 otherwise.  */
int action_add(Node** addressBook)
{
    char* name = strtok(NULL, " ");
    char* surname = strtok(NULL, " ");
    char* email = strtok(NULL, " ");
    char* phoneNum = strtok(NULL, " ");
    char* index = strtok(NULL, " ");

    if (name == NULL || surname == NULL || email == NULL || phoneNum == NULL)
        return -1;

    Node* temp = create_new_node(name, surname, email, " ");
    if (temp == NULL) return -1;

    if (index != NULL){
        index[strlen(index) - 1] = '\0';

        strncpy(temp->phoneNumber, phoneNum, sizeof(temp->phoneNumber));
        temp->phoneNumber[sizeof(temp->phoneNumber) - 1] = '\0';

        if(is_index(index) == -1){
            free(temp);
            printf("Incorrect index.\n");
            return -1;
        }

        return add_new_by_index(temp, atoi(index), addressBook);
    }

    phoneNum[strlen(phoneNum) - 1] = '\0';

    strncpy(temp->phoneNumber, phoneNum, sizeof(temp->phoneNumber));
    temp->phoneNumber[sizeof(temp->phoneNumber) - 1] = '\0';

    return add_new_to_end(temp, addressBook);
}

void print_actions_table()
{
    printf("------------------------------------  ACTIONS ------------------------------------\n");
    printf("display - Show all addresses in the address book\n");
    printf("add [name] [surname] [email] [phoneNumber] [index: optional] - Adds new address\n");
    printf("delete [index] | delete all - Deleted address\n");
    printf("find [index] | find [name] - Finds address\n");
    printf("exit - Exits the program\n");
    printf("------------------------------------  ACTIONS ------------------------------------\n");
}