#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

/*  Builds a string of the path to the default addresses.csv location.
    Returns a `char*` path on success, `NULL` otherwise.  */
char* get_full_path(const char* homeDir, const char* FILENAME)
{
    int fullLen = strlen(homeDir) + strlen(FILENAME) + 2;   // +2 to account for '/' symbol and '\0'.

    char* fullPath = (char*)malloc(fullLen * sizeof(char));

    if (fullPath == NULL) return NULL;

    sprintf(fullPath, "%s/%s", homeDir, FILENAME);

    return fullPath;
}