# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 09:49:37 by jkauker           #+#    #+#              #
#    Updated: 2024/01/22 09:52:48 by jkauker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
SRC		= philo.c
OBJ		= $(SRC:.c=.o)
FLAGS	= -Wall -Wextra -Werror -pthread

all: $(NAME)

%.o: %.c
	@$(CC) -c $< -o $@

$(NAME):
	$(CC) -Wall -Wextra -Werror -pthread -o $(NAME) philo.c

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all