/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#include "player.h"
#include <string.h>

invent_t init_inv(void)
{
    invent_t inventor;
    inventor.q0 = 10;
    inventor.q1 = 0;
    inventor.q2 = 0;
    inventor.q3 = 0;
    inventor.q4 = 0;
    inventor.q5 = 0;
    inventor.q6 = 0;
    return inventor;
}

player_t *init_player(team_t team, int player_nb)
{
    player_t *player = malloc(sizeof(player_t));
    team.actual_client++;
    player->n = player_nb;
    player->O = 1;
    player->L = 1;
    player->e = 0;
    gettimeofday(&player->T, NULL);
    player->N = team.name;
    player->R = 0;
    player->M = "";
    player->i = 0;
    player->inv = init_inv();
    return player;
}

map_t under_delete_player(map_t map, int player_number, int i, int j)
{
    int nb = 0;
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (map.map[j][i].players[nb]->n == player_number) {
            map.map[j][i].n_players--;
            free(map.map[j][i].players[nb]);
            map.map[j][i].players[nb] = NULL;
        }
    }
    return map;
}

map_t delete_player(map_t map, int player_number)
{
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            map = under_delete_player(map, player_number, i, j);
        }
    }
    return map;
}

map_t place_player(map_t map, player_t *player)
{
    int _x = rand() % map.width;
    int _y = rand() % map.height;
    map.map[_x][_y].players[map.map[_x][_y].n_players] = player;
    map.map[_x][_y].n_players++;
    return map;
}