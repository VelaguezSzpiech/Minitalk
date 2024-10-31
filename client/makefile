# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yourname <youremail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 12:00:00 by yourname          #+#    #+#              #
#    Updated: 2024/04/27 12:00:00 by yourname         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = client.c client_helper.c
OBJ = $(SRC:.c=.o)
INC = ../includes/minitalk.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
