//
// Created by Ruto on 9/13/2016.
//

#include "nr_twitch.h"
#include "nr_socket.h"
#include "nr_utils.h"

#define BUFFER_SIZE 512

#define TWITCH_IRC "irc.chat.twitch.tv"
#define TWITCH_PORT 6667

void data_handler(nr_twitch_ctx *, char *);
void nr_twitch_read(nr_twitch_ctx *);

void nr_twitch_alloc(nr_twitch_ctx *ctx) {
    nr_dictionary_init(&ctx->handlers);
    ctx->sock = nr_socket_create();
    ctx->loggedin = false;
    //nr_dictionary_init(ctx->channels);
}

void nr_twitch_free(nr_twitch_ctx *ctx) {
    //nr_dictionary_free(ctx->channels);
    nr_dictionary_free(&ctx->handlers);
    nr_socket_shutdown(ctx->sock);
}

void nr_twitch_register_callback(nr_twitch_ctx *ctx, char *command, void(*callback)(nr_twitch_ctx *, char *)) {
    nr_dictionary_add(&ctx->handlers, command, callback);
}

void nr_twitch_login(nr_twitch_ctx *ctx, char *username, char *oath) {
    nr_socket_connect(ctx->sock, TWITCH_IRC, TWITCH_PORT);
    char *pass = concat("PASS ", oath);
    char *nick = concat("NICK ", strtolower(username)); //username always lower
    nr_twitch_send(ctx, pass);
    nr_twitch_send(ctx, nick);
    nr_twitch_read(ctx);
}

void nr_twitch_read(nr_twitch_ctx *ctx) {
    char buffer[BUFFER_SIZE];
    int size = 1;
    while (size > 0) {
        size = nr_socket_read(ctx->sock, buffer, BUFFER_SIZE);
        buffer[size] = '\0';
        data_handler(ctx, buffer);
    }
}

int nr_twitch_send(nr_twitch_ctx *ctx, char *buffer) {
    return nr_socket_send(ctx->sock, concat(buffer, "\n"), strlen(buffer)+1);
}

void nr_twitch_join_channel(nr_twitch_ctx *ctx, char *channel) {
    char *lower = strtolower(channel);
    char *send = concat("JOIN #", lower);
    nr_twitch_send(ctx, send);

    free(lower);
    free(send);
}

void nr_twitch_leave_channel(nr_twitch_ctx *ctx, char *channel) {
    char *lower = strtolower(channel);
    char *send = concat("PART #", lower);
    nr_twitch_send(ctx, send);

    free(lower);
    free(send);
}

nr_twitch_message nr_twitch_parse_message_alloc(char *data) {
    char *basemsg = substr(data, indexof(data, '#'), strlen(data));
    char *channel = substr(basemsg, 0, indexof(basemsg, ' '));
    char *message = substr(basemsg, indexof(basemsg, ':')+1, strlen(basemsg));
    char *nick = substr(data, 1, indexof(data,'!'));

    nr_twitch_message msg;
    msg.channel = channel;
    msg.message = message;
    msg.nickname = nick;
    return msg;
}

void nr_twitch_free_message(nr_twitch_message *msg) {
    free(msg->nickname);
    free(msg->message);
    free(msg->channel);
}

char *extract_command(char *str) {
    //Each response won't always have a command.
    //When it does, it'll be the second position splitted by space
    char *delimeter = " ";
    strtok(strdup(str), delimeter);
    return strtok(NULL, delimeter);

}

void data_handler(nr_twitch_ctx *ctx, char *data) {
    int index;

    if (startswith(data, "PING")) {
        nr_twitch_send(ctx, "PONG :tmi.twitch.t");
    }
    if (contains(data, "Welcome")) {
        ctx->loggedin = true;
        if ((index = nr_dictionary_indexof(&ctx->handlers, "LOGIN SUCCESS")) > -1) {
            ((void(*)(nr_twitch_ctx *))(&ctx->handlers)->headers[index].value)(ctx);
        }
    }
    if (strequals(extract_command(data), "PRIVMSG")) {
        if ((index = nr_dictionary_indexof(&ctx->handlers, "PRIVMSG")) > -1) {
            ((void(*)(nr_twitch_ctx *, char *))(&ctx->handlers)->headers[index].value)(ctx, data);
        }
    }
    //printf("\nRECV\n%s\nEND RECV\n", data);
}