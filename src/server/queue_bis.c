/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** queue
*/

#include "queue.h"

queue_time_t *add_to_queue(queue_time_t *queue, char *buf, int unit, int freq);

struct timeval get_esimation_time_s(int time_unit, int freq, struct timeval new)
{
    unsigned long usec, sec;

    usec = (1000000 *time_unit) / freq;
    sec = usec/1000000;
    usec -= sec * 1000000;
    new.tv_sec += sec;
    new.tv_usec += usec;
    if (new.tv_usec >= 1000000) {
        new.tv_usec -= 1000000;
        new.tv_sec += 1;
    }
    return new;
}

int queue_parser4(socket_handle_t *att, int player, char *buf, int freq)
{
    queue_time_t *queue = att->player_att[player].queue;
    if (strncmp("Forward\n", buf, 8) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    }
    return 0;
}

int graphical_ppo_bis(socket_handle_t *att, int player, int i, int j)
{
    char buff[4096];
    int x;
    int y;
    player_attach_t *npb = &att->player_att[player];
    for (int nb = 0; att->map->map[j][i].players[nb] != NULL; nb++) {
        if (att->map->map[j][i].players[nb]->n == npb->client_socket) {
            x = j;
            y = i;
            snprintf(buff, 4096, "ppo %d %d %d %d", npb->client_socket, x, y,
            npb->player->O);
            send_graph(att, buff);
            return 1;
        }
    }
    return 0;
}

void graphical_ppo(socket_handle_t *att, int player)
{
    for (int i = 0; i < att->map->width; i++) {
        for (int j = 0; j < att->map->height; j++) {
            graphical_ppo_bis(att, player, i, j);
        }
    }
}