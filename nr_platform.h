//
// Created by Ruto on 9/11/2016.
//

#ifndef CTWITCHBOT_PLATFORM_H
#define CTWITCHBOT_PLATFORM_H

#ifdef NR_NETWORK_INCLUDES
#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
//#define inet_pton(a,b,c) InetPton(a,b,c)
#else
#ifndef SOCKET
#define SOCKET int
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR	(-1)
#endif
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif
#endif

#endif //CTWITCHBOT_PLATFORM_H