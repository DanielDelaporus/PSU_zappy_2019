/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "parsing_arg.h"
#include "player.h"
#include "team.h"
#include "queue.h"

typedef struct team_s team_t;
typedef struct Player player_t;
typedef struct map_s map_t;
typedef struct queue_time queue_time_t;

typedef struct player_attach
{
    int client_socket;
    player_t *player;
    team_t *team;
    queue_time_t *queue;
    int is_graphical;
} player_attach_t;

typedef struct socket_handle
{
    map_t *map;

    int max_clients;
    player_attach_t player_att[100];

    int nb_teams;
    team_t **teams;

    fd_set rfds_master;
    fd_set write_master;
    int listenfd;

    int freq;
} socket_handle_t;

int launch_server(argment_t *list);
map_t place_player(map_t map, player_t *player);
socket_handle_t *init_socket_handle(int listenfd, argment_t *client);

#endif /* !SERVER_H_ */
