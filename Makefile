# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 14:08:38 by ksuomala          #+#    #+#              #
#    Updated: 2020/12/16 02:38:16 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ksuomala.filler

SRCS = main.c \
	get_board.c \
	minesweeper.c \
	next_move.c \

SRCS_DIR = src

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

OBJ_DIR = obj

LIBFT = libft/libft.a

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

LINKS = -L libft -lft

INCL = -I includes -I libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(LIBFT) $(addprefix $(SRCS_DIR)/, $(SRCS)) $(OBJ_DIR)
	@echo "Compiling..."
	$(CC) $(FLAGS) -c $(addprefix $(SRCS_DIR)/, $(SRCS)) $(INCL)
	@echo "Compiled. Moving .o files..."
	@mv $(SRCS:.c=.o) $(OBJ_DIR)/

$(LIBFT):
	@make -C libft

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "*.o removed!"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "Targets removed!"

re: fclean all
