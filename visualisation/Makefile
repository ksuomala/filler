# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2021/03/10 22:33:08 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = graphics_main.c \
	game_data.c \
	draw_to_window.c \
	score.c \
	events.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIBSDL2 = $(LIB_DIR)libSDL2/lib/libSDL2.a

LIBSDL2_TTF = $(LIB_DIR)lib/libSDL2_ttf.a

LIBSDL_MAKE = libSDL2/Makefile

LIB_DIR = lib/

OBJ_DIR = obj/

SRCS_DIR = srcs/

OS_NAME := $(shell uname -s | tr A-Z a-z)

CC = gcc

C_FLAGS = -g -Wall -Wextra -Werror `$(LIB_DIR)libSDL2/bin/sdl2-config --cflags`

L_FLAGS = `$(LIB_DIR)libSDL2/bin/sdl2-config --libs` -lSDL2_ttf $(LINUX_LINK)

LINUX_LINK =

ifeq "$(OS_NAME)" "linux"
	LINUX_LINK = -lfreetype
endif

LINKS = -L ../libft -lft -L lib/lib

#FLAGS = -g -Wall -Wextra -Werror `sdl2-config --cflags --libs`

#LINKS = -L ../libft -lft -lSDL2_image -lSDL2_ttf -lm

INCL = -I ../includes -I ../libft -I lib/libSDL2/include -I lib/include/SDL2

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o ../$(NAME) $(L_FLAGS) $(INCL) $(LINKS)
	@echo "executable compiled!"

$(OBJS): $(addprefix $(SRCS_DIR), $(SRCS)) $(LIBSDL2_TTF) $(OBJ_DIR)
	@echo "Compiling..."
	$(CC) $(C_FLAGS) $(INCL) -c $(addprefix $(SRCS_DIR), $(SRCS))
	@mv $(SRCS:.c=.o) $(OBJ_DIR)/
	@echo "*object files created!"

clean:
	@rm -f $(OBJS)
	@echo "*.o removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=SDL2/libSDL2 clean; fi
	@echo "*LIBSDL2 cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=SDL2/libSDL2 distclean; fi
	rm -rf $(LIB_DIR)
	@echo "*LIBSDL2 removed!"

$(LIBSDL2_TTF): $(LIBSDL2)
	@echo "Configuring SDL2_ttf..."
	cd SDL2/SDL2_ttf && ./configure --prefix=$(abspath $(LIB_DIR))
	@echo "SDL2_ttf configured!"
	@echo "bulding SDL2_ttf"
	$(MAKE) --directory=SDL2/SDL2_ttf
	$(MAKE) --directory=SDL2/SDL2_ttf install
	@echo "SDL2_ttf built!"

$(LIBSDL2): $(LIB_DIR)
	@echo "Configuring SDL2..."
	cd SDL2/libSDL2 && ./configure --prefix=$(abspath $(LIB_DIR)libSDL2) --disable-shared --disable-video-wayland
	@echo "SDL2 configured"
	@echo "Building SDL2..."
	$(MAKE) --directory=SDL2/libSDL2
	$(MAKE) --directory=SDL2/libSDL2 install
	@echo "SDL2 built!"

$(LIB_DIR):
	mkdir $(@)

$(OBJ_DIR):
	mkdir $(@)

re: fclean all
