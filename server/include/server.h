/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include "my_teams.h"
#include "client_to_server_command.h"
#include "server_to_client_command.h"
#include "logging_server.h"

typedef enum code_rfc_s {
    CODE_200,
    CODE_201,
    CODE_400,
    CODE_401,
    CODE_402,
    CODE_403,
    CODE_404,
    CODE_405,
    CODE_500,
    CODE_501,
    CODE_502,
    CODE_503,
    CODE_504,
    CODE_505,
    CODE_506
}code_rfc_t;

typedef enum status_s {
    CONNECT,
    DISCONNECT,
    UNDEFINED
}statut_t;

typedef struct client_connection_s {
    struct client_connection_s *next;
    char *uuid;
    char *readbuffer;
    char *name;
    char *description;
    char *use_path;
    void *answer;
    size_t answer_size;
    size_t read_size;
    int socket;
    statut_t status;
}client_t;

typedef struct server {
    struct sockaddr_in address;
    client_t *client;
    fd_set readfds;
    fd_set writefds;
    int port;
    int master_socket;
}server_data;

extern void (* const command[])(client_t *, client_t **);
extern const char *command_name[];
extern const char *command_description[];
extern const char *rfc_message[];
extern const size_t header_size;
extern const size_t rfc_size;
extern const size_t rfc_content_size;
extern const size_t user_size;
extern const size_t user_content_size;
extern const size_t subscribe_size;
extern const size_t subscribe_content_size;
extern const size_t users_size;
extern const size_t users_content_size;
extern const size_t subscribed_size;
extern const size_t subscribed_content_size;
extern const size_t list_size;
extern const size_t list_content_size;
extern const size_t logout_size;
extern const size_t logout_content_size;
extern const size_t login_size;
extern const size_t login_content_size;
extern const size_t unsubscribe_size;
extern const size_t unsubscribe_content_size;
extern const size_t send_size;
extern const size_t send_content_size;
extern const size_t help_size;
extern const size_t help_content_size;
extern const size_t create_size;
extern const size_t create_content_size;

/* Link list function */
bool init_server_data(server_data **server);
void add_node_back(client_t **client, int);
void add_node_front(client_t ** c, int);
void free_useless(client_t **client, bool);
void display_list(server_data *server);

/* Server function */
int init_server(server_data *server);
void handle_fd(server_data **server);
void handle_new_connection(server_data **server);
void free_server_data(server_data **server);
void server_loop(server_data *server);
void get_binary(server_data **server);
void load_client(void);

/* Command */

/* show help */
void help(client_t *client, client_t **);
/* set the username used by client */
void login(client_t *client, client_t **);
/* disconnect the client from the server */
void logout(client_t *client, client_t **);
/* get the list of all users that exist on the domain */
void users(client_t *client, client_t **);
/* get information about a user */
void user(client_t *client, client_t **);
/* send a message to a user */
void send_c(client_t *client, client_t **);
/* list all messages exchange with an user */
void messages(client_t *client, client_t **);
/* subscribe to the event of a team and its sub directories
(enable reception of all events from a team) */
void subscribe(client_t *client, client_t **);
/* list all subscribed teams or list all users subscribed to a team */
void subscribed(client_t *client, client_t **);
/* unsubscribe from a team */
void unsubscribe(client_t *client, client_t **);
/* use specify a context team/channel/thread */
void use(client_t *client, client_t **);
void create(client_t *client, client_t **);
void list(client_t *client, client_t **);
void info(client_t *client, client_t **);

/* gestion arguement function*/

/* subfunction of send command */

command_status_t set_send_rfc(int status, char id[SIZE_ID]);
void send_rfc(client_t **client, command_status_t rfc, size_t index);
void set_send_s(client_t **client, ctos_send_t sender, client_t **all);
void write_message_inside_file(ctos_send_t sender, char *user_id);

/* subfuncion of login command */

command_status_t set_login_rfc(int status);
size_t set_user_send(client_t **, stoc_login_t, client_t **);
void login_send_rfc(client_t **client, command_status_t rfc, size_t index);
bool check_is_user_already_exist(client_t **client, ctos_login_t receive);
bool add_user(client_t *client);
void set_login_brodcast(stoc_login_t login, client_t **all, int socket);

/* subfunction of logout function */
command_status_t set_logout_rfc(int status);
void set_logout_broadcast(stoc_logout_t logout, client_t **all, int socket);
void logout_send_rfc(client_t **client, command_status_t rfc, size_t index);
void set_logout(client_t **client, client_t **all);

/* subfunction of unsubscribe function */

char **create_broadcast_list(char *path);
char *found_path_team(char team_id[SIZE_ID]);
command_status_t unsubscribe_set_rfc(int status, char team_id[SIZE_ID]);
int found_team(char team_id[SIZE_ID], char *user_id);
int determine_length_int(int c);
void unsubscribe_send_rfc(client_t **client, command_status_t rfc, \
size_t index);
void set_unsubscribe_success(client_t **client, char team_id[SIZE_ID], \
client_t **all);
void unsubscribe_set_broadcast(stoc_unsubscribe_t, char[SIZE_ID], \
char *user_id, client_t **all);

/* subfunction of message function */

char *message_create_path(char id[SIZE_ID], char *user_id);
char *list_conversation(char *path);
size_t size_of_list(messages_list_t *list);
void free_message_list(messages_list_t **list);
void init_message_list(messages_list_t **messages_list, char *line);
void send_message_rfc(int status, client_t **client, char id[SIZE_ID]);
void messages_success(client_t **client, char id[SIZE_ID]);

/* subfunction of user command*/

void user_send_success(stoc_user_t, command_status_t, client_t **);
void user_send_rfc(client_t **client, command_status_t rfc, size_t index);
command_status_t set_rfc(int status, char user_id[SIZE_ID]);

/* subfunction of subscribe command */

command_status_t subscribe_set_rfc(int status, char team_id[SIZE_ID]);
stoc_subscribe_t set_subscribe(char *, char team_id[SIZE_ID]);
void subscribe_send_rfc(client_t **client, command_status_t rfc, size_t index);
void subscribe_broadcast(stoc_subscribe_t, char *, client_t **);
void realloc_buffer(client_t **client, size_t size);

/* subfunction of users function */
command_status_t users_set_rfc(int);
size_t size_of_users_list(users_list_t **list);
int check_users_is_log(char *user_id, client_t **all);
bool create_users_list(client_t **, client_t **, users_list_t **);
void free_users_list(users_list_t **list);
void send_succes_list(client_t **client, client_t **all);
void users_send_rfc(client_t **, command_status_t, size_t);
void users_send_success(stoc_users_t, command_status_t, client_t **);

/* subfunction of subscribed function */

char **subscribed_create_teams_list(char **, char *);
char **subscribed_create_users_list(char team_id[SIZE_ID]);
command_status_t subscribed_set_rfc(int, char[SIZE_ID]);
size_t send_subscribed_answere(client_t **, subscribed_list_t *);
bool check_team(char[SIZE_ID]);
void subscribed_send_rfc(client_t **, command_status_t, size_t);
void subscribed_create_user_link_list(client_t **, client_t **, \
subscribed_list_t **, char **);
void subscribed_create_teams_link_list(client_t **, client_t **, \
subscribed_list_t **, char **);
void send_unsubscribe_brodcast(void *buffer, char team_list[SIZE_ID], \
client_t **all, char **client_team_list);

/* subfunction of list function */

char *list_all_folders(char *path);
char *list_replies(char *path);
char *get_all_info(char *name, char *path);
char *get_name(char *str);
location_t determine_use(char *str);
command_status_t list_set_rfc(int status, char team_id[SIZE_ID]);
size_t list_link_size(list_list_t *list);
void send_list_success(client_t **client, char *str);
void list_send_rfc(client_t **client, command_status_t rfc, size_t index);
void add_node_list(list_list_t **list, char **details, location_t which);
void create_link_list(char *str, list_list_t **link_list, client_t **client);

/* help subfunction */

command_status_t set_help_rfc(int status);
void help_send(client_t **client, stoc_help_t help);

/* use subfunction */

void find_teams(client_t ** client, char *str);
void find_channel(client_t ** client, char *str);
void find_thread(client_t ** client, char *str);

/* create subfunction */

command_status_t set_create_rfc(int status);
char **create_broadcast_subscribe_list(char *path, char * user_uid);
char *get_uuid_parent_folder(char *path);
char *get_uuid_team(char *path);
void *create_set_broadcast_buffer(stoc_create_t c);
int add_teams(client_t ** client, ctos_create_t create, client_t **all, \
char *new_uuid);
int add_channel(client_t ** client, ctos_create_t create, client_t **all, \
char *new_uuid);
int add_thread(client_t ** client, ctos_create_t create, client_t **all, \
char *uuid);
stoc_create_t memset_all(ctos_create_t create, int local, client_t **cli);
int add_message(client_t **client, ctos_create_t create, client_t **all);
int write_create_in_file(char *str, ctos_create_t create, char temp[10]);
int write_timestamp(char *str, char temp[10], \
ctos_create_t create, client_t **client);
bool verify_name(char *str);
void send_create(client_t **client, size_t index, stoc_create_t c);
void create_subscribe_broadcast(void *buffer, client_t **all, \
char **client_team_list);
void create_broadcast(client_t **client, client_t **all, void *buffer);

/* utils funcition */

char **str_to_word_array(char *str, char *delimiter);
char **ls_directories(char *path);
char **ls_files(char *path);
char *make_random_uuid(void);
char *separate_line(char *line);
char *my_strcat(char *str, char *str2);
char *get_info_user(char *uuid);
char *get_description(char *path);
size_t size_array(char **array);
int handle_args(server_data *server, char **av, int ac);
int my_strcmp(char *str1, char *str2);
int count_in_str(char *str, char c);
bool subscribe_read(char *path, char *uuid);
bool verify_if_folder_exist(char *path);
void free_array(char **array);
void send_message_rfc(int status, client_t **client, char id[SIZE_ID]);

#endif /* !SERVER_H_ */
