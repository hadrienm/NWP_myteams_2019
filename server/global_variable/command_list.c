/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_list
*/

#include "server.h"

const char *command_name[] = {
    "/HELP",
    "/LOGIN",
    "/LOGOUT",
    "/USERS",
    "/USER",
    "/SEND",
    "/MESSAGES",
    "/SUBSCRIBE",
    "/SUBSCRIBED",
    "/UNSUBSCRIBE",
    "/USE",
    "/CREATE",
    "/LIST",
    "/INFO",
    NULL
};

const char *command_description[] = {
    "/help : show help\r\n",
    "/login [username] : set the username used by client\r\n",
    "/logout : disconnect the client from the server\r\n",
    "/users : get the list of all users that exist on the domain\r\n",
    "/user [user_uuid] : get information about a user\r\n",
    "/send [user_uuid] [message_body] : send a message to a user\r\n",
    "/messages [user_uuid] : list all messages exchange with an user\r\n",
    "/subscribe [team_uuid] : subscribe to the event of a team and"
    "its sub directories (enable reception of all events from a team)r\n",
    "/subscribed [team_uuid] : list all subscribed teams or list"
    " all users subscribed to a team\r\n",
    "/unsubscribe [team_uuid] : unsubscribe from a team\r\n",
    "/use [team_uuid] [channel_uuid] [thread_uuid] : use specify"
    " a context team/channel/thread\r\n",
    "When the context is not defined (/use):\n"
    "• /create [team_name] [team_description] : create a new team\n"
    "When team_uuid is defined (/use team_uuid):\n"
    "• /create [channel_name] [channel_description] : create a new channel\n"
    "When team_uuid and channel_uuid are defined (/use team_id channel_"
    "uuid):\n• /create [thread_title] [thread_message] : create a new thread\n"
    "When team_uuid, channel_uuid and thread_uuid are defined"
    "(/use team_uuid channel_uuid thread_uuid):\n"
    "• /create [comment_body] : create a new reply\r\n",
    "When the context is not defined (/use):\n"
    "• /list : list all existing teams\n"
    "When team_uuid is defined (/use team_uuid):\n"
    "• /list : list all existing channels\n"
    "When team_uuid and channel_uuid are defined (/use team_uuid"
    "channel_uuid):\n• /list : list all existing threads\n"
    "When team_uuid, channel_uuid and thread_uuid are defined"
    " (/use team_uuid channel_uuid thread_uuid):\n"
    "• /list : list all existing replies\r\n",
    "When the context is not defined (/use):\n"
    "• /info : display currently logged user infos\n"
    "When team_uuid is defined (/use team_uuid):\n"
    "• /info : display currently selected team infos\n"
    "When team_uuid and channel_uuid are defined (/use team_uuid"
    "channel_uuid):\n• /info : display currently selected channel infos\n"
    "When team_uuid, channel_uuid and thread_uuid are defined"
    " (/use team_uuid channel_uuid thread_uuid):\n"
    "• /info : display currently selected thread infos\r\n",
    NULL};