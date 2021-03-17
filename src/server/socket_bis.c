/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** socket_bis
*/

#include "socket.h"

int set_rfds(int *sd_max, socket_handle_t *att, fd_set *rfds_fd,
    fd_set *write_fd)
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 50;

    *sd_max = att->listenfd;
    int sd;
    int reader_sel;
    for (int i = 0; i < att->max_clients; i++) {
        sd = att->player_att[i].client_socket;
        if (sd > 0)
            FD_SET(sd, rfds_fd);
        if (sd > *sd_max)
            *sd_max = sd;
    }
    return reader_sel = select((*sd_max) + 1, rfds_fd, write_fd, NULL, &tv);
}

int send_message(socket_handle_t *att, char *buffer, int player)
{
    dprintf(att->player_att[player].client_socket, "%s\n", buffer);
    return 0;
}

queue_time_t *delete_queue(queue_time_t *q)
{
    if (q == NULL)
        return NULL;
    q->next = delete_queue(q->next);
    if (q->message)
        free(q->message);
    if (q)
        free(q);
    return NULL;
}

void remove_player(socket_handle_t *att, int player, fd_set *rfds_fd,
    fd_set *write_fd)
{
    char buff[1024];
    printf("Client %d disconnected\n", player);
    if (rfds_fd != NULL && write_fd != NULL) {
        FD_CLR(att->player_att[player].client_socket, rfds_fd);
        FD_CLR(att->player_att[player].client_socket, write_fd);
        FD_CLR(att->player_att[player].client_socket, &(att->rfds_master));
        FD_CLR(att->player_att[player].client_socket, &(att->write_master));
    }
    close(att->player_att[player].client_socket);
    snprintf(buff, 4096, "pdi %d", att->player_att[player].client_socket);
    send_graph(att, buff);
    *(att->map) = delete_player(*(att->map),
        att->player_att[player].client_socket);
    att->player_att[player].client_socket = 0;
    att->player_att[player].player = NULL;
    att->player_att[player].team = NULL;
    att->player_att[player].queue = delete_queue(
                                    att->player_att[player].queue);
    att->player_att[player].is_graphical = 0;
}


int parsing_handle6(socket_handle_t *att, int player, char *buf)
{
    if (strncmp("Incantation\n", buf, 12) == 0) {
        *(att->map) = incantation(*(att->map),
            att->player_att[player].client_socket);
        send_message(att, "ok", player);
        return 1;
    }
    return 0;
}