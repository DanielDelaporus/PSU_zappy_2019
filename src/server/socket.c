/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** socket
*/

#include "socket.h"

int config_socket(void)
{
    int mult = 1;
    int sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror ("socket");
        exit (84);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &mult, sizeof(mult)) < 0) {
        perror("Error socketopt");
        exit(84);
    }
    return sock;
}

socket_handle_t *socket_init(argment_t *client)
{
    struct sockaddr_in infos;
    int listenfd = config_socket();
    socket_handle_t *att = init_socket_handle(listenfd, client);

    infos.sin_family = AF_INET;
    infos.sin_addr.s_addr = htons(INADDR_ANY);
    infos.sin_port = htons(client->port);
    if (bind(listenfd, (struct sockaddr *) &infos, sizeof(infos)) < 0) {
        perror("Error on binding\n");
        exit(84);
    }
    if (listen(listenfd, 5) < 0) {
        perror("Error on listen\n");
        exit(84);
    }
    printf("PORT: %d\n", client->port);
    return att;
}

int client_new_inputs(socket_handle_t *att, int player, fd_set *rfds_fd,
    fd_set *write_fd)
{
    char buf[1024];
    int reader;
    memset(buf, 0, 1024);
    reader = read(att->player_att[player].client_socket, buf, sizeof(buf));
    if (reader <= 0) {
        remove_player(att, player, rfds_fd, write_fd);
    } else {
        printf("inputs: %s", buf);
        queue_parser(att, player, buf);
        graphical_parser_gen(att, player, buf);
    }
    return 0;
}

int new_client(socket_handle_t *att)
{
    struct sockaddr_in infos;
    int ns;
    socklen_t info_size = sizeof(infos);
    ns = accept(att->listenfd, (struct sockaddr *)&(infos), &info_size);
    if (ns < 0) {
        perror("Error: accept");
        exit(84);
    }
    for (int i = 0; i < att->max_clients; i++) {
        if (att->player_att[i].client_socket == 0) {
            att->player_att[i].client_socket = ns;
            att->player_att[i].is_graphical = 0;
            send_message(att, "WELCOME", i);
            break;
        }
    }
    return 0;
}

int sock_update(socket_handle_t *att)
{
    int sd;
    fd_set rfds_fd = att->rfds_master;
    fd_set write_fd = att->write_master;
    int sd_max;
    int reader_sel = set_rfds(&sd_max, att, &rfds_fd, &write_fd);

    if (reader_sel < 0)
        perror("Select Error\n");
    if (FD_ISSET(att->listenfd, &rfds_fd)) {
        new_client(att);
    }
    for (int i = 0; i < att->max_clients; i++) {
        sd = att->player_att[i].client_socket;
        if (FD_ISSET(sd, &rfds_fd) && sd != 0) {
            client_new_inputs(att, i, &rfds_fd, &write_fd);
        }
    }
    return 0;
}