/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** lifetime
*/

#include "player.h"

int check_player_life(player_t *player, socket_handle_t *a, int i)
{
    struct timeval new = get_esimation_time_s(126, a->freq, player->T);
    struct timeval actual;
    gettimeofday(&actual, NULL);
    if (new.tv_sec < actual.tv_sec || (new.tv_sec == actual.tv_sec
    && new.tv_usec <= actual.tv_usec)) {
        printf("new: %ld, %ld\n", new.tv_sec, new.tv_usec);
        printf("actual: %ld, %ld\n", actual.tv_sec, actual.tv_usec);
        if (player->inv.q0 > 0) {
            player->inv.q0 -= 1;
            player->T = actual;
        } else {
            send_message(a, "dead", i);
            remove_player(a, i, NULL, NULL);
        }
    }
    return 0;
}

int check_life(socket_handle_t *a)
{
    for (int i = 0; i < a->max_clients; i++) {
        if (a->player_att[i].player != NULL) {
            check_player_life(a->player_att[i].player, a, i);
        }
    }
    return 0;
}