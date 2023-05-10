# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:18:30 by jomirand          #+#    #+#              #
#    Updated: 2023/04/28 15:15:35 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philos
NAME_BONUS = philos_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -rf

SRCS = 	philo/main.c\
		philo/monitoring.c\
		philo/philos_and_forks.c\
		philo/simulation.c\
		philo/utils.c\
		philo/utils_libft.c\
		philo/verifs.c\

SRCS_BONUS = 	philo_bonus/main.c \
				philo_bonus/utils_bonus.c \
				philo_bonus/utils_libft_bonus.c \
				philo_bonus/utils2_libft_bonus.c \
				philo_bonus/verifs_bonus.c \
				philo_bonus/initialize_bonus.c \
				philo_bonus/simulation_bonus.c \
				philo_bonus/monitoring_bonus.c \

OBJS = $(SRCS:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

clean_bonus:
	@$(RM) $(OBJS_BONUS)
	@$(RM) $(NAME_BONUS)

fclean: clean clean_bonus
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re: fclean all