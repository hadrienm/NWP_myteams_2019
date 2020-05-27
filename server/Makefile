##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

NAME	= ../myteams_server

CC	= gcc

RM	= rm -f

SRCS	= ./main.c \
			../utils_function/my_const_strcat.c \
			../utils_function/str_to_word_array.c \
			../utils_function/make_random_uuid.c \
			../utils_function/my_strcmp.c \
			../utils_function/free_array.c \
			../utils_function/size_array.c \
			./ls_utils.c \
			./server_gestion/set_server.c \
			./server_gestion/init.c \
			./server_gestion/delete.c \
			./server_gestion/server_loop.c \
			./server_gestion/get_binary.c \
			./argument_gestion.c \
			./link_list/add_node.c \
			./link_list/delete_node.c \
			./link_list/utilities_function.c \
			./global_variable/ptr_function.c \
			./global_variable/command_list.c \
			./global_variable/rfc_message.c \
			./global_variable/size.c \
			./command/help/help.c \
			./command/help/send_help.c \
			./command/login/login.c \
			./command/login/login_broadcast.c \
			./command/login/login_check_user.c \
			./command/login/send_login.c \
			./command/logout/logout.c \
			./command/logout/send_logout.c \
			./command/logout/broadcast_logout.c \
			./command/users/users.c \
			./command/users/utils.c \
			./command/users/link_list.c \
			./command/users/delete.c \
			./command/users/users_send.c \
			./command/user/user.c \
			./command/user/user_send.c \
			./command/send/send.c \
			./command/send/send_error.c \
			./command/send/send_success.c \
			./command/send/save_messages.c \
			./command/message/messages.c \
			./command/message/get_messages.c \
			./command/message/message_error.c \
			./command/message/message_success.c \
			./command/message/link_list_messages.c \
			./command/subscribe/subscribe.c \
			./command/subscribe/send_subscribe.c \
			./command/subscribe/broadcast_subscribe.c \
			./command/subscribed/subscribed.c \
			./command/subscribed/users_link_list.c \
			./command/subscribed/teams_link_list.c \
			./command/subscribed/send_subscribed.c \
			./command/subscribed/create_list.c \
			./command/unsubscribe/unsubscribe.c \
			./command/unsubscribe/send_unsubscribe.c \
			./command/unsubscribe/broadcast/unsubscribe_broadcast.c \
			./command/unsubscribe/broadcast/send_unsubscribe_broadcast.c \
			./command/unsubscribe/broadcast/create_user_list.c \
			./command/unsubscribe/broadcast/found_team.c \
			./command/use/use.c \
			./command/use/find_use.c \
			./command/create/broadcast/create_broadcast.c \
			./command/create/broadcast/send_broadcast.c \
			./command/create/create.c \
			./command/create/create_channel.c \
			./command/create/create_get_uuid.c \
			./command/create/create_replies.c \
			./command/create/create_teams.c \
			./command/create/create_thread.c\
			./command/create/send_create.c \
			./command/list/list.c \
			./command/list/get_info.c \
			./command/list/link_list.c \
			./command/list/list_info.c \
			./command/list/send_list.c \
			./command/info.c

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
