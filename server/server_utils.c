/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:03:07 by vszpiech          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:08 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

extern t_server g_server;

int append_char(t_server *server, char c)
{
    char *new_message;

    if (server->index + 1 >= server->capacity)
    {
        server->capacity *= 2;
        new_message = realloc(server->message, server->capacity);
        if (!new_message)
            return -1;
        server->message = new_message;
    }
    server->message[server->index++] = c;
    return 0;
}

void reset_server_state(void)
{
    g_server.index = 0;
    g_server.capacity = INITIAL_CAPACITY;
    g_server.client_pid = 0;
}

void send_acknowledgment(pid_t client_pid)
{
    if (kill(client_pid, SIGUSR1) == -1)
    {
        perror("Failed to send acknowledgment");
        exit(EXIT_FAILURE);
    }
}

int initialize_message(void)
{
    g_server.message = malloc(g_server.capacity);
    if (!g_server.message)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    memset(g_server.message, 0, g_server.capacity);
    return 0;
}

void process_received_char(siginfo_t *info)
{
    if (g_server.current_char == '\0')
    {
        if (g_server.message)
        {
            g_server.message[g_server.index] = '\0';
            printf("Received message from PID %d: %s\n",
                   g_server.client_pid, g_server.message);
            free(g_server.message);
            g_server.message = NULL;
        }
        reset_server_state();
        send_acknowledgment(info->si_pid);
    }
    else
    {
        if (!g_server.message)
            initialize_message();
        if (append_char(&g_server, g_server.current_char) == -1)
        {
            perror("Failed to append character");
            free(g_server.message);
            exit(EXIT_FAILURE);
        }
    }
}
