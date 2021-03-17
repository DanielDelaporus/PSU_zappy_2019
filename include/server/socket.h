/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** socket
*/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include "server.h"
#include "graphical_parser.h"

typedef struct socket_handle socket_handle_t;

socket_handle_t *socket_init(argment_t *client);
int sock_update(socket_handle_t *att);
int send_message(socket_handle_t *att, char *buffer, int player);
void parsing_handle(socket_handle_t *att, int player, char *buf);
int set_rfds(int *sd_max, socket_handle_t *att, fd_set *rfds_fd,
    fd_set *write_fd);
void remove_player(socket_handle_t *att, int player, fd_set *rfds_fd,
    fd_set *write_fd);

#endif /* !SOCKET_H_ */
