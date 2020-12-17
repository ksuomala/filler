/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/17 21:19:50 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

// Read the stdout/in, take the size of the board. Board width and height. Divide the screen. Most of it should be the board and that should scale
// according to the size so it always takes the same area of the screen. I want to make bars on the right side with the player colors, names and
// scores. Maybe buttons where I could change the players.


void	ft_error(int msg)
{
	ft_printf("error %d", msg);
	exit(0);
}

int		inside_rect(int x, int y, SDL_Rect dest)
{
	if (x < dest.x || x > dest.x + dest.w)
		return (0);
	if (y < dest.y || y > dest.y + dest.h)
		return (0);
	return (1);
}

void	events(t_game *game, t_buttons rect)
{
	SDL_Event		event;
	t_coordinate	click;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			if (inside_rect(event.button.x, event.button.y, rect.pause))
			{
				if (game->paused)
					game->paused = 0;
				else
					game->paused = 1;
			}


	}
}

/*
** start initializes SDL and TTF. Calling get_data to get player data and
** window size. background draws the board and writes the player names on the
** screen and returns the renderer.
*/

void	play(t_filler *data)
{
	t_buttons	button;
	t_game		game;
	char		**frames[10000];


	ft_bzero(frames, sizeof(char**) * 10000);
	ft_bzero(&game, sizeof(game));
	frames[game.frame] = get_board(data->h, data->w);
	game.fps = 1000 / 20;
	game.paused = 0;
	while (game.paused || !(data->game_over = game_over(data)))
	{
		events(&game, button);
		data->board = frames[game.frame];
		button = background(data, game);
		game_to_window(data, game.fps);
		if (!game.paused)
		{
			game.frame += 1;
			frames[game.frame] = get_board(data->h, data->w);
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

	ft_bzero(&data, sizeof(t_filler));
	data = get_data(data.win);
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
	play(&data);
}

int	main(void)
{
	start();
	SDL_Quit();
	return (0);
}
