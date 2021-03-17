/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** map
*/

#include "map.h"

tile_t rand_tile(tile_t tile)
{
    tile.q0 = rand() % 2;
    tile.q1 = rand() % 2;
    tile.q2 = rand() % 2;
    tile.q3 = rand() % 2;
    tile.q4 = rand() % 2;
    tile.q5 = rand() % 2;
    tile.q6 = rand() % 2;
    tile.players = calloc(20, sizeof(player_t *));
    tile.n_players = 0;
    return tile;
}

map_t generate_map(map_t map)
{
    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            map.map[j][i].X = j;
            map.map[j][i].Y = i;
            map.map[j][i].n_players = 0;
            map.map[j][i] = rand_tile(map.map[j][i]);
        }
    }
    return map;
}

map_t init_map(int width, int height)
{
    map_t map;
    map.height = height;
    map.width = width;
    map.map = calloc(width, sizeof(tile_t *));
    for (int i = 0; i < width; i++){
        map.map[i] = calloc(height, sizeof(tile_t));
    }
    return generate_map(map);
}

void delete_tile(tile_t tile)
{
    for (int i = 0; i < tile.n_players; i++) {
        free(tile.players[i]);
        tile.players[i] = NULL;
    }
}

void detele_map(map_t map)
{
    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            delete_tile(map.map[j][i]);
            free(map.map[j]);
            map.map[j] = NULL;
        }
    }
    free(map.map);
    map.map = NULL;
}