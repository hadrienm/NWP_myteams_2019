##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

NAME	= ../myteams_cli

CC	= gcc -g

RM	= rm -f

SRCS	= ./main.c \
			../utils_function/my_const_strcat.c \
			../utils_function/str_to_word_array.c \
			../utils_function/make_random_uuid.c \
			../utils_function/my_strcmp.c \
			../utils_function/free_array.c \
			./argument_gestion.c \
			./global_variable/ptr_function.c \
			./global_variable/command_list.c \
			./client_gestion/client_loop.c \
			./client_gestion/close_client.c \
			./client_gestion/init_client.c \
			./client_gestion/set_client.c \
			./client_gestion/get_command.c \
			./command/help.c \
			./command/login.c \
			./command/logout.c \
			./command/users.c \
			./command/user.c \
			./command/send.c \
			./command/messages.c \
			./command/subscribe.c \
			./command/subscribed.c \
			./command/unsubscribe.c \
			./command/use.c \
			./command/create/create.c \
			./command/create/event_create.c \
			./command/list.c \
			./command/info.c \
			./command/rfc.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/ -I ../include -I ../libs/myteams/
CFLAGS += -Wextra -g

LDFLAGS = -luuid -l myteams -L ../libs/myteams/

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
