/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 03:35:11 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/18 03:35:25 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

int		inside_rect(int x, int y, SDL_Rect dest)
{
	if (x < dest.x || x > dest.x + dest.w)
		return (0);
	if (y < dest.y || y > dest.y + dest.h)
		return (0);
	return (1);
}

void	keypress(t_game *game, SDL_Event event, t_buttons rect)
{
	if (inside_rect(event.button.x, event.button.y, rect.pause))
	{
		if (game->paused)
			game->paused = 0;
		else
			game->paused = 1;
	}
	else if (game->paused && inside_rect(event.button.x, event.button.y,\
	rect.previous))
	{
		if (game->frame)
			game->frame -= 1;
	}
	else if (game->paused && inside_rect(event.button.x, event.button.y,\
	rect.next))
	{
		if (game->frame < game->moves - 1)
			game->frame += 1;
	}
}

void	events(t_game *game, t_buttons rect)
{
	SDL_Event		event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.key.keysym.sym == SDLK_DOWN)
			game->fps += 3;
		if (event.key.keysym.sym == SDLK_UP)
			game->fps -= 3;
		if (game->fps < 1)
			game->fps = 1;
		if (event.type == SDL_MOUSEBUTTONDOWN)
			keypress(game, event, rect);
	}
}
