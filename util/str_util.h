#ifndef STR_UTIL_H
#define STR_UTIL_H
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

static void lowercase(char* str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

static char** split(char* str, const char* sep) {
    size_t ct = 0;
    char* last = 0;
    char* cp = str;

    while (*cp)
    {
        if (*sep == *cp)
        {
            ct++;
            last = cp;
        }
        cp++;
    }

    if (last == cp) {
        ct += 2;
    } else {
        ct++;
    }

    char** parts = malloc(sizeof(char*) * (ct + 1));

    char* test = strdup(str);
    char* pt = strtok(test, sep);
    size_t i = 0;

    while(pt) {
        *(parts + i) = strdup(pt);
        i++;
        pt = strtok(NULL, sep);
    }

    *(parts+i) = 0;
    free(test);
    return parts;
}

static void trim(char* str) { // do preceeding spaces later
    int last_char = 0;
    int str_len = strlen(str);

    for (int i = 0; i < str_len; i++) {
        if (!isspace(str[i])) {
            last_char = i+1;
        }
    }

    strncpy(str, str, last_char);
    str[last_char] = '\0';
}


#endif //STR_UTIL_H
