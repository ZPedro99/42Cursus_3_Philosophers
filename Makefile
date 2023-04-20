# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:18:30 by jomirand          #+#    #+#              #
#    Updated: 2023/04/20 16:46:32 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
NAME_BONUS = philosophers_bonus

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
PFLAGS = -pthread
RM = rm -rf

SRCS = 	philo/main.c\
		philo/monitoring.c\
		philo/philos_and_forks.c\
		philo/simulation.c\
		philo/utils.c\
		philo/utils_libft.c\
		philo/verifs.c\

SRCS_BONUS = 	bonus/so_long_bonus.c\
				bonus/load_map_bonus.c\
				bonus/moves_bonus.c\
				bonus/utils_map_bonus.c\
				bonus/utils_bonus.c\
				bonus/utils2_bonus.c\
				bonus/utils3_bonus.c\
				bonus/utils4_bonus.c\
				bonus/utils5_bonus.c\
				bonus/free_bonus.c\
				bonus/free2_bonus.c\
				bonus/enemies.c\

OBJS = $(SRCS:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(PFLAGS) -o $(NAME)

bonus: $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(PFLAGS) -o $(NAME_BONUS)

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