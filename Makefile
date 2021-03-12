# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:20:59 by ksuomala          #+#    #+#              #
#    Updated: 2021/03/12 18:25:42 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME = ksuomala.filler

SRCS = main.c \
	get_board.c \
	minesweeper.c \
	next_move.c \

SRCS_DIR = src/

# Is the dependency right?

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJ_DIR = obj/

LIBFT = libft/libft.a

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

LINKS = -L libft -lft

INCL = -I includes -I libft

VISUALIZER = visualizer

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(LIBFT) $(addprefix $(SRCS_DIR), $(SRCS)) | $(OBJ_DIR)
	@echo "Compiling..."
	$(CC) $(FLAGS) -c $(addprefix $(SRCS_DIR), $(SRCS)) $(INCL)
	@echo "Compiled. Moving .o files..."
	mv $(SRCS:.c=.o) $(OBJ_DIR)

$(LIBFT):
	@make -s -C libft

$(OBJ_DIR):
	mkdir $(@)

clean:
	make -s -C libft clean
	make -s -C visualisation clean
	rm -f $(OBJS)
	echo "*.o removed!"

fclean: clean
	make -s -C libft fclean
	make -s -C visualisation fclean
	rm -f $(NAME)
	echo "Targets removed!"

re: fclean all

$(VISUALIZER):
	@make -s -C visualisation
