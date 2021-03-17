/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** inventory_3
*/

#include "player.h"

tile_t under_under_fill_inv(tile_t tile, player_t *player,
char *what, char **str)
{
    if (strncmp(what, "thystame", 8) == 0) {
        player->inv.q6 += tile.q6;
        if (tile.q6 != 0)
            *str = "ok";
        tile.q6 = 0;
    }
    return tile;
}

tile_t under_fill_inv(tile_t tile, player_t *player, char *what, char **str)
{
    if (strncmp(what, "sibur", 5) == 0) {
        player->inv.q3 += tile.q3;
        if (tile.q3 != 0)
            *str = "ok";
        tile.q3 = 0;
    }
    if (strncmp(what, "mendiane", 8) == 0) {
        player->inv.q4 += tile.q4;
        if (tile.q4 != 0)
            *str = "ok";
        tile.q4 = 0;
    }
    if (strncmp(what, "phiras", 6) == 0) {
        player->inv.q5 += tile.q5;
        if (tile.q5 != 0)
            *str = "ok";
        tile.q5 = 0;
    }
    return under_under_fill_inv(tile, player, what, str);
}

tile_t fill_inv(tile_t tile, player_t *player, char *what, char **str)
{
    if (strncmp(what, "food", 4) == 0) {
        player->inv.q0 += tile.q0;
        if (tile.q0 != 0)
            *str = "ok";
        tile.q0 = 0;
    }
    if (strncmp(what, "linemate", 8) == 0) {
        player->inv.q1 += tile.q1;
        if (tile.q1 != 0)
            *str = "ok";
        tile.q1 = 0;
    }
    if (strncmp(what, "deraumere", 9) == 0) {
        player->inv.q2 += tile.q2;
        if (tile.q2 != 0)
            *str = "ok";
        tile.q2 = 0;
    }
    return under_fill_inv(tile, player, what, str);
}