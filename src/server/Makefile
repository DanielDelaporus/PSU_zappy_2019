##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile to build project
##

CC		=	gcc

CFLAGS		=	-Wall -Wextra

SRC		=	main.c		   \
			parsing_arg.c \
			server.c \
			socket.c \
			socket_bis.c \
			map.c \
			team.c \
			player.c \
			socket_parser.c \
			queue.c \
			queue_bis.c \
			lifetime.c \
			graphical_parser.c \
			player_commands/incantation.c \
			player_commands/inventory_2.c \
			player_commands/inventory_3.c \
			player_commands/inventory.c \
			player_commands/look.c \
			player_commands/moves.c \
			player_commands/moves_2.c

OBJ     	=       $(SRC:.c=.o)

NAME    	=       zappy_server

TMS_HDR =	../../include/server

INCLUDE	= 	-I$(TMS_HDR)

RM		=	rm -f

%.o: %.c
			$(CC) -g -c $< $(CFLAGS) $(INCLUDE) -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)
		$(RM) *~
		$(RM) *#

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

auteur:
		echo $(USER) > auteur

.PHONY:
			all clean fclean re

.SILENT:
			all clean fclean re
