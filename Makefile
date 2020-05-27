##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

all: client server

server:
	@make -C server/

client:
	@make -C client/

clean:
	@make clean -C server/
	@make clean -C client/

fclean:
	@make fclean -C server/
	@make fclean -C client/

re: fclean all

.PHONY: clean re fclean all server client