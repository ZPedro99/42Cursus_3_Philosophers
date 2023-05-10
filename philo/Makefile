# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:18:30 by jomirand          #+#    #+#              #
#    Updated: 2023/05/10 15:36:57 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
RM = rm -rf

SRCS = 	main.c\
		monitoring.c\
		philos_and_forks.c\
		simulation.c\
		utils.c\
		utils_libft.c\
		verifs.c\

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