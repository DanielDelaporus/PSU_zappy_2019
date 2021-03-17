/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** map
*/

#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "team.h"

typedef struct Player player_t;

typedef struct Tile_s {
    int X;
    int Y;
    int n_players;
    player_t **players;
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;
} tile_t;

typedef struct map_s
{
    int width;
    int height;
    tile_t **map;
} map_t;

map_t generate_map(map_t map);
tile_t rand_tile(tile_t tile);
map_t init_map(int width, int height);

#endif /* !MAP_H_ */
