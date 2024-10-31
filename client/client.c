/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:33:08 by vszpiech          #+#    #+#             */
/*   Updated: 2024/10/31 16:01:45 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "client_helper.h"

volatile sig_atomic_t g_ack_received = FALSE;

void handle_ack(int signo)
{
    if (signo == SIGUSR1)
        g_ack_received = TRUE;
}

int validate_arguments(int argc, char **argv, pid_t *server_pid)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <server_pid> \"<message>\"\n", argv[0]);
        return -1;
    }
    *server_pid = (pid_t)atoi(argv[1]);
    if (*server_pid <= 0)
    {
        fprintf(stderr, "Invalid server PID.\n");
        return -1;
    }
    return 0;
}

int setup_signal_handler(void)
{
    struct sigaction sa;

    sa.sa_handler = &handle_ack;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("Error setting up SIGUSR1 handler");
        return -1;
    }
    return 0;
}

void wait_for_acknowledgment(void)
{
    while (!g_ack_received)
        pause();
}

int main(int argc, char **argv)
{
    pid_t server_pid;

    if (validate_arguments(argc, argv, &server_pid) == -1)
        return EXIT_FAILURE;
    if (setup_signal_handler() == -1)
        return EXIT_FAILURE;
    if (send_message(server_pid, argv[2]) == -1)
    {
        perror("Failed to send message");
        return EXIT_FAILURE;
    }
    wait_for_acknowledgment();
    printf("Message sent and acknowledged by server.\n");
    return EXIT_SUCCESS;
}
