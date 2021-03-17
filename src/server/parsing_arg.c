/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** parsing_arg
*/

#include "parsing_arg.h"

argment_t usage(argment_t list);

argment_t parsing_port(char **argv, argment_t list, int i)
{
    if (strcmp(argv[i], "-p") == 0) {
        if (argv[i + 1] && atoi(argv[i + 1])) {
            list.port = atoi(argv[i + 1]);
        } else if (atoi(argv[i + 1]) < 0) {
            printf("\n-p option only accepts valid ports\n\n");
            list = usage(list);
        } else
            list = usage(list);
    }
    return list;
}

argment_t parsing_c(char **argv, argment_t list, int i)
{
    if (strcmp(argv[i], "-c") == 0) {
        if (argv[i + 1] && atoi(argv[i + 1]))
            list.nb_clients = atoi(argv[i + 1]);
        else if (atoi(argv[i + 1]) < 1) {
            printf("\n-c option only accepts integer values"
            " greater or equal to 1\n\n");
            list = usage(list);
        }
        else
            list = usage(list);
    }
    return list;
}

argment_t parsing_f(char **argv, argment_t list, int i)
{
    if (strcmp(argv[i], "-f") == 0) {
        if (argv[i + 1] && atoi(argv[i + 1]))
            list.freq = atoi(argv[i + 1]);
        else if (atoi(argv[i + 1]) < 2 && atoi(argv[i + 1]) > 10000) {
            printf("\n-f option only accepts integer values"
            " between 2 and 10000\n\n");
            list = usage(list);
        }
        else
            list = usage(list);
    }
    return list;
}

argment_t parsing_x(char **argv, argment_t list, int i)
{
    if (strcmp(argv[i], "-x") == 0) {
        if (argv[i + 1] && atoi(argv[i + 1]) <= 30 && atoi(argv[i + 1]) >= 10)
            list.width = atoi(argv[i + 1]);
        else if (atoi(argv[i + 1]) > 30 || atoi(argv[i + 1]) < 10) {
            printf("\n-x option only accepts integer values "
            "between 10 and 30\n\n");
            list = usage(list);
        }
        else
            list = usage(list);
    }
    return list;
}

argment_t parsing_y(char **argv, argment_t list, int i)
{
    if (strcmp(argv[i], "-y") == 0) {
        if (argv[i + 1] && atoi(argv[i + 1]) <= 30 && atoi(argv[i + 1]) >= 10)
            list.height = atoi(argv[i + 1]);
        else if (atoi(argv[i + 1]) > 30 || atoi(argv[i + 1]) < 10) {
            printf("\n-y option only accepts integer values "
            "between 10 and 30\n\n");
            list = usage(list);
        }
        else
            list = usage(list);
    }
    return list;
}