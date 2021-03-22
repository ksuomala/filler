# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2021/03/22 20:52:03 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME = ../visualizer
SRCS = graphics_main.c \
	game_data.c \
	draw_to_window.c \
	score.c \
	events.c
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
LIBSDL2 = $(LIB_DIR)libSDL2/lib/libSDL2.a
LIBSDL2_TTF = $(LIB_DIR)lib/libSDL2_ttf.a
LIBSDL_MAKE = SDL2/libSDL2/Makefile
LIBFT = ../libft/libft.a
BUILD_DIR = SDL2/
LIB_DIR = lib/
F_SANITIZE = -fsanitize=leak -fsanitize=address
OBJ_DIR = obj/
SRCS_DIR = srcs/
SDL_ARCHIVE = SDL2-2.0.14
TTF_ARCHIVE = SDL2_ttf-2.0.15
UNZIP_SDL = $(BUILD_DIR)libSDL2
UNZIP_TTF = $(BUILD_DIR)SDL2_ttf
OS_NAME := $(shell uname -s | tr A-Z a-z)
CC = gcc
C_FLAGS = -g -Wall -Wextra -Werror `$(LIB_DIR)libSDL2/bin/sdl2-config --cflags`
L_FLAGS = `$(LIB_DIR)libSDL2/bin/sdl2-config --libs` -lSDL2_ttf $(LINUX_LINK)
LINUX_LINK =

ifeq "$(OS_NAME)" "linux"
	LINUX_LINK = -lfreetype
endif

LINKS = -L ../libft -lft -L lib/lib -L lib/libSDL2/lib

#FLAGS = -g -Wall -Wextra -Werror `sdl2-config --cflags --libs`

#LINKS = -L ../libft -lft -lSDL2_image -lSDL2_ttf -lm

# rm -f

INCL = -I ../includes -I ../libft -I lib/libSDL2/include -I lib/include/SDL2

.PHONY: all clean fclean leaks re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LINKS) $(L_FLAGS) $(INCL)
	@echo "executable compiled!"

$(OBJS): $(addprefix $(SRCS_DIR), $(SRCS)) $(LIBSDL2_TTF) | $(OBJ_DIR) $(LIBFT)
	@echo "Compiling..."
	$(CC) $(C_FLAGS) $(INCL) -c $(addprefix $(SRCS_DIR), $(SRCS))
	@mv $(SRCS:.c=.o) $(OBJ_DIR)/
	@echo "*object files created!"

clean:
	@rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	@echo "*.o removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=SDL2/libSDL2 clean; fi
	@echo "*LIBSDL2 cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=SDL2/libSDL2 distclean; fi
	rm -rf $(LIB_DIR) $(BUILD_DIR)
	@echo "*LIBSDL2 removed!"

$(LIBSDL2_TTF): $(LIBSDL2) | $(UNZIP_TTF)
	@echo "Configuring SDL2_ttf..."
	cd SDL2/SDL2_ttf && ./configure --prefix=$(abspath $(LIB_DIR)) SDL2_CONFIG=$(abspath $(BUILD_DIR))
	@echo "SDL2_ttf configured!"
	@echo "bulding SDL2_ttf"
	$(MAKE) --directory=SDL2/SDL2_ttf
	$(MAKE) --directory=SDL2/SDL2_ttf install
	@echo "SDL2_ttf built!"

$(LIBSDL2): $(LIB_DIR) | $(UNZIP_SDL)
	@echo "Configuring SDL2..."
	cd SDL2/libSDL2 && ./configure --prefix=$(abspath $(LIB_DIR)libSDL2) --disable-shared --disable-video-wayland
	@echo "SDL2 configured"
	@echo "Building SDL2..."
	$(MAKE) --directory=SDL2/libSDL2
	$(MAKE) --directory=SDL2/libSDL2 install
	@echo "SDL2 built!"

$(LIBFT):
	make -C ../libft

$(LIB_DIR):
	mkdir $(@)

$(OBJ_DIR):
	mkdir $(@)

$(BUILD_DIR):
	mkdir $(@)

$(UNZIP_SDL): | $(BUILD_DIR)
	unzip $(SDL_ARCHIVE).zip
	mv $(SDL_ARCHIVE) $(UNZIP_SDL)
$(UNZIP_TTF): | $(BUILD_DIR)
	unzip $(TTF_ARCHIVE).zip
	mv $(TTF_ARCHIVE) $(UNZIP_TTF)

leaks:
	$(CC) $(C_FLAGS) $(F_SANITIZE) $(INCL) -c $(addprefix $(SRCS_DIR), $(SRCS))
	@$(CC) $(OBJS) -o $(NAME) $(L_FLAGS) $(F_SANITIZE) $(INCL) $(LINKS)

re: fclean all
