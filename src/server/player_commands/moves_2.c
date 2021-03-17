/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** moves_2
*/

#include "player.h"

int truemod (int x, int y);

map_t walk(map_t map, int i , int j, int nb)
{
    player_t *tmp;
    tmp = map.map[j][i].players[nb];
    map.map[j][i].n_players--;
    int horr = 0;
    int vert = 0;
    if (map.map[j][i].players[nb]->O % 2 == 0)
        horr += map.map[j][i].players[nb]->O - 3;
    if (map.map[j][i].players[nb]->O % 2 == 1)
        vert += map.map[j][i].players[nb]->O - 2;
    horr = -horr;
    horr = truemod(j + horr, map.width);
    vert = truemod(i + vert, map.height);
    map.map[j][i].players[nb] = NULL;
    map.map[horr][vert].players[map.map[horr][vert].n_players] = tmp;
    map.map[horr][vert].n_players++;
    return map;
}

map_t under_forward(map_t map, int player_number, int *ij, int *moved)
{
    int nb = 0;
    int i = ij[0];
    int j = ij[1];
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (nb >= 0 && *moved &&
        map.map[j][i].players[nb]->n == player_number) {
            map = walk(map, i, j, nb);
            *moved = 0;
        }
    }
    return map;
}