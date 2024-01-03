#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

#define FILENAME "addresses.csv"

int load_init_data();

int main(void)
{
    printf("------ LOADING DATA FROM ADDRESSES.CSV ------\n");
    load_init_data();
    printf("------ LOADING DATA FROM ADDRESSES.CSV ------\n");

    print_records();    // FOR DEBUGGING

    return 0;
}

char* get_full_path(char* homeDir)
{
    unsigned int fullLen = strlen(homeDir) + strlen(FILENAME) + 1;

    char* fullPath = malloc(fullLen * sizeof(char));

    if (fullPath == NULL) return NULL;

    snprintf(fullPath, fullLen + 1, "%s/%s", homeDir, FILENAME);

    return fullPath;
}

int load_init_data()
{
    char* homeDir = getenv("HOME");
    char* fullPath = get_full_path(homeDir);

    FILE *fin;

    if ((fin = fopen(fullPath, "r")) == NULL){
        printf("%s was not found in %s\n", FILENAME, homeDir);
        return -1;
    }

    char buffer[1000];

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
        printf("%s %s %s %s\n", temp->name, temp->surname, temp->email, temp->phoneNumber);
        add_new_to_end(temp);
    }

    free(fullPath);
    fclose(fin);

    return 0;
}