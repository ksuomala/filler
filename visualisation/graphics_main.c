/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/23 08:52:13 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ft_error(const char *msg)
{
	ft_printf("error %s", msg);
	exit(0);
}

void	cleanup(t_filler *data, char **frames[], int moves_made)
{
	int i;

	i = 0;
	SDL_DestroyWindow(data->win);
	SDL_DestroyRenderer(data->renderer);
	ft_strdel(&data->p1);
	ft_strdel(&data->p2);
	ft_strdel(&data->score_1);
	ft_strdel(&data->score_2);
	while (i < moves_made)
	{
		ft_putgrid_eol(frames[i], 0);
		ft_printf("i = %d, moves = %d\n", i, moves_made);
		ft_free2d((void**)frames[i]);
		i++;
	}
}

/*
** Running the game loop, until x is pressed to close the game. In
** the loop we are reading events, getting the board from stdin, and
** re-rendering the screen for each frame.
*/

void	play(t_filler *data, t_buttons button, int fd, char **frames[10000])
{
	t_game game;

	ft_bzero(&game, sizeof(t_game));
	frames[game.frame] = get_board(data->h, data->w, fd);
	game.fps = 100;
	game.moves = 1;
	game.paused = 1;
	game_over(data, fd);
	while (!data->quit)
	{
		data->quit = events(&game, button);
		data->board = frames[game.frame];
		button = background(data, game);
		game_to_window(data, game.fps);
		if (!game.paused && !data->game_over && !data->quit)
		{
			game.frame += 1;
			if (game.frame == game.moves)
			{
				frames[game.frame] = get_board(data->h, data->w, fd);
				game.moves += 1;
				data->game_over = game_over(data, fd);
			}
		}
	}
	cleanup(data, frames, game.moves);
}


/*
** Initialising data structures and SDL pointers
*/

void	start(int fd)
{
	t_filler	data;
	t_buttons	button;
	char		**frames[10000];

	ft_bzero(&frames, sizeof(char**) * 10000);
	ft_bzero(&data, sizeof(t_filler));
	data = get_data(fd);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_error(SDL_GetError());
	if (TTF_Init() == -1)
		ft_error(SDL_GetError());
	data.win_width = (float)data.w / data.h * WIN_HT + 420;
	data.win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_CENTERED, data.win_width, WIN_HT, 0);
	if (!data.win)
		ft_error(SDL_GetError());
	if (!(data.renderer = SDL_CreateRenderer(data.win, -1,\
	SDL_RENDERER_ACCELERATED)))
		ft_error(SDL_GetError());
	if (!(data.font = TTF_OpenFont("Ubuntu-M.ttf", 24)))
		ft_error(SDL_GetError());
	play(&data, button, fd, frames);
}

int		main(void)
{
	int fd;

	fd = open("visualizer_log.txt", O_RDWR);
	if (!fd)
		ft_error("failed to open file");
	start(fd);
	close(fd);
	return (0);
}
