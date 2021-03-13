# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:20:59 by ksuomala          #+#    #+#              #
#    Updated: 2021/03/13 15:22:37 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME = ksuomala.filler

SRCS = main.c \
	get_board.c \
	minesweeper.c \
	next_move.c \

SRCS_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJ_DIR = obj/

LIBFT = libft/libft.a

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

F_SANITIZE = -fsanitize=address

LINKS = -L libft -lft

INCL = -I includes -I libft

VISUALIZER = visualizer

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LINKS)
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
	rm -rf $(OBJ_DIR)
	echo "*.o removed!"

fclean: clean
	make -s -C libft fclean
	make -s -C visualisation fclean
	rm -f $(NAME)
	echo "Targets removed!"

re: fclean all

$(VISUALIZER):
	@make -s -C visualisation

leaks:
	$(CC) $(FLAGS) -c $(addprefix $(SRCS_DIR), $(SRCS)) $(INCL) $(F_SANITIZE)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS) $(F_SANITIZE)
