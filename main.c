#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

#define FILENAME "addresses.csv"
#define PROGRAM_NOT_ENDED 1
#define MAX_INPUT_LENGTH 200

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
    Node* addressBook = load_init_data();
    if (addressBook == NULL) {
        printf("COULDN'T LOAD DATA CORRECTLY. CAN CONTINUE WITHOUT IT.");
    }

    print_actions_table();

    char input[MAX_INPUT_LENGTH];

    while(PROGRAM_NOT_ENDED){
        printf("~ ");
        fgets(input, sizeof(input), stdin);

        char* action = strtok(input, " ");

        int code = exec_action(action, &addressBook);

        if (code != 0) printf("Action failed, try again.\n");
    }

    return 0;
}

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
    printf("exit - Exits the program\n");
    printf("------------------------------------  ACTIONS ------------------------------------\n");
}

/*  Builds a string of the path to the default addresses.csv location.
    Returns a `char*` path on success, `NULL` otherwise.  */
char* get_full_path(const char* homeDir)
{
    int fullLen = strlen(homeDir) + strlen(FILENAME) + 2;   // +2 to account for '/' symbol and '\0'.

    char* fullPath = (char*)malloc(fullLen * sizeof(char));

    if (fullPath == NULL) return NULL;

    sprintf(fullPath, "%s/%s", homeDir, FILENAME);

    return fullPath;
}

/*  Loads the initial data from addresses.csv.
    Returns a new `Node*` address book on success, `NULL` if the path is incorrect or if the file couldn't be opened.  */
Node* load_init_data()
{
    char* homeDir = getenv("HOME");
    char* fullPath = get_full_path(homeDir);

    if (fullPath == NULL) return NULL;

    FILE *fin;

    if ((fin = fopen(fullPath, "r")) == NULL){
        printf("%s was not found in %s. Continuing without it.\n", FILENAME, homeDir);
        free(fullPath);
        return NULL;
    }

    Node* adrBook = NULL;

    parse_init_data(fin, &adrBook);
    free(fullPath);
    fclose(fin);

    return adrBook;
}

/*  Parses data from the .csv file.
    On successful parse, appends the node to the address book.  */
void parse_init_data(FILE* fin, Node** addressBook)
{
    char buffer[MAX_INPUT_LENGTH];

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

/*  Duplicates the string.
    Returns a new `char*` on success, `NULL` otherwise.  */
char* strdup(const char *c)
{
    int len = strlen(c) + 1;
    char* dup = (char*)malloc(len * sizeof(char));

    if (dup == NULL) return NULL;

    memcpy(dup, c, len);

    return dup;
}

/*  Checks if the given string is a valid index (integer).
    Returns 0 if true, -1 if false.  */
int is_index(const char* inp)
{
    while(*inp != '\0'){
        if (*inp < '0' || *inp > '9') return -1;
        inp++;
    }

    return 0;
}