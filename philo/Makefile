# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 09:49:37 by jkauker           #+#    #+#              #
#    Updated: 2024/01/22 10:37:51 by jkauker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
SRC		= ./src/philosopher.c \
            ./src/main.c \
			./src/monitoring.c \
            ./utils/ft_atoi.c \
			./utils/time.c
# FLAGS	= -Wall -Wextra -Werror -pthread

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -pthread -c $< -o $@

$(NAME): $(SRC:.c=.o)
	$(CC) -Wall -Wextra -Werror -pthread $^ -o $@

clean:
	rm -rf ./src/*.o
	rm -rf ./utils/*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all