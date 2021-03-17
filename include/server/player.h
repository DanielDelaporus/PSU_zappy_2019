/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "map.h"
#include "team.h"
#include "queue.h"

typedef struct map_s map_t;
typedef struct Tile_s tile_t;
typedef struct team_s team_t;

typedef struct Inventory
{
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;
} invent_t;

typedef struct Player
{
    int n;
    int O;
    int L;
    int e;
    struct timeval T;
    char *N;
    char *M;
    int R;
    int i;
    invent_t inv;
} player_t;

invent_t init_inv(void);
player_t *init_player(team_t team, int player_nb);

map_t delete_player(map_t map, int player_number);
map_t place_player(map_t map, player_t *player);

map_t *pick_up(map_t *map, int player_number, char *what, char **str);
tile_t fill_inv(tile_t tile, player_t *player, char *what, char **str);
tile_t under_fill_inv(tile_t tile, player_t *player, char *what, char **str);

map_t *put_down(map_t *map, int player_number, char *what, char **str);
tile_t empty_inv(tile_t tile, player_t *player, char *what, char **str);
tile_t under_empty_inv(tile_t tile, player_t *player, char *what, char **str);

map_t forward(map_t map, int player_number);
map_t walk(map_t map, int i , int j, int nb);

map_t turn_left(map_t map, int player_number);

map_t turn_right(map_t map, int player_number);

char *inventory(map_t map, int player_number, char *str);

char *look(map_t map, int player_number, char *str);
char *field_of_view(map_t map, int *h, tile_t tile, char *str);
char *print_tile(tile_t tile, int beggin);

map_t incantation(map_t map, int player_number);
tile_t one_up(int list[8], player_t player, tile_t tile, int nb);
tile_t level_up(player_t player, tile_t tile, int nb);
int more_than_level(int level, tile_t tile);

#endif /* !PLAYER_H_ */
