/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 04:33:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/20 06:59:55 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

SDL_Rect	draw_button(char *image, SDL_Rect location, t_filler *data)
{
	SDL_Surface *img;
	SDL_Texture *bmp_texture;

	img = SDL_LoadBMP(image);
	bmp_texture = SDL_CreateTextureFromSurface(data->renderer, img);
	if (!img)
		ft_printf("Failed to load img Error: %s", SDL_GetError());
	SDL_RenderCopy(data->renderer, bmp_texture, NULL, &location);
	SDL_FreeSurface(img);
	SDL_DestroyTexture(bmp_texture);
	return (location);
}

void		ft_score(t_filler *filler, char *line)
{
	char **scoreline;

	scoreline = ft_strsplit(line, ' ');
	filler->score_1 = ft_strdup(scoreline[3]);
	ft_strdel(&line);
	ft_free2d((void**)scoreline);
	get_next_line(0, &line);
	scoreline = ft_strsplit(line, ' ');
	filler->score_2 = ft_strdup(scoreline[3]);
}

/*
** Reading stdin to see whether more moves were made or the game is over.
** "Plateau" is contained in the line that shows the size of the board and
** is only displayed if the game is still running.
*/

int			game_over(t_filler *filler)
{
	char	*line;
	int		ret;

	line = NULL;
	while (!ft_strstr(line, "Plateau") && !ft_strstr(line, "=="))
	{
		ft_strdel(&line);
		ret = get_next_line(0, &line);
		if (ret == -1)
			ft_error("GNL error\n");
		if (!ret)
			break ;
	}
	if (ft_strstr(line, "Plateau"))
	{
		ft_strdel(&line);
		return (0);
	}
	else
	{
		ft_score(filler, line);
		ft_strdel(&line);
		return (1);
	}
}

void		show_score(t_filler *data)
{
	text_to_window(data, (SDL_Color){0, 255, 0, 100}, data->score_1,\
	(int[]){data->win_width - 520, WIN_HT * 0.05 + 75});
	text_to_window(data, (SDL_Color){0, 255, 0, 100}, data->score_2,\
	(int[]){data->win_width - 520, WIN_HT * 0.05 + 200});
	SDL_RenderPresent(data->renderer);
}
