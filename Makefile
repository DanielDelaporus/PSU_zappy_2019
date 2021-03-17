##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

RM	=	rm -f

all: 	client server

server:
		make -C ./src/server
		mv ./src/server/zappy_server ./

client:
		make -C ./src/client
		mv ./src/client/zappy_ai ./

clean:
		make clean -C ./src/server
		make clean -C ./src/client

fclean:
		make -C ./src/server fclean
		make -C ./src/client fclean
		$(RM) zappy_server
		$(RM) zappy_ai

re: fclean all

.PHONY:
	all server client clean fclean re

.SILENT:
	all server client clean fclean re