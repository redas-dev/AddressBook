#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "linkedList.h"
#include "actions.h"
#include "helpers.h"

#define FILENAME "addresses.csv"
#define MAX_INPUT_LENGTH MAX_SIZE * 6

Node* load_init_data();
void parse_init_data(FILE* fin, Node** adressBook);

static volatile sig_atomic_t signal_sent = 0;

void sig_handler(int signal)
{
    signal_sent = 1;
}

int main(void)
{
    struct sigaction sa = { .sa_handler = sig_handler };

    sigaction(SIGINT, &sa, 0);
    sigaction(SIGQUIT, &sa, 0);

    char input[MAX_INPUT_LENGTH];
    
    Node* addressBook = load_init_data();

    if (addressBook == NULL) {
        printf("COULDN'T LOAD DATA CORRECTLY. CAN CONTINUE WITHOUT IT.");
    }

    print_actions_table();

    while (!signal_sent){
        printf("~ ");
        if(fgets(input, sizeof(input), stdin)){
            char* action = strtok(input, " ");

            int code = exec_action(action, &addressBook);

            if (code != 0) printf("Action failed, try again.\n");
        }
    } 

    delete_all(&addressBook);

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