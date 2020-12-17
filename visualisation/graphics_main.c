/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/17 04:11:19 by ksuomala         ###   ########.fr       */
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



void	events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
	}
}

/*
** start initializes SDL and TTF. Calling get_data to get player data and
** window size. background draws the board and writes the player names on the
** screen and returns the renderer.
*/

void	play(t_filler *data)
{
	while (!(data->game_over = game_over(data)))
	{
		events();
		data->board = get_board(data->h, data->w);
		background(data);
		game_to_window(data);
	}
	background(data);
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
	data.win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_CENTERED, (float)data.w / data.h * WIN_HT + 420, WIN_HT, 0);
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
