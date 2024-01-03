#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

#define FILENAME "addresses.csv"
#define PROGRAM_NOT_ENDED 1

Node* load_init_data();
char* strdup(const char* c);
void parse_init_data(FILE* fin, Node** adressBook);
void print_actions_table();
int exec_action(const char* action, Node** addressBook);
int is_index(const char* inp);
int action_delete(Node** addressBook);
int action_add(Node** addressBook);
int action_find(Node** addressBook);

int main(void)
{
    printf("------ LOADING DATA FROM ADDRESSES.CSV ------\n");

    Node* addressBook = load_init_data();
    if (addressBook == NULL) {
        printf("COULDN'T LOAD DATA CORRECTLY. CAN CONTINUE WITHOUT IT.");
    }

    printf("------ LOADING DATA FROM ADDRESSES.CSV ------\n");

    print_actions_table();
    char input[200];

    while(PROGRAM_NOT_ENDED){
        printf("- ");
        fgets(input, sizeof(input), stdin);

        char* action = strtok(input, " ");

        int code = exec_action(action, &addressBook);

        if (code != 0) printf("Action failed, try again.\n");
    }

    return 0;
}

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

int action_find(Node** addressBook)
{
    char* param = strtok(NULL, " ");
    param[strlen(param) - 1] = '\0';

    if (is_index(param) == -1){
        Node* tmp = find_by_name(param, *addressBook);

        if (tmp == NULL){
            printf("No adress with name %s\n", param);
            return 0;
        }

        print_node(tmp);
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

int action_add(Node** addressBook)
{
    char* name = strtok(NULL, " ");
    char* surname = strtok(NULL, " ");
    char* email = strtok(NULL, " ");
    char* phoneNum = strtok(NULL, " ");
    char* index = strtok(NULL, " ");

    Node* temp = create_new_node(strdup(name), strdup(surname), strdup(email), NULL);
    if (temp == NULL) return -1;

    if (index != NULL){
        index[strlen(index) - 1] = '\0';
        temp->phoneNumber = strdup(phoneNum);

        if(is_index(index) == -1){
            printf("Incorrect index.\n");
            return -1;
        }

        return add_new_by_index(temp, atoi(index), addressBook);
    }

    phoneNum[strlen(phoneNum) - 1] = '\0';
    temp->phoneNumber = strdup(phoneNum);

    return add_new_to_end(temp, addressBook);
}

void print_actions_table()
{
    printf("------------------------------------  ACTIONS ------------------------------------\n");
    printf("display - Show all addresses in the address book\n");
    printf("add [name] [surname] [email] [phoneNumber] [index: optional] - Adds new address\n");
    printf("delete [index] | delete all - Deleted address\n");
    printf("find [index] | find [name] - Finds address\n");
    printf("exit - exits the program\n");
    printf("------------------------------------  ACTIONS ------------------------------------\n");
}

char* get_full_path(const char* homeDir)
{
    int fullLen = strlen(homeDir) + strlen(FILENAME) + 2;

    char* fullPath = (char*)malloc(fullLen * sizeof(char));

    if (fullPath == NULL) return NULL;

    sprintf(fullPath, "%s/%s", homeDir, FILENAME);

    return fullPath;
}

Node* load_init_data()
{
    char* homeDir = getenv("HOME");
    char* fullPath = get_full_path(homeDir);

    if (fullPath == NULL) return NULL;

    FILE *fin;

    if ((fin = fopen(fullPath, "r")) == NULL){
        printf("%s was not found in %s. Continuing without it.\n", FILENAME, homeDir);
        return NULL;
    }

    Node* adrBook = NULL;

    parse_init_data(fin, &adrBook);

    free(fullPath);
    fclose(fin);

    return adrBook;
}

void parse_init_data(FILE* fin, Node** addressBook)
{
    char buffer[200];

    while(fgets(buffer, sizeof(buffer), fin) != NULL){
        buffer[strlen(buffer) - 1] = '\0';  // Remove trailing \n

        char* name;
        char* surname;
        char* email;
        char* phoneNumber;

        name = strtok(buffer, ",");
        surname = strtok(NULL, ",");
        email = strtok(NULL, ",");
        phoneNumber = strtok(NULL, ",");

        Node* temp = create_new_node(strdup(name), strdup(surname), strdup(email), strdup(phoneNumber));

        if (temp == NULL) continue;

        add_new_to_end(temp, addressBook);
    }
}

// Duplicate the string
char* strdup(const char *c)
{
    int len = strlen(c) + 1;
    char* dup = (char*)malloc(len * sizeof(char));

    if (dup == NULL) return NULL;

    memcpy(dup, c, len);

    return dup;
}

int is_index(const char* inp)
{
    while(*inp != '\0'){
        if (*inp < '0' || *inp > '9') return -1;
        inp++;
    }

    return 0;
}