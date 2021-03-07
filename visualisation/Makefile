# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2021/03/07 22:04:31 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = graphics_main.c \
	game_data.c \
	draw_to_window.c \
	score.c \
	events.c

OBJS = $(SRCS:.c=.o)

LIBSDL2 = $(LIB_DIR)libSDL2/lib/libSDL2.a

LIBSDL2_TTF = $(LIB_DIR)libSDL2_ttf/lib/libSDL2_ttf.a

LIBSDL_MAKE = libSDL2/Makefile

LIB_DIR = lib/

CC = gcc

C_FLAGS = -g -Wall -Wextra -Werror `$(LIB_DIR)libSDL2/bin/sdl2-config --cflags`

L_FLAGS = `$(LIB_DIR)libSDL2/bin/sdl2-config --libs` -lSDL2_ttf

LINKS = -L ../libft -lft -L lib/libSDL2_ttf/lib

#FLAGS = -g -Wall -Wextra -Werror `sdl2-config --cflags --libs`

#LINKS = -L ../libft -lft -lSDL2_image -lSDL2_ttf -lm

INCL = -I ../includes -I ../libft -I libSDL2/include -I SDL2_ttf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(L_FLAGS) $(INCL) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(SRCS) $(LIBSDL2_TTF)
	@echo "Compiling..."
	$(CC) $(C_FLAGS) $(INCL) -c $(SRCS)
	@echo "*object files created!"

clean:
	@rm -f $(OBJS)
	@echo "*.o removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=libSDL2 clean; fi
	@echo "*LIBSDL2 cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=libSDL2 distclean; fi
	rm -rf $(LIB_DIR)
	@echo "*LIBSDL2 removed!"

$(LIBSDL2_TTF): $(LIBSDL2) | $(LIB_DIR)
	cd SDL2_ttf && ./configure --prefix=$(abspath $(LIB_DIR)libSDL2_ttf) --disable-shared
	$(MAKE) --directory=SDL2_ttf
	$(MAKE) --directory=SDL2_ttf install

$(LIBSDL2): $(LIB_DIR)
	cd libSDL2 && ./configure --prefix=$(abspath $(LIB_DIR)libSDL2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libSDL2
	$(MAKE) --directory=libSDL2 install


$(LIB_DIR):
	mkdir $(@)

re: fclean all
