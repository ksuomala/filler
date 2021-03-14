/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 04:33:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/14 16:10:19 by ksuomala         ###   ########.fr       */
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
	if (SDL_RenderCopy(data->renderer, bmp_texture, NULL, &location) < 0)
		ft_error(SDL_GetError());
	SDL_FreeSurface(img);
	SDL_DestroyTexture(bmp_texture);
	return (location);
}

void		score(t_filler *filler, char *line)
{
	char **scoreline;

	ft_printf("%s\n", line); //test
	scoreline = ft_strsplit(line, ' ');
	if (!scoreline)
		ft_error("split fail \n");
	filler->score_1 = ft_strdup(scoreline[3]);
	if (!filler->score_1)
		ft_error("failed to allocate for score \n");
//	ft_strdel(&line);
	ft_free2d((void**)scoreline);
	if (get_next_line(0, &line) < 0)
		ft_error("GNL error\n");
	ft_printf("%s\n", line); //test
	scoreline = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (!scoreline)
		ft_error("failed to split score");
	filler->score_2 = ft_strdup(scoreline[3]);
	if (!filler->score_2)
		ft_error("failed to allocate for score2\n");
	ft_free2d((void**)scoreline);
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
		if (line)
			ft_strdel(&line);
		if (!(ret = get_next_line(0, &line)))
			break ;
		if (ret == -1)
			ft_error("GNL error\n");
	}
	if (ft_strstr(line, "Plateau"))
	{
		ft_strdel(&line);
		return (0);
	}
	else
	{
		score(filler, line);
		show_score(filler);
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
}
