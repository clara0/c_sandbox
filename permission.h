#ifndef PERMISSION_H
#define PERMISSION_H
#include <stdbool.h>
#include <string.h>

struct permission {
    char* subject;
    char* resource;
    char* action;
    bool allow;
};

bool samePerm(struct permission p1, struct permission p2) {
    return strcmp(p1.subject, p2.subject) && strcmp(p1.resource, p2.resource) &&
        strcmp(p1.action, p2.action);
}

bool sameAllow(struct permission p1, struct permission p2) {
    return strcmp(p1.subject, p2.subject) && strcmp(p1.resource, p2.resource) &&
        strcmp(p1.action, p2.action) && p1.allow == p2.allow;
}

#endif //PERMISSION_H
