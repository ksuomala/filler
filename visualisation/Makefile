# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2020/12/16 04:45:59 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = graphics_main.c \
	game_data.c \
	draw_to_window.c \
	score.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = `sdl2-config --cflags --libs`

LINKS = -lSDL2_image -lSDL2_ttf -lm

INCL = -I ../includes -I ../libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) ../libft/libft.a -o $(NAME) $(FLAGS) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(SRCS)
	@echo "Compiling..."
	$(CC) $(FLAGS) -c $(SRCS) $(INCL) $(LINKS)
	@echo "*object files created"

clean:
	@rm -f $(OBJS)
	@echo "*.o removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"

re: fclean all
