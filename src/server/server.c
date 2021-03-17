/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** server
*/

#include "server.h"

int check_life(socket_handle_t *a);

socket_handle_t *init_socket_handle(int listenfd, argment_t *client)
{
    socket_handle_t *new = malloc(sizeof(socket_handle_t));
    new->map = malloc(sizeof(map_t));
    *(new->map) = init_map(client->width, client->height);
    new->max_clients = 100;
    for (int i = 0; i < new->max_clients; i++) {
        new->player_att[i].client_socket = 0;
        new->player_att[i].player = NULL;
        new->player_att[i].team = NULL;
        new->player_att[i].queue = NULL;
        new->player_att[i].is_graphical = 0;
    }
    new->nb_teams = client->nb_teams;
    new->teams = list_team(client);
    FD_ZERO(&new->rfds_master);
    FD_ZERO(&new->write_master);
    FD_SET(listenfd, &new->rfds_master);
    FD_SET(listenfd, &new->write_master);
    new->listenfd = listenfd;
    new->freq = client->freq;
    return new;
}

queue_time_t *check_and_delete(queue_time_t *check, socket_handle_t *a, int i)
{
    struct timeval actual_time;
    gettimeofday(&actual_time, NULL);
    queue_time_t *tmp;
    if (check == NULL)
        return NULL;
    if (check->time_to_execute.tv_sec < actual_time.tv_sec ||
                (check->time_to_execute.tv_sec == actual_time.tv_sec &&
                check->time_to_execute.tv_usec <= actual_time.tv_usec)) {
        parsing_handle(a, i, check->message);
        tmp = check;
        check = check->next;
        tmp->next = NULL;
        free(tmp);
        return check_and_delete(check, a, i);
    }
    check->next = check_and_delete(check->next, a, i);
    return check;
}

int queue_check_handle(socket_handle_t *a)
{
    for (int i = 0; i < a->max_clients; i++) {
        if (a->player_att[i].queue != NULL) {
            a->player_att[i].queue = check_and_delete(a->player_att[i].queue,
                a, i);
        }
    }
    return 0;
}

int launch_server(argment_t *list)
{
    socket_handle_t *a = socket_init(list);
    while (1) {
        sock_update(a);
        queue_check_handle(a);
        check_life(a);
    }
}