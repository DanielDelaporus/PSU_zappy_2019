/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** socket_parser
*/

#include "socket_parser.h"

int parsing_handle2(socket_handle_t *att, int player, char *buf);

int parsing_handle3(socket_handle_t *att, int player, char *buf);

int parsing_handle4(socket_handle_t *att, int player, char *buf);

int parsing_handle5(socket_handle_t *att, int player, char *buf);

int parsing_handle6(socket_handle_t *att, int player, char *buf);

void parsing_handle(socket_handle_t *att, int player, char *buf)
{
    player_attach_t *npb = &att->player_att[player];
    for (int i = 0; i < att->nb_teams && npb->team == NULL; i++) {
        if (strncmp(buf, att->teams[i]->name,
                strlen(att->teams[i]->name)) == 0 &&
                att->teams[i]->actual_client < att->teams[i]->max_client) {
            add_to_team(att, player, i);
            return;
        }
        if (strncmp(buf, "GRAPHIC", 7) == 0)
            npb->is_graphical = 1;
    }
    if (npb->is_graphical == 1)
        return;
    if (npb->team == NULL) {
        send_message(att, "ko", player);
    } else if (parsing_handle2(att, player, buf) == 0 &&
            parsing_handle3(att, player, buf) == 0 &&
            parsing_handle4(att, player, buf) == 0 &&
            parsing_handle5(att, player, buf) == 0 &&
            parsing_handle6(att, player, buf) == 0)
        send_message(att, "ko", player);
}

int parsing_handle2(socket_handle_t *att, int player, char *buf)
{
    if (strncmp("Forward\n", buf, 8) == 0) {
        *(att->map) = forward(*(att->map),
            att->player_att[player].client_socket);
        graphical_ppo(att, player);
        send_message(att, "ok", player);
        return 1;
    }
    if (strncmp("Right\n", buf, 6) == 0) {
        *(att->map) = turn_right(*(att->map),
            att->player_att[player].client_socket);
        send_message(att, "ok", player);
        return 1;
    }
    if (strncmp("Left\n", buf, 5) == 0) {
        *(att->map) = turn_left(*(att->map),
            att->player_att[player].client_socket);
        send_message(att, "ok", player);
        return 1;
    }
    return 0;
}

int parsing_handle3(socket_handle_t *att, int player, char *buf)
{
    if (strncmp("Look\n", buf, 5) == 0) {
        char *str = malloc(sizeof(char) * 2000);
        str = look(*(att->map), att->player_att[player].client_socket, str);
        send_message(att, str, player);
        free(str);
        return 1;
    }
    if (strncmp("Inventory\n", buf, 10) == 0) {
        char *str = malloc(sizeof(char) * 80);
        str = inventory(*(att->map),
        att->player_att[player].client_socket, str);
        send_message(att, str, player);
        free(str);
        return 1;
    }
    if (strncmp("Broadcast", buf, strlen("Broadcast")) == 0) {
        send_message(att, "ko", player);
        return 1;
    }
    return 0;
}

int parsing_handle4(socket_handle_t *att, int player, char *buf)
{
    if (strncmp("Connect_nbr\n", buf, 12) == 0) {
        dprintf(att->player_att[player].client_socket, "%d\n",
            (att->player_att[player].team->max_client)
            - (att->player_att[player].team->actual_client));
        return 1;
    }
    if (strncmp("Fork\n", buf, 5) == 0) {
        send_message(att, "ko", player);
        return 1;
    }
    if (strncmp("Eject\n", buf, 5) == 0) {
        send_message(att, "ko", player);
        return 1;
    }
    return 0;
}

int parsing_handle5(socket_handle_t *att, int player, char *buf)
{
    if (strncmp("Set ", buf, 4) == 0) {
        char **str = calloc(1, sizeof(char *));
        *str = calloc(2, sizeof(char));
        att->map = put_down(att->map,
            att->player_att[player].client_socket, buf + 4, str);
        send_message(att, *str, player);
        free(str);
        return 1;
    }
    if (strncmp("Take ", buf, 5) == 0) {
        char **str = calloc(1, sizeof(char *));
        *str = calloc(2, sizeof(char));
        att->map = pick_up(att->map,
            att->player_att[player].client_socket, buf + 5, str);
        send_message(att, *str, player);
        free(str);
        return 1;
    }
    return 0;
}