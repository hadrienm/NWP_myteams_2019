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

typedef struct messages_s {
    char uuid[SIZE_ID];
    char message[DEFAULT_BODY_LENGTH];
    int timestamp;
}messages_t;

typedef struct cpr_message_list_s {
    struct cpr_message_list_s *next;
    messages_t message;
}cpr_message_list_t;

typedef struct corresponding_s {
    struct corresponding_s *next;
    cpr_message_list_t *msg_list;
    char uuid1[SIZE_ID];
    char uuid2[SIZE_ID];
}corresponding_t;

typedef struct client_list_s {
    struct client_list_s *next;
    char name[DEFAULT_NAME_LENGTH];
    char uuid[SIZE_ID];
}client_list_t;

typedef struct replies_s {
    struct replies_s *next;
    char body[DEFAULT_BODY_LENGTH];
    char user_uuid[SIZE_ID];
    int timestamp;
}replies_t;

typedef struct thread_s {
    struct thread_s *next;
    replies_t *reply;
    char name[DEFAULT_NAME_LENGTH];
    char description[DEFAULT_BODY_LENGTH];
    char uuid[SIZE_ID];
    char sender[(SIZE_ID + DEFAULT_NAME_LENGTH + 1)];
    char *path;
    int timestamp;
}thread_t;

typedef struct channel_s {
    struct channel_s *next;
    thread_t *thread;
    char name[DEFAULT_NAME_LENGTH];
    char description[DEFAULT_DESCRIPTION_LENGTH];
    char uuid[SIZE_ID];
    char *path;
    int timestamp;
}channel_t;

typedef struct team_s {
    struct team_s *next;
    channel_t *channel;
    char **user_subscribe;
    char name[DEFAULT_NAME_LENGTH];
    char description[DEFAULT_DESCRIPTION_LENGTH];
    char uuid[SIZE_ID];
    char *path;
    int timestamp;
}team_t;

typedef struct client_connection_s {
    struct client_connection_s *next;
    statut_t status;
    char *uuid;
    char *readbuffer;
    char *name;
    char *description;
    char *use_path;
    void *answer;
    size_t answer_size;
    size_t read_size;
    int socket;
}client_t;

typedef struct server {
    team_t *team;
    client_list_t *client_list;
    corresponding_t *crp_list;
    struct sockaddr_in address;
    client_t *client;
    fd_set readfds;
    fd_set writefds;
    int port;
    int master_socket;
}server_data;

extern void (* const command[])(client_t *, server_data **);
extern const char *command_name[];
extern const char *command_description[];
extern const char *rfc_message[];

/* Link list function */

bool init_server_data(server_data **server);
void add_node_back(client_t **client, int);
void add_node_front(client_t ** c, int);
void free_useless(client_t **client, bool);
void display_list(server_data *server);

/* Server function */

void add_replies_load(thread_t **thread, char *path);
void create_thread(thread_t *thread);
void create_replies(thread_t *thread);
void add_thread_load(channel_t **channel);
void add_channel_load(team_t **team);
char **read_after_line1(char *path, char *path2);
char **copy_array(char **array);
char **list_files(void);
int init_server(server_data *server);
void handle_fd(server_data **server);
void handle_new_connection(server_data **server);
void free_server_data(server_data **server);
void server_loop(server_data *server);
void get_binary(server_data **server);
void load_client(client_list_t **client);
void load_server(server_data **);
void load_messages(corresponding_t **);
void add_corresponding(corresponding_t **, char **, char **);
void add_message_to_list(cpr_message_list_t **, char **);
void push_client_list(client_list_t *);
void push_corresponding_list(corresponding_t *);
void load_all(server_data **server);
void make_save(server_data *server);
void delete_load(server_data **server);

/* Command */

void help(client_t *, server_data **);
void login(client_t *, server_data **);
void logout(client_t *, server_data **);
void users(client_t *, server_data **);
void user(client_t *, server_data **);
void send_c(client_t *, server_data **);
void messages(client_t *, server_data **);
void subscribe(client_t *, server_data **);
void subscribed(client_t *, server_data **);
void unsubscribe(client_t *, server_data **);
void use(client_t *, server_data **);
void create(client_t *, server_data **);
void list(client_t *, server_data **);
void info(client_t *, server_data **);

/* gestion arguement function*/

/* send subfunction */

command_status_t set_send_rfc(int status, char id[SIZE_ID]);
void send_rfc(client_t **client, command_status_t rfc, size_t index);
void set_send_s(client_t **client, ctos_send_t sender, client_t **all);
void save_message(ctos_send_t sender, char *uuid, corresponding_t **cpr_list);

/* subfuncion of login command */

command_status_t set_login_rfc(int status);
size_t set_user_send(client_t **, stoc_login_t, client_t **);
void login_send_rfc(client_t **client, command_status_t rfc, size_t index);
void set_login_brodcast(stoc_login_t login, client_t **all, int socket);
void add_node_to_client_list(client_list_t **, char **);

/* logout subfunction */
command_status_t set_logout_rfc(int status);
void set_logout_broadcast(stoc_logout_t logout, client_t **all, int socket);
void logout_send_rfc(client_t **client, command_status_t rfc, size_t index);
void set_logout(client_t **client, client_t **all);

/* unsubscribe subfunction */

char **create_broadcast_list(char *path);
char *found_path_team(char team_id[SIZE_ID]);
command_status_t unsubscribe_set_rfc(int status, char team_id[SIZE_ID]);
int found_team(char team_id[SIZE_ID], char *user_id, server_data **server);
int determine_length_int(int c);
void unsubscribe_set_broadcast(stoc_unsubscribe_t, char[SIZE_ID], char *, \
server_data **);
void unsubscribe_send_rfc(client_t **, command_status_t, size_t);
void set_unsubscribe_success(client_t **, char[SIZE_ID], server_data **);

/* messages subfunction */

char *list_conversation(char *, char *, corresponding_t *);
size_t size_of_list(messages_list_t *list);
bool found_conversation(char id[SIZE_ID], char *user_id, corresponding_t *);
void free_message_list(messages_list_t **list);
void init_message_list(messages_list_t **messages_list, char *line);
void send_message_rfc(int status, client_t **client, char id[SIZE_ID]);
void messages_success(client_t **, char[SIZE_ID], corresponding_t *);

/* subfunction of user command*/

void user_send_success(stoc_user_t, command_status_t, client_t **);
void user_send_rfc(client_t **client, command_status_t rfc, size_t index);
command_status_t set_rfc(int status, char user_id[SIZE_ID]);

/* subscribe subfunction */

command_status_t subscribe_set_rfc(int status, char team_id[SIZE_ID]);
stoc_subscribe_t set_subscribe(char *, char team_id[SIZE_ID]);
void subscribe_send_rfc(client_t **client, command_status_t rfc, size_t index);
void subscribe_broadcast(stoc_subscribe_t, char *, server_data **server);
void realloc_buffer(client_t **client, size_t size);

/* users subfunction */

command_status_t users_set_rfc(int);
size_t size_of_users_list(users_list_t **list);
int check_users_is_log(char *user_id, client_t *all);
void create_users_list(client_t **, server_data *, users_list_t **);
void free_users_list(users_list_t **list);
void send_succes_list(client_t **, server_data *);
void users_send_rfc(client_t **, command_status_t, size_t);
void users_send_success(stoc_users_t, command_status_t, client_t **);

/* subscribed subfunction */

char **subscribed_create_teams_list(server_data *, char *);
char **subscribed_create_users_list(char[SIZE_ID], server_data *);
command_status_t subscribed_set_rfc(int, char[SIZE_ID]);
size_t send_subscribed_answere(client_t **, subscribed_list_t *);
bool check_team(char[SIZE_ID], server_data *);
void subscribed_send_rfc(client_t **, command_status_t, size_t);
void subscribed_create_user_link_list(client_t **, server_data *, \
subscribed_list_t **, char **);
void subscribed_create_teams_link_list(client_t **, \
subscribed_list_t **, char **);
void send_unsubscribe_brodcast(void *buffer, char team_list[SIZE_ID], \
client_t **all, char **client_team_list);

/* list subfunction */

team_t *find_team_for_replies(server_data **s, char *path);
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
void list_channel(server_data **s, client_t ** c);
void list_thread(server_data **s, client_t ** c);
void list_repli(server_data **s, client_t ** c);

/* help subfunction */

command_status_t set_help_rfc(int status);
void help_send(client_t **client, stoc_help_t help);

/* use subfunction */

void find_teams(char *str, server_data **, client_t ** client);
void find_channel(char *str, server_data **, client_t ** client);
void find_thread(char *str, server_data **, client_t ** client);

/* create subfunction */

void init_reply(thread_t **th);
channel_t *find_channel_path(team_t **team, char *path);
team_t *find_team_for_replies(server_data **s, char *path);
team_t *find_team(team_t **t, char *path);
command_status_t set_create_rfc(int status);
char **create_broadcast_subscribe_list(team_t *, char *);
char *get_uuid_parent_folder(char *path);
char *get_uuid_team(char *path);
void *create_set_broadcast_buffer(stoc_create_t c);
int add_teams(client_t ** client, ctos_create_t create, server_data **s, \
char *new_uuid);
int add_channel(client_t ** client, ctos_create_t create, server_data **s, \
char *new_uuid);
int add_thread(client_t ** client, ctos_create_t create, server_data **s, \
char *uuid);
stoc_create_t memset_all(ctos_create_t create, int local, client_t **cli);
int add_message(client_t ** client, ctos_create_t create, server_data **s, \
char *uuid);
int write_create_in_file(char *str, ctos_create_t create, char temp[10]);
int write_timestamp(char *str, char temp[10], \
ctos_create_t create, client_t **client);
bool verify_name(char *str);
void send_create(client_t **client, size_t index, stoc_create_t c);
void create_subscribe_broadcast(void *buffer, client_t **all, \
char **client_team_list);
void create_broadcast(client_t **client, client_t **all, void *buffer);
char *cut_path(char *path);
void *create_set_buffer_thread_message(team_t *t, thread_t *th);

/* info subfunction */

channel_t *find_channel_path(team_t **team, char *path);
thread_t *find_thread_for_replies(team_t **t, char *path);
void info_user(server_data **s, client_t **client, stoc_info_t info);
void info_team(server_data **s, client_t **client, stoc_info_t info);
void info_channel(server_data **s, client_t **client, stoc_info_t info);
void info_thread(server_data **s, client_t **client, stoc_info_t info);
void send_info(client_t **client, stoc_info_t info);

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
bool subscribe_read(team_t *team, char *uuid, char *team_uuid);
bool verify_if_folder_exist(char *path);
bool check_path_exist(char *, char *);
void free_array(char **array);
void send_message_rfc(int status, client_t **client, char id[SIZE_ID]);
void list_teams(server_data **s, client_t **client);
void free_path(client_t *client);
#endif /* !SERVER_H_ */
