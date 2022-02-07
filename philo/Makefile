# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 12:11:44 by ldurante          #+#    #+#              #
#    Updated: 2022/02/07 18:47:42 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
MAKE = make
DEBUG = -g3 -fsanitize=address

# COLORS #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
GREY = \033[2;37m
MAGENTA = \033[0;35m
CURSIVE = \033[3m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #

SRCS =	srcs/main.c \
		srcs/threads.c \
		srcs/time.c \
		srcs/utils.c \
		srcs/routine.c \
		srcs/free.c

OBJS = $(SRCS:.c=.o)

# RULES #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@echo "$(GREY) philo compiled $(GREEN) ✔✔✔ $(NO_COLOR)"

test1: all
	@echo "$(YELLOW) **** Running philo test1 **** $(NO_COLOR)"
	./philo 1 800 200 200

test2: all
	@echo "$(YELLOW) **** Running philo test2 **** $(NO_COLOR)"
	./philo 5 800 200 200
	
test3: all
	@echo "$(YELLOW) **** Running philo test3 **** $(NO_COLOR)"
	./philo 5 800 200 200 7

test4: all
	@echo "$(YELLOW) **** Running philo test4 **** $(NO_COLOR)"
	./philo 4 410 200 200

test5: all
	@echo "$(YELLOW) **** Running philo test5 **** $(NO_COLOR)"
	./philo 4 310 200 200

clean:
	@clear
	@$(RM) $(OBJS)
	@echo "$(RED) **** object files deleted **** $(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED) **** philo deleted **** $(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean test1 test2 test3 test4 test5

.SILENT: $(OBJS)