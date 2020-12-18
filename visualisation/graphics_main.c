/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/18 03:35:48 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ft_error(int msg)
{
	ft_printf("error %d", msg);
	exit(0);
}

/*
** start initializes SDL and TTF. Calling get_data to get player data and
** window size. background draws the board and writes the player names on the
** screen and returns the renderer.
*/

void	play(t_filler *data, t_buttons button, t_game game,\
char **frames[10000])
{
	frames[game.frame] = get_board(data->h, data->w);
	game.fps = 50;
	game.moves = 1;
	while (game.paused || !(data->game_over = game_over(data)))
	{
		events(&game, button);
		data->board = frames[game.frame];
		button = background(data, game);
		game_to_window(data, game.fps);
		if (!game.paused)
		{
			game.frame += 1;
			if (game.frame == game.moves)
			{
				frames[game.frame] = get_board(data->h, data->w);
				game.moves += 1;
			}
		}
	}
	background(data, game);
	show_score(data);
	SDL_Delay(5000);
	SDL_DestroyWindow(data->win);
}

void	start(void)
{
	t_filler	data;
	t_buttons	button;
	t_game		game;
	char		**frames[10000];

	ft_bzero(frames, sizeof(char**) * 10000);
	ft_bzero(&game, sizeof(game));
	ft_bzero(&data, sizeof(t_filler));
	data = get_data();
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_printf("Error initializing SDL : %s", SDL_GetError());
	if (TTF_Init() == -1)
		ft_printf("Failed to initialize TTF\n");
	data.win_width = (float)data.w / data.h * WIN_HT + 420;
	data.win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_CENTERED, data.win_width, WIN_HT, 0);
	if (!data.win)
		ft_printf("error creating window");
	data.renderer = SDL_CreateRenderer(data.win, -1, SDL_RENDERER_ACCELERATED);
	data.font = TTF_OpenFont("../fonts/ubuntu/Ubuntu-M.ttf", 24);
	play(&data, button, game, frames);
}

int		main(void)
{
	start();
	ft_printf("THE END\n");
	SDL_Quit();
	return (0);
}
