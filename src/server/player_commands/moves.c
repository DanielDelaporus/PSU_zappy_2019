/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** moves
*/

#include "player.h"

map_t walk(map_t map, int i , int j, int nb);

map_t under_forward(map_t map, int player_number, int *ij, int *moved);

map_t forward(map_t map, int player_number)
{
    int *moved = malloc(sizeof(int));
    *moved = 1;
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            int *ij = calloc(2, sizeof(int));
            ij[0] = i;
            ij[1] = j;
            map = under_forward(map, player_number, ij, moved);
            free(ij);
        }
    }
    return map;
}

map_t under_turn_left(map_t map, int player_number, int i, int j)
{
    int nb = 0;
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (map.map[j][i].players[nb]->n == player_number) {
            if (map.map[j][i].players[nb]->O == 1)
                map.map[j][i].players[nb]->O = 4;
            else
                map.map[j][i].players[nb]->O -= 1;
        }
    }
    return map;
}

map_t turn_left(map_t map, int player_number)
{
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            map = under_turn_left(map, player_number, i, j);
        }
    }
    return map;
}

map_t under_turn_right(map_t map, int player_number, int i, int j)
{
    int nb = 0;
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (map.map[j][i].players[nb]->n == player_number) {
            if (map.map[j][i].players[nb]->O == 4)
                map.map[j][i].players[nb]->O = 1;
            else
                map.map[j][i].players[nb]->O += 1;
        }
    }
    return map;
}

map_t turn_right(map_t map, int player_number)
{
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            map = under_turn_right(map, player_number, i, j);
        }
    }
    return map;
}