# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:18:30 by jomirand          #+#    #+#              #
#    Updated: 2023/05/10 15:43:34 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
RM = rm -rf

SRCS = 	main.c \
		utils_bonus.c \
		utils_libft_bonus.c \
		utils2_libft_bonus.c \
		verifs_bonus.c \
		initialize_bonus.c \
		simulation_bonus.c \
		monitoring_bonus.c \

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re: fclean all