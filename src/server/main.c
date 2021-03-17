/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** Main function for zappy project
*/

#include <stdio.h>
#include <stdlib.h>
#include "parsing_arg.h"
#include "server.h"

argment_t usage(argment_t list)
{
    list.not_ok = 1;
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2)");
    printf(" ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit for execution of");
    printf(" actions\n");
    return list;
}

int check_arg(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
        return 1;
    return 0;
}

argment_t parsing_n(char **argv, argment_t list, int i)
{
    if (strcmp(argv[i], "-n") == 0 && argv[i + 1] && argv[i + 2]) {
        int nb = 1;
        for (; argv[i + nb] != NULL && argv[i + nb][0] != '-'; nb++);
        nb--;
        if (nb < 2) {
            list = usage(list);
            return list;
        }
        list.TeamName = calloc(nb, sizeof(char *));
        for (int j = 0; j < nb; j++)
        {
            list.TeamName[j] = calloc(sizeof(argv[i + 1]), sizeof(char));
            list.TeamName[j] = argv[i + j + 1];
        }
        list.nb_teams = nb;
    }
    else if (strcmp(argv[i], "-n") == 0 &&
        (!argv[i + 1] || !argv[i + 2]))
        list = usage(list);
    return list;
}

int main(int argc, char *argv[])
{
    argment_t list;
    if (check_arg(argc, argv)) {
        list = usage(list);
    } else {
        list.freq = 100;
        list.not_ok = 0;
        for (int i = 1; i < argc; i++) {
            list = parsing_port(argv, list, i);
            list = parsing_x(argv, list, i);
            list = parsing_y(argv, list, i);
            list = parsing_c(argv, list, i);
            list = parsing_f(argv, list, i);
            list = parsing_n(argv, list, i);
        }
        if (list.not_ok)
            return 1;
        return launch_server(&list);
    }
}
