/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 01:37:27 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/18 03:40:30 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WINDOW_H
# define _WINDOW_H

# include <SDL2/SDL.h>
# include <SDL_ttf.h>
# include <fcntl.h>
# include "filler.h"

typedef	struct		s_buttons
{
	SDL_Rect		speed_up;
	SDL_Rect		speed_down;
	SDL_Rect		pause;
	SDL_Rect		previous;
	SDL_Rect		next;
}					t_buttons;

typedef struct		s_game
{
	t_buttons		rect;
	int				frame;
	int				paused;
	int				fps;
	int				moves;
}					t_game;

typedef struct		s_filler
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Rect		*speed_up;
	SDL_Rect		*speed_down;
	TTF_Font		*font;
	int				win_width;
	char			**board;
	int				h;
	int				w;
	int				game_over;
	int				square_size;
	char			*p1;
	char			*p2;
	char			*score_1;
	char			*score_2;
}					t_filler;

void				ft_error(int msg);
char				**get_board(size_t height, size_t width);
t_filler			get_data(void);
char				**cpy_board(char **board, size_t n);
void				show_score(t_filler *data);

void				square_to_window(t_filler *filler, int y, int x);
int					game_to_window(t_filler *filler, int fps);
t_buttons			background(t_filler *data, t_game game);
void				text_to_window(t_filler *data, SDL_Color color,\
char *message, int location[1]);

t_buttons			*ft_buttons(t_filler *data);
int					game_over(t_filler *filler);
SDL_Rect			draw_button(char *image, SDL_Rect location, t_filler *data);
void				draw_pause(t_filler *data);

void				events(t_game *game, t_buttons rect);

#endif
