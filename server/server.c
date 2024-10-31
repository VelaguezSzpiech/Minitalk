/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:03:09 by vszpiech          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:13 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_server g_server = {
    .message = NULL,
    .bit_count = 0,
    .current_char = 0,
    .index = 0,
    .capacity = INITIAL_CAPACITY,
    .client_pid = 0
};

void handle_signal(int signo, siginfo_t *info, void *context)
{
    (void)context;
    if (g_server.client_pid == 0)
        g_server.client_pid = info->si_pid;

    if (signo == SIGUSR1)
        g_server.current_char = (g_server.current_char << 1);
    else if (signo == SIGUSR2)
        g_server.current_char = (g_server.current_char << 1) | 1;

    g_server.bit_count++;
    if (g_server.bit_count == 8)
    {
        process_received_char(info);
        g_server.bit_count = 0;
        g_server.current_char = 0;
    }
}

int main(void)
{
    struct sigaction sa;

    printf("Server PID: %d\n", getpid());
    sa.sa_sigaction = &handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("Error setting up SIGUSR1 handler");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("Error setting up SIGUSR2 handler");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        pause();
    }
    return 0;
}
