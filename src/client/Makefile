##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile to build project
##

CC		=	g++

CFLAGS		=	-Wall -Wextra

SRC		=	main.cpp			\
			SocketHandle.cpp	\
			IA.cpp				\
			Parseur.cpp			\
			CommandManager.cpp	\
			GUI.cpp

OBJ     	=       $(SRC:.cpp=.o)

NAME    	=       zappy_ai

TMS_HDR =	../../include/client

INCLUDE	= 	-I$(TMS_HDR)

LIB = -lsfml-graphics -lsfml-window -lsfml-system

RM		=	rm -f

%.o: %.cpp
			$(CC) -g -c $< $(CFLAGS) $(INCLUDE) -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB)

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
