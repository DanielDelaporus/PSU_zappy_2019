/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** inventory
*/

#include "player.h"

char *under_inventory(map_t map, int player_number, int *ij, char *str);

char *inventory(map_t map, int player_number, char *str)
{
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            int *ij = calloc(2, sizeof(int));
            ij[0] = i;
            ij[1] = j;
            str = under_inventory(map, player_number, ij, str);
            free(ij);
        }
    }
    return str;
}

map_t *under_pick_up(map_t *map, int *ij, char *what, char **str)
{
    int nb = 0;
    int i = ij[0];
    int j = ij[1];
    int player_number = ij[2];
    for (;map->map[j][i].players[nb] != NULL; nb++) {
        if (map->map[j][i].players[nb]->n == player_number) {
            map->map[j][i] = fill_inv(map->map[j][i],
            map->map[j][i].players[nb], what, str);
        }
    }
    if (strcmp(*str, "ok") != 0)
        *str = "ko";
    return map;
}

map_t *pick_up(map_t *map, int player_number, char *what, char **str)
{
    for (int  i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            int *ij = calloc(3, sizeof(int));
            ij[0] = i;
            ij[1] = j;
            ij[2] = player_number;
            map = under_pick_up(map, ij, what, str);
            free(ij);
        }
    }
    return map;
}

map_t *under_put_down(map_t *map, int *ij, char *what, char **str)
{
    int nb = 0;
    int i = ij[0];
    int j = ij[1];
    int player_number = ij[2];
    for (;map->map[j][i].players[nb] != NULL; nb++) {
        if (map->map[j][i].players[nb]->n == player_number) {
            map->map[j][i] = empty_inv(map->map[j][i],
            map->map[j][i].players[nb], what, str);
        }
    }
    if (strcmp(*str, "ok") != 0)
        *str = "ko";
    return map;
}

map_t *put_down(map_t *map, int player_number, char *what, char **str)
{
    for (int  i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            int *ij = calloc(3, sizeof(int));
            ij[0] = i;
            ij[1] = j;
            ij[2] = player_number;
            map = under_put_down(map, ij, what, str);
            free(ij);
        }
    }
    return map;
}