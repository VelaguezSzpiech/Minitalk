/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:03:19 by vszpiech          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:21 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "client_helper.h"
#include <unistd.h>  // For usleep

int send_bit(pid_t server_pid, int bit)
{
    int signal;

    if (bit == 0)
        signal = SIGUSR1;
    else
        signal = SIGUSR2;
    if (kill(server_pid, signal) == -1)
        return -1;
    // Introduce a small delay to prevent signal loss
    usleep(100);
    return 0;
}

int send_char(pid_t server_pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        if (send_bit(server_pid, (c >> bit) & 1) == -1)
            return -1;
        bit--;
    }
    return 0;
}

int send_message(pid_t server_pid, const char *message)
{
    size_t i;

    i = 0;
    while (message[i])
    {
        if (send_char(server_pid, message[i]) == -1)
            return -1;
        i++;
    }
    // Send null terminator to indicate end of message
    if (send_char(server_pid, '\0') == -1)
        return -1;
    return 0;
}
