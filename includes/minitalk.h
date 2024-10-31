/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:02:56 by vszpiech          #+#    #+#             */
/*   Updated: 2024/10/31 16:02:58 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
#define MINITALK_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INITIAL_CAPACITY 1024

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
typedef struct s_server
{
    char            *message;
    int             bit_count;
    unsigned char   current_char;
    size_t          index;
    size_t          capacity;
    pid_t           client_pid;
}                   t_server;

// Function prototypes
void handle_signal(int signo, siginfo_t *info, void *context);
void process_received_char(siginfo_t *info);
int append_char(t_server *server, char c);
void reset_server_state(void);
void send_acknowledgment(pid_t client_pid);
int initialize_message(void);

#endif // MINITALK_H
