#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/str_util.h";
#include "permission.h";

const int STR_SPACE = 30;
const int FILE_SPACE = 1000;

int index = 0;

FILE* file;

void read_file(char* content, FILE* file, struct permission check);

struct permission perms[10];

void can_main(int argc, char* argv[]) {
    bool invalid_path = false;
    int fileIndex = 1;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--policy-file", 13) == 0) {
            printf("%s\n", argv[i]);
            fileIndex = i;
        }
    }

    if (fileIndex == 1 || fileIndex == 4) {
        char subject[STR_SPACE];
        char action[STR_SPACE];
        char resource[STR_SPACE];
        char hehe[STR_SPACE]; // uhm program doesn't work without this line (?) don't ask

        strcpy(subject, argv[2]);
        strcpy(resource, argv[4]);
        strcpy(action, argv[3]);

        if (fileIndex == 4) {
            strcpy(subject, argv[1]);
            strcpy(resource, argv[3]);
            strcpy(action, argv[2]);
        }

        char path[sizeof(argv[fileIndex])];
        strcpy(path, argv[fileIndex]+14);
        file = fopen(path, "r");

        if (file == NULL) {
            file = fopen(argv[fileIndex+1], "r");

            if (file == NULL) {
                invalid_path = true;
                goto invalid_path;
            }

            if (fileIndex == 1) {
                strcpy(subject, argv[3]);
                strcpy(resource, argv[5]);
                strcpy(action, argv[4]);
            }
        }

        char* c = malloc(FILE_SPACE);

        struct permission check = {subject, resource, action, true};

        read_file(c, file, check);

        fclose(file);
        free(c);

    } else {
        puts("Use --policy-file to specify location of permissions file.");
    }

    invalid_path:
    if (invalid_path) {
        puts("Include a valid path for the policy file.");
    }

}

void read_file(char* content, FILE* file, struct permission check) {

    while(fgets(content, 100, file)) {
        lowercase(content);
        trim(content);
        puts(content);

        if (content[0] == 'p') {
            //restrict options for resources and actions later
            char* sep = ",";
            char** parts = split(content, sep);
            char* subj = parts[1];
            char* resource = parts[2];
            char* action = parts[3];
            char* allow = parts[4];
            bool allowed;

            if (strcmp(allow, "deny") == 0) {
                allowed = false;
            } else if (strcmp(allow, "allow") == 0) {
                allowed = true;
            } else {
                goto skip;
            }

            struct permission perm = {subj, resource, action, allowed};

            free(parts);
        }

        skip:
            // skip to next line in file
    }

}

