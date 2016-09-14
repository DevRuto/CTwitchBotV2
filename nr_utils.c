//
// Created by Ruto on 9/11/2016.
//

#include <mem.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "nr_utils.h"

// http://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c
bool startswith(const char *str, const char *pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

char *concat(char *str1, char *str2) {
    char* output = malloc(1+strlen(str1)+strlen(str2));
    strcpy(output, str1);
    strcat(output, str2);
    return output;
}

bool contains(char* haystack, char* needle) {
    return strstr(haystack, needle) != NULL;
}

int indexof(char* str, char c) {
    int i;
    for (i = 0; i < strlen(str); i++)
        if (str[i]==c)return i;
    return -1;
}

char *substr(char* str, int start, int end) {
    char* output = malloc((size_t) (1 + (end - start)));
    memcpy(output, str+start, (size_t)(end-start));
    output[(end-start)] = '\0';
    return output;
}


char *strtolower(char *str) {
    size_t size = strlen(str);
    char *output = malloc(size+1);
    int i;
    for (i = 0; i < size; i++)
        output[i] = (char) tolower(str[i]);
    output[size] = '\0';
    return output;
}

bool strequals(char *str1, char *str2) {
    return strcmp(str1, str2) == 0;
}