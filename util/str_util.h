#ifndef STR_UTIL_H
#define STR_UTIL_H
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

static int valid_brackets(char* str) {
    int size = strlen(str);
    char brackets[size];
    int bracket_index = 0;

    for (int i = 0; i < strlen(str); i++) {

        char c = str[i];

        switch(c) {
            case '(': case '{': case '[': case '<':
                brackets[bracket_index] = c;
                bracket_index++;
                break;
            case ')':
                if (brackets[bracket_index-1] != '(') {
                    return 0;
                }
                bracket_index--;
                break;
            case '}':
                if (brackets[bracket_index-1] != '{') {
                    return 0;
                }
                bracket_index--;
                break;
            case ']':
                if (brackets[bracket_index-1] != '[') {
                    return 0;
                }
                bracket_index--;
                break;
            case '>':
                if (brackets[bracket_index-1] != '<') {
                    return 0;
                }
                bracket_index--;
                break;
        }
    }

    return bracket_index == 0;
}

// <(>{)} is considered valid here
static int valid_brackets1(char* str) {
    int paren_ct = 0;
    int curl_ct = 0;
    int sq_ct = 0;
    int carrot_ct = 0;

    for (int i = 0; i < strlen(str); i++) {

        char c = str[i];

        switch(c) {
            case '(':
                paren_ct++;
                break;
            case '{':
                curl_ct++;
                break;
            case '[':
                sq_ct++;
                break;
            case '<':
                carrot_ct++;
                break;
            case ')':
                paren_ct--;
                break;
            case '}':
                curl_ct--;
                break;
            case ']':
                sq_ct--;
                break;
            case '>':
                carrot_ct--;
                break;
        }

        if (paren_ct < 0 || curl_ct < 0 || sq_ct < 0 || carrot_ct < 0) {
            return 0;
        }
    }

    return paren_ct == 0 && curl_ct == 0 && sq_ct == 0 && carrot_ct == 0;
}


#endif //STR_UTIL_H
