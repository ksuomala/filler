#ifndef _WINDOW_H
# define _WINDOW_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <fcntl.h>
#include "filler.h"

typedef struct		s_filler
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	char			**board;
	int				h;
	int				w;
	int				square_size;
	char			*p1;
	char			*p2;
	char			*score_1;
	char			*score_2;
}					t_filler;


void			ft_error(int msg);
char			**get_board(size_t height, size_t width);
t_filler		get_data(SDL_Window *w);
char			**cpy_board(char **board, size_t n);
void			show_score(t_filler *data);

void			square_to_window(t_filler *filler, int y, int x);
int				game_to_window(t_filler *filler);
SDL_Renderer	*background(t_filler *data);
void			text_to_window(SDL_Renderer *renderer, SDL_Color color, char *message, int location[1]);

#endif
