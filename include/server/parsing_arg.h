/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** server
*/

#ifndef PARSING_H_
#define PARSING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct argment_s {
    int port;
    int width;
    int height;
    int nb_clients;
    int nb_teams;
    char **TeamName;
    int freq;
    int not_ok;
} argment_t;

argment_t parsing_port(char **argv, argment_t list, int i);
argment_t parsing_c(char **argv, argment_t list, int i);
argment_t parsing_f(char **argv, argment_t list, int i);
argment_t parsing_x(char **argv, argment_t list, int i);
argment_t parsing_y(char **argv, argment_t list, int i);

#endif