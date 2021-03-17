/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** team
*/

#ifndef TEAM_H_
#define TEAM_H_

#include "player.h"
#include "server.h"
#include <sys/select.h>

typedef struct socket_handle socket_handle_t;

typedef struct team_s {
    char *name;
    int max_client;
    int actual_client;
} team_t;

team_t **list_team(argment_t *arg);
void add_to_team(socket_handle_t *att, int player, int i);

#endif /* !TEAM_H_ */
