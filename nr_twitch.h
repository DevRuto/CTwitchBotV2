//
// Created by Ruto on 9/13/2016.
//

#ifndef CTWITCHBOTV2_NR_TWITCH_H
#define CTWITCHBOTV2_NR_TWITCH_H

#include <stdlib.h>
#include <stdbool.h>
#include "nr_dictionary.h"


typedef struct {
    char* name;
    int flags;
} nr_twitch_channel;

typedef struct {
    char *nickname;
    char *channel;
    char *message;
} nr_twitch_message;

typedef struct {
    int sock;
    bool loggedin;
    nr_dictionary_t handlers;
    nr_dictionary_t channels;
} nr_twitch_ctx;

void nr_twitch_alloc(nr_twitch_ctx *);

void nr_twitch_free(nr_twitch_ctx *);

void nr_twitch_login(nr_twitch_ctx *, char *, char *);

void nr_twitch_register_callback(nr_twitch_ctx *, char *, void(*)(nr_twitch_ctx *, char *));

//void nr_twitch_read(nr_twitch_ctx *, void (*)(nr_twitch_ctx *,char *));

void nr_twitch_join_channel(nr_twitch_ctx *, char *);

void nr_twitch_leave_channel(nr_twitch_ctx *, char *);

nr_twitch_message nr_twitch_parse_message_alloc(char *);

void nr_twitch_free_message(nr_twitch_message *);

int nr_twitch_send(nr_twitch_ctx *, char *);

#endif //CTWITCHBOTV2_NR_TWITCH_H
