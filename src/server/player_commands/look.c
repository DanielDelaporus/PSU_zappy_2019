/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** look
*/

#include "player.h"
#include <math.h>

int truemod (int x, int y)
{
    int rep = x % y;
    if (x < 0)
        rep = y + x;
    return rep;
}

char *under_look(map_t map, int player_number, int *ij, char *str)
{
    int nb = 0;
    int i = ij[0];
    int j = ij[1];
    for (;map.map[j][i].players[nb] != NULL; nb++) {
        if (map.map[j][i].players[nb]->n == player_number) {
            int horr = 0;
            int vert = 0;
            if (map.map[j][i].players[nb]->O % 2 == 0)
                horr += map.map[j][i].players[nb]->O - 3;
            if (map.map[j][i].players[nb]->O % 2 == 1)
                vert += map.map[j][i].players[nb]->O - 2;
            int *hv = calloc(3, sizeof(int));
            hv[0] = -horr;
            hv[1] = vert;
            hv[2] = nb;
            str = field_of_view(map, hv, map.map[j][i], str);
            free(hv);
        }
    }
    return str;
}

char *look(map_t map, int player_number, char *str)
{
    for (int  i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            int *ij = calloc(2, sizeof(int));
            ij[0] = i;
            ij[1] = j;
            str = under_look(map, player_number, ij, str);
            free(ij);
        }
    }
    return str;
}

char *field_of_view(map_t map, int *h, tile_t tile, char *str)
{
    str = strcpy(str, "[");
    int v = (h[1] != 0) ? 1 : -1;
    str = strcat(str, print_tile(map.map[tile.X][tile.Y], 1));
    for (int i = 1; i < map.map[tile.X][tile.Y].players[h[2]]->L + 1; i++) {
        for (int j = 1; j < i + 1; j++) {
            int _x = truemod(tile.X + (i * h[0]) + (v * j * h[1]), map.width);
            int _y = truemod(tile.Y + (i * h[1]) + (v * j * h[0]), map.height);
            str = strcat(str, print_tile(map.map[_x][_y], 0));
        }
        int x = truemod((tile.X + (i * h[0])), (map.width));
        int y = truemod((tile.Y + (i * h[1])), (map.height));
        str = strcat(str, print_tile(map.map[x][y], 0));
        for (int j = 1; j < i + 1; j++) {
            int _x = truemod(tile.X + (i * h[0]) + (-v * j * h[1]), map.width);
            int _y = truemod(tile.Y + (i * h[1]) + (-v * j * h[0]), map.height);
            str = strcat(str, print_tile(map.map[_x][_y], 0));
        }
    }
    return strcat(str, " ]");
}

char *print_tile(tile_t tile, int beggin)
{
    char *str = malloc(2000);
    str = strcpy(str, "");
    str = (beggin == 0) ? strcpy(str, ",") : strcpy(str, "");
    for (int i = 0; i < tile.n_players; i++)
        str = strcat(str, " player");
    for (int i = 0; i < tile.q0; i++)
        str = strcat(str, " food");
    for (int i = 0; i < tile.q1; i++)
        str = strcat(str, " linemate");
    for (int i = 0; i < tile.q2; i++)
        str = strcat(str, " deraumere");
    for (int i = 0; i < tile.q3; i++)
        str = strcat(str, " sibur");
    for (int i = 0; i < tile.q4; i++)
        str = strcat(str, " mendiane");
    for (int i = 0; i < tile.q5; i++)
        str = strcat(str, " phiras");
    for (int i = 0; i < tile.q6; i++)
        str = strcat(str, " thystame");
    return str;
}
