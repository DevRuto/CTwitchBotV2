//
// Created by Ruto on 9/11/2016.
//

#ifndef CTWITCHBOT_SOCKET_H
#define CTWITCHBOT_SOCKET_H

#include <stdio.h>
#define NR_NETWORK_INCLUDES
#include "nr_platform.h"

int nr_socket_create(void);

int nr_socket_shutdown(int);

int nr_socket_connect(int, char*, int);

int nr_socket_bind(int, char*, int);

int nr_socket_listen(int, int);

int nr_socket_accept(int, struct sockaddr*, int*);

int nr_socket_read(int, char*, int);

int nr_socket_send(int, char *, size_t);

#endif //CTWITCHBOT_SOCKET_H