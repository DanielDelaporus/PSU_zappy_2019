/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** queue
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include "socket.h"
#include <time.h>
#include <sys/time.h>

typedef struct socket_handle socket_handle_t;

typedef struct queue_time
{
    struct timeval time_to_execute;
    char *message;
    struct queue_time *next;
} queue_time_t;

struct timeval get_esimation_time(int time_unit, int freq);
void queue_parser(socket_handle_t *att, int player, char *buf);
struct timeval get_esimation_time_s(int time_unit, int freq,
struct timeval new);

void graphical_ppo(socket_handle_t *att, int player);

#endif /* !QUEUE_H_ */
