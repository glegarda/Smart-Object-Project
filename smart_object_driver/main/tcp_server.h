#pragma once
#include "lib_includes.h"

#define CONFIG_EXAMPLE_IPV4 1
#define PORT 3500

#define START 1
#define STOP 2
#define RESTART 3
#define TEST 4
#define GLOBAL_CONFIG 5

static const char *TAG = "TCP";

int tcp_socket_listening(const int listen_sock);
int tcp_respond(const int socket, const char* message, const int size);
void print_message(const int sock);
int tcp_server_init(void *pvParameters);
int get_action(const int sock);
int get_config(const int sock);