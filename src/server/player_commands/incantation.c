/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantation
*/

#include "player.h"

int more_than_level(int level, tile_t tile)
{
    int nb = 0;
    for (int i = 0; i < tile.n_players; i++) {
        if (tile.players[i]->L >= level)
            nb++;
    }
    return nb;
}

tile_t one_up(int list[8], player_t player, tile_t tile, int nb)
{
    if (player.L == list[0] && tile.q1 >= list[2] &&
    tile.q2 >= list[3] && tile.q3 >= list[4] &&
    tile.q4 >= list[5] && tile.q5 >= list[6] &&
    tile.q6 >= list[7] && more_than_level(list[0], tile) >= list[1]) {
        printf("LEVEL UP!\n");
        tile.q1 -= list[2];
        tile.q2 -= list[3];
        tile.q3 -= list[4];
        tile.q4 -= list[5];
        tile.q5 -= list[6];
        tile.q6 -= list[7];
        player.R = 0;
        player.L++;
        if (player.L == 8)
            player.R = 5;
        *tile.players[nb] = player;
    }
    return tile;
}

tile_t level_up(player_t player, tile_t tile, int nb)
{
    int list1[8] = { 1, 1, 1, 0, 0, 0, 0, 0};
    tile = one_up(list1, player, tile, nb);
    int list2[8] = { 2, 2, 1, 1, 1, 0, 0, 0};
    tile = one_up(list2, player, tile, nb);
    int list3[8] = { 3, 2, 2, 0, 1, 0, 2, 0};
    tile = one_up(list3, player, tile, nb);
    int list4[8] = { 4, 4, 1, 1, 2, 0, 1, 0};
    tile = one_up(list4, player, tile, nb);
    int list5[8] = { 5, 4, 1, 2, 1, 3, 0, 0};
    tile = one_up(list5, player, tile, nb);
    int list6[8] = { 6, 6, 1, 2, 3, 0, 1, 0};
    tile = one_up(list6, player, tile, nb);
    int list7[8] = { 7, 6, 2, 2, 2, 2, 2, 1};
    tile = one_up(list7, player, tile, nb);
    return tile;
}

map_t under_incantation(map_t map, int player_number, int i, int j)
{
    int nb = 0;
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (map.map[j][i].players[nb]->n == player_number) {
            map.map[j][i] = level_up(*(map.map[j][i].players[nb]),
            map.map[j][i], nb);
        }
    }
    return map;
}

map_t incantation(map_t map, int player_number)
{
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            map = under_incantation(map, player_number, i, j);
        }
    }
    return map;
}