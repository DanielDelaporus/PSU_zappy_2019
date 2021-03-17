/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** inventory_2
*/

#include "player.h"

char *under_inventory(map_t map, int player_number, int *ij, char *str)
{
    int nb = 0;
    int i = ij[0];
    int j = ij[1];
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (map.map[j][i].players[nb]->n == player_number) {
            player_t *player = map.map[j][i].players[nb];
            snprintf(str, 80,
            "[food %d, linemate %d, deraumere %d, sibur %d, "
            "mendiane %d, phiras %d, thystame %d]",
            player->inv.q0, player->inv.q1,
            player->inv.q2, player->inv.q3,
            player->inv.q4, player->inv.q5,
            player->inv.q6);
        }
    }
    return str;
}

tile_t under_under_empty_inv(tile_t tile, player_t *player,
char *what, char **str)
{
    if (strncmp(what, "phiras", 6) == 0) {
        tile.q5 += player->inv.q5;
        if (player->inv.q5 != 0)
            *str = "ok";
        player->inv.q5 = 0;
    }
    if (strncmp(what, "thystame", 8) == 0) {
        tile.q6 += player->inv.q6;
        if (player->inv.q6 != 0)
            *str = "ok";
        player->inv.q6 = 0;
    }
    return tile;
}

tile_t under_empty_inv(tile_t tile, player_t *player, char *what, char **str)
{
    if (strncmp(what, "sibur", 5) == 0) {
        tile.q3 += player->inv.q3;
        if (player->inv.q3 != 0)
            *str = "ok";
        player->inv.q3 = 0;
    }
    if (strncmp(what, "mendiane", 8) == 0) {
        tile.q4 += player->inv.q4;
        if (player->inv.q4 != 0)
            *str = "ok";
        player->inv.q4 = 0;
    }
    return under_under_empty_inv(tile, player, what, str);
}

tile_t empty_inv(tile_t tile, player_t *player, char *what, char **str)
{
    if (strncmp(what, "food", 4) == 0) {
        tile.q0 += player->inv.q0;
        if (player->inv.q0 != 0)
            *str = "ok";
        player->inv.q0 = 0;
    }
    if (strncmp(what, "linemate", 8) == 0) {
        tile.q1 += player->inv.q1;
        if (player->inv.q1 != 0)
            *str = "ok";
        player->inv.q1 = 0;
    }
    if (strncmp(what, "deraumere", 9) == 0) {
        tile.q2 += player->inv.q2;
        if (player->inv.q2 != 0)
            *str = "ok";
        player->inv.q2 = 0;
    }
    return under_fill_inv(tile, player, what, str);
}