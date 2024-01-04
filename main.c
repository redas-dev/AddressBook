#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "linkedList.h"
#include "actions.h"
#include "helpers.h"

#define FILENAME "addresses.csv"
#define PROGRAM_NOT_ENDED 1
#define MAX_INPUT_LENGTH MAX_SIZE * 6

Node* load_init_data();
void parse_init_data(FILE* fin, Node** adressBook);

Node* addressBook = NULL;

void sig_handler(int signum)
{
    delete_all(&addressBook);

    switch (signum)
    {
        case 2:
            signal(SIGINT, SIG_DFL);
            raise(signum);
            break;
        case 3:
            signal(SIGQUIT, SIG_DFL);
            raise(signum);
            break;
    }
}

int main(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    
    addressBook = load_init_data();

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

/*  Loads the initial data from addresses.csv.
    Returns a new `Node*` address book on success, `NULL` if the path is incorrect or if the file couldn't be opened.  */
Node* load_init_data()
{
    char* homeDir = getenv("HOME");
    char* fullPath = get_full_path(homeDir, FILENAME);

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

        Node* temp = create_new_node(name, surname, email, phoneNumber);

        if (temp == NULL) continue;

        add_new_to_end(temp, addressBook);
    }
}