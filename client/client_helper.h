/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_helper.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:03:22 by vszpiech          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:24 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HELPER_H
#define CLIENT_HELPER_H

#include <unistd.h>
#include <signal.h>

int send_bit(pid_t server_pid, int bit);
int send_char(pid_t server_pid, char c);
int send_message(pid_t server_pid, const char *message);

#endif // CLIENT_HELPER_H
