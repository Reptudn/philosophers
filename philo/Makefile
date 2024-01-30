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

NAME	:= philo
CC		:= cc
SRC		:= ./src/philosopher.c \
            ./src/main.c \
            ./utils/ft_atoi.c \
FLAGS	:= -Wall -Wextra -Werror -pthread

all: $(NAME)

# %.o: %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC:.c=.o)
    @$(CC) $(FLAGS) $^ -o $(NAME)

clean:
    @rm -rf $(OBJ)

fclean: clean
    @rm -rf $(NAME)

re: fclean all