//
// Created by Ruto on 9/11/2016.
//

#ifndef CTWITCHBOT_NR_FUNC_H
#define CTWITCHBOT_NR_FUNC_H

#include <stdbool.h>

bool startswith(const char *, const char *);

char *concat(char *, char *);

bool contains(char *, char *);

int indexof(char *, char);

char *substr(char*, int, int);

char *strtolower(char *);

bool strequals(char *, char *);

#endif //CTWITCHBOT_NR_FUNC_H