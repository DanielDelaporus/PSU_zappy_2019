/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** team
*/

#include "team.h"

team_t **list_team(argment_t *arg)
{
    team_t **list = calloc(arg->nb_teams, sizeof(team_t *));
    for ( int i = 0; i < arg->nb_teams; i++) {
        team_t *teamate = malloc(sizeof(team_t));
        teamate->name = malloc(strlen(arg->TeamName[i]));
        teamate->name = arg->TeamName[i];
        teamate->max_client = arg->nb_clients;
        teamate->actual_client = 0;
        list[i] = teamate;
    }
    return list;
}

int add_to_team_bis(socket_handle_t *att, int player, int i, int j)
{
    char buff[4096];
    int x;
    int y;
    player_attach_t *npb = &att->player_att[player];
    for (int nb = 0; att->map->map[j][i].players[nb] != NULL; nb++) {
        if (att->map->map[j][i].players[nb]->n == npb->client_socket) {
            x = j;
            y = i;
            snprintf(buff, 4096, "pnw %d %d %d %d %d %s", npb->client_socket,
            x, y, npb->player->O, npb->player->L, npb->player->N);
            send_graph(att, buff);
            return 1;
        }
    }
    return 0;
}

void add_to_team(socket_handle_t *att, int player, int i)
{
    player_attach_t *npb = &att->player_att[player];
    npb->team = att->teams[i];
    npb->player = init_player(*(att->teams[i]), npb->client_socket);
    place_player(*(att->map), npb->player);
    npb->team->actual_client += 1;
    dprintf(npb->client_socket, "%d\n%d %d\n",
        npb->client_socket, att->map->width, att->map->height);
    for (i = 0; i < att->map->width; i++) {
        for (int j = 0; j < att->map->height; j++) {
            add_to_team_bis(att, player, i, j);
        }
    }
}