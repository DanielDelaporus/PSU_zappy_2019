/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** graphical_parser
*/

#ifndef GRAPHICAL_PARSER_H_
#define GRAPHICAL_PARSER_H_

#include "server.h"

typedef struct socket_handle socket_handle_t;

void graphical_parser_gen(socket_handle_t *att, int player, char *buf);
void send_graph(socket_handle_t *att, char *buf);

#endif /* !GRAPHICAL_PARSER_H_ */
