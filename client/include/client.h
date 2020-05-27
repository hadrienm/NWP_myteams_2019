/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include "my_teams.h"
#include "client_to_server_command.h"
#include "server_to_client_command.h"
#include "logging_client.h"

typedef struct client {
    char **command;
    char *name;
    char *ip;
    char *data;
    char *user_id;
    char *buffer;
    char *pending_command;
    ssize_t data_size;
    int port;
    int master_socket;
    struct sockaddr_in address;
    fd_set writefds;
    fd_set readfds;
}client_data;

char **str_to_word_array(char *str, char *delimiter);

extern void (* const command[])(client_data **client);
extern void (* const decrypt_command[])(stoc_header_t *, size_t, \
client_data **);
extern const char *command_name[];
extern volatile int stop;

void error(char *str);

/* Client function */

char *make_random_uuid(void);
int connect_client(client_data ** client);
void init_client(client_data **client);
void client_loop(client_data ** client);
void handle_fd(client_data **client);
void free_struct(client_data *client);
void free_command(client_data **client);

/* Argument gestion */

int handle_args(client_data *c, char **av, int ac);

/* Command */

/* show help */
void help(client_data **client);
/* set the username used by client */
void login(client_data **client);
/* disconnect the client from the server */
void logout(client_data **client);
/* get the list of all users that exist on the domain */
void users(client_data **client);
/* get information about a user */
void user(client_data **client);
/* send a message to a user */
void send_c(client_data **client);
/* list all messages exchange with an user */
void messages(client_data **client);
/* subscribe to the event of a team and its sub directories (enable reception
 of all events from a team) */
void subscribe(client_data **client);
/* list all subscribed teams or list all users subscribed to a team */
void subscribed(client_data **client);
/* unsubscribe from a team */
void unsubscribe(client_data **client);
/* use specify a context team/channel/thread */
void use(client_data **client);
void create(client_data **client);
void list(client_data **client);
void info(client_data **client);

/* Decrypt Command */

void help_decrypt(stoc_header_t *, size_t, client_data **);
void login_decrypt(stoc_header_t *, size_t, client_data **);
void logout_decrypt(stoc_header_t *, size_t, client_data **);
void users_decrypt(stoc_header_t *, size_t, client_data **);
void user_decrypt(stoc_header_t *, size_t, client_data **);
void send_decrypt(stoc_header_t *, size_t, client_data **);
void messages_decrypt(stoc_header_t *, size_t, client_data **);
void subscribe_decrypt(stoc_header_t *, size_t, client_data **);
void subscribed_decrypt(stoc_header_t *, size_t, client_data **);
void unsubscribe_decrypt(stoc_header_t *, size_t, client_data **);
void use_decrypt(stoc_header_t *, size_t, client_data **);
void create_decrypt(stoc_header_t *, size_t, client_data **);
void list_decrypt(stoc_header_t *, size_t, client_data **);
void info_decrypt(stoc_header_t *, size_t, client_data **);
void rfc_decrypt(stoc_header_t *, size_t, client_data **);

/* use subfunction */

void event_create(void *k, int index);

/* utils function */

size_t size_array(char **array);
char **get_client_command(char *line);
char *delete_useless(char *str, char *delimiter);
char *my_strcat(char *str, char *str2);
void free_array(char **array);
int my_strcmp(char *str1, char *str2);

typedef struct decrypt_subscribed_s
{
    char team_id[SIZE_ID];
    char user_id[SIZE_ID];
    char description[DEFAULT_DESCRIPTION_LENGTH];
    char name[DEFAULT_NAME_LENGTH];
    int timestamp;
    int status;
}decrypt_subscribed_t;

#endif /* !CLIENT_H_ */