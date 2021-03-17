/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Debian]
** File description:
** queue
*/

#include "queue.h"

int queue_parser2(socket_handle_t *att, int player, char *buf, int freq);

int queue_parser3(socket_handle_t *att, int player, char *buf, int freq);

int queue_parser4(socket_handle_t *att, int player, char *buf, int freq);

struct timeval get_esimation_time(int time_unit, int freq)
{
    struct timeval new;
    unsigned long usec, sec;

    gettimeofday(&new, NULL);
    usec = (1000000 *time_unit) / freq;
    sec = usec/1000000;
    usec -= sec * 1000000;
    new.tv_sec += sec;
    new.tv_usec += usec;
    if (new.tv_usec >= 1000000) {
        new.tv_usec -= 1000000;
        new.tv_sec += 1;
    }
    return new;
}

queue_time_t *add_to_queue(queue_time_t *queue, char *buf, int unit, int freq)
{
    if (queue == NULL) {
        queue = malloc(sizeof(queue_time_t));
        queue->message = calloc(1024, sizeof(char));
        queue->message = strcpy(queue->message, buf);
        queue->time_to_execute = get_esimation_time(unit, freq);
        queue->next = NULL;
        return queue;
    }
    queue->next = add_to_queue(queue->next, buf, unit, freq);
    return queue;
}

void queue_parser(socket_handle_t *att, int player, char *buf)
{
    player_attach_t *playerb = &att->player_att[player];
    queue_time_t *queue = (att->player_att[player].queue);
    for (int i = 0; i < att->nb_teams && playerb->team == NULL; i++) {
        if ((!strncmp(buf, att->teams[i]->name, strlen(att->teams[i]->name))
            && att->teams[i]->actual_client < att->teams[i]->max_client)
            || !strncmp(buf, "GRAPHIC", 7)) {
            att->player_att[player].queue =
            add_to_queue(queue, buf, 0, att->freq);
            return;
        }
    }
    if (playerb->is_graphical == 1)
        return;
    if (playerb->team == NULL) {
        send_message(att, "ko", player);
        return;
    } else if (queue_parser2(att, player, buf, att->freq) == 0 &&
                queue_parser3(att, player, buf, att->freq) == 0 &&
                queue_parser4(att, player, buf, att->freq) == 0) {
        send_message(att, "ko", player);
    }
}

int queue_parser2(socket_handle_t *att, int player, char *buf, int freq)
{
    queue_time_t *queue = att->player_att[player].queue;
    if (strncmp("Left\n", buf, 5) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    } else if (strncmp("Look\n", buf, 5) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    }
    if (strncmp("Inventory\n", buf, 10) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 1, freq);
        return 1;
    }
    if (strncmp("Broadcast", buf, strlen("Broadcast")) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    } else if (strncmp("Fork\n", buf, 5) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 42, freq);
        return 1;
    }
    return 0;
}

int queue_parser3(socket_handle_t *att, int player, char *buf, int freq)
{
    queue_time_t *queue = att->player_att[player].queue;
    if (strncmp("Eject\n", buf, 5) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    } else if (strncmp("Set ", buf, 4) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    }
    if (strncmp("Take ", buf, 5) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, freq);
        return 1;
    } else if (strncmp("Incantation\n", buf, 12) == 0) {
        att->player_att[player].player->R = 1;
        att->player_att[player].queue = add_to_queue(queue, buf, 300, freq);
        return 1;
    }
    if (strncmp("Right\n", buf, 6) == 0) {
        att->player_att[player].queue = add_to_queue(queue, buf, 7, att->freq);
        return 1;
    }
    return 0;
}