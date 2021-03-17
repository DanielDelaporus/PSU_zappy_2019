/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** graphical_parser
*/

#include "graphical_parser.h"

void send_graph(socket_handle_t *att, char *buf)
{
    for (int i = 0; i < att->max_clients; i++) {
        if (att->player_att[i].is_graphical == 1) {
            dprintf(att->player_att[i].client_socket, "%s\n", buf);
        }
    }
}

void graphical_bct(socket_handle_t *att, int player, char *buf)
{
    player_attach_t *npb = &att->player_att[player];
    int i;
    int x;
    int y;
    y = atoi(buf + 4);
    for (i = 4; buf[i] <= '9' && buf[i] >= '0'; i++);
    x = atoi(buf+i+1);
    dprintf(npb->client_socket, "bct %d %d %d %d %d %d %d %d %d\n", y, x,
    att->map->map[y][x].q0,
    att->map->map[y][x].q1, att->map->map[y][x].q2, att->map->map[y][x].q3,
    att->map->map[y][x].q4, att->map->map[y][x].q5, att->map->map[y][x].q6);
}

void graphical_mct(socket_handle_t *att, int player)
{
    player_attach_t *npb = &att->player_att[player];
    for (int y = 0; y < att->map->width; y++) {
        for (int x = 0; x < att->map->height; x++) {
            dprintf(npb->client_socket, "bct %d %d %d %d %d %d %d %d %d\n",
            y, x,
            att->map->map[y][x].q0, att->map->map[y][x].q1,
            att->map->map[y][x].q2, att->map->map[y][x].q3,
            att->map->map[y][x].q4, att->map->map[y][x].q5,
            att->map->map[y][x].q6);
        }
    }
}

void graphical_parser_gen(socket_handle_t *att, int player, char *buf)
{
    player_attach_t *npb = &att->player_att[player];
    if (npb->is_graphical == 0)
        return;
    if (strncmp("msz", buf, 3) == 0)
        dprintf(npb->client_socket, "msz %d %d\n", att->map->width,
                                                    att->map->height);
    if (strncmp("bct", buf, 3) == 0) {
        graphical_bct(att, player, buf);
    }
    if (strncmp("mct", buf, 3) == 0) {
        graphical_mct(att, player);
    }
}