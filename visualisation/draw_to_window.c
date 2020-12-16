/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:11:16 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/17 01:33:20 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void				square_to_window(t_filler *filler, int y, int x)
{
	SDL_Rect	square;

	if (filler->board[y][x] == 'O')
		SDL_SetRenderDrawColor(filler->renderer, 0, 0, 255, 255);
	else if (filler->board[y][x] == 'o')
		SDL_SetRenderDrawColor(filler->renderer, 50, 50, 255, 230);
	else if (filler->board[y][x] == 'X')
		SDL_SetRenderDrawColor(filler->renderer, 255, 0, 0, 255);
	else if (filler->board[y][x] == 'x')
		SDL_SetRenderDrawColor(filler->renderer, 255, 50, 50, 230);
	square.h = filler->square_size;
	square.w = square.h;
	square.x = WIN_HT * 0.05 + square.h * x;
	square.y = WIN_HT * 0.05 + square.h * y;
	SDL_RenderFillRect(filler->renderer, &square);
}

int					game_to_window(t_filler *filler)
{
	int				x;
	int				y;
	static char		**current;

	x = -1;
	y = -1;
	while(++y < filler->h)
	{
		while(++x < filler->w)
		{
//			ft_putchar(filler->board[y][x]); //test
			if (filler->board[y][x] != '.')
				square_to_window(filler, y, x);
		}
	//	ft_n(1); //test
		x = -1;
	}
//	text_to_window(filler->renderer, (SDL_Color){120, 120, 120}, "yees", (int[]){(filler->w + 1) * filler->square_size, filler->h * filler->square_size * 0.35}); //test
	if (!(current = cpy_board(filler->board, filler->h + 1)))
		ft_error(5);
	SDL_RenderPresent(filler->renderer);
	return (0);
}

void				text_to_window(t_filler *data, SDL_Color color, char *message, int location[1])
{
//	TTF_Font *font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;

//	SDL_RenderPresent(renderer);
//	font = TTF_OpenFont("../fonts/ubuntu/Ubuntu-M.ttf", 24);
	// if (font)
	// {
	// 	ft_error(5);
	// 	ft_printf("Unable to OpenFOnt\n");
	// }
	surface = TTF_RenderText_Solid(data->font, message, color);
	ft_printf("test\n");
	if (!surface)
		ft_printf("Unable to get surfaceMessage!\n");
	texture = SDL_CreateTextureFromSurface(data->renderer, surface);
	if (!texture)
		ft_printf("Unable to create Texture!");
	TTF_SizeText(data->font, message, &rect.w, &rect.h);
	rect.x = location[0] + 210 - rect.w / 2;
	rect.y = location[1];

	SDL_RenderCopy(data->renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

t_coordinate		players_to_window(t_filler *data, SDL_Renderer *renderer)
{
	t_coordinate new;

	new.x = (data->w + 1)* data->square_size;
	new.y = (data->h + 1) * data->square_size * 0.2;
	ft_printf("x = %d y = %d\n", new.x, new.y);
	text_to_window(data, (SDL_Color){0, 0, 255}, data->p1,\
	(int[]){new.x, data->h * data->square_size * 0.25});
	text_to_window(data, (SDL_Color){100, 100, 100}, "VS",\
	(int[]){new.x, data->h  * data->square_size * 0.5});
	text_to_window(data, (SDL_Color){255, 0, 0}, data->p2,\
	(int[]){new.x, data->h * data->square_size * 0.75});
	return(new);
}

SDL_Renderer		*background(t_filler *data)
{
	SDL_Rect		board;

	SDL_SetRenderDrawColor(data->renderer, 25, 25, 25, 255);
	SDL_RenderClear(data->renderer);
	board.h = WIN_HT * 0.9;
	data->square_size = board.h / data->h;
	board.w = data->square_size * data->w;
	board.x = WIN_HT * 0.05;
	board.y = WIN_HT * 0.05;
	SDL_SetRenderDrawColor(data->renderer, 69, 69, 69, 255);
	SDL_RenderFillRect(data->renderer, &board);
	players_to_window(data, data->renderer);
	SDL_RenderPresent(data->renderer);
	return (data->renderer);
}
