#include <stdio.h>
#include <mem.h>
#include "nr_twitch.h"
#include "nr_utils.h"

#define USERNAME "USERNAME"
#define OATH_TOKEN "PASSWORD"

void login_success(nr_twitch_ctx *);
void message_handler(nr_twitch_ctx *, char *);

int main() {
    nr_twitch_ctx ctx;

    puts("TEST");
    nr_twitch_alloc(&ctx);

    nr_twitch_register_callback(&ctx, "LOGIN SUCCESS", login_success);
    nr_twitch_register_callback(&ctx, "PRIVMSG", message_handler);

    nr_twitch_login(&ctx, USERNAME, OATH_TOKEN);
    puts("END");
    fgetc(stdin);
    nr_twitch_free(&ctx);
    return 0;
}

void login_success(nr_twitch_ctx *ctx) {
    puts("LOGIN SUCCESS");
    nr_twitch_join_channel(ctx, "summit1g");
}

void message_handler(nr_twitch_ctx *ctx, char *data) {
    nr_twitch_message message = nr_twitch_parse_message_alloc(data);

    printf("%s: %s => %s\n", message.channel, message.nickname, message.message);

    nr_twitch_free_message(&message);
}