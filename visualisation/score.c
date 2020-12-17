/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 04:33:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/17 04:35:15 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

SDL_Rect		draw_button(char *image, SDL_Rect location, t_filler *data)
{
	SDL_Surface *img = SDL_LoadBMP(image);
	if (!img)
		ft_printf("Failed to load img Error: %s", SDL_GetError());
	SDL_Texture *bmp_texture = SDL_CreateTextureFromSurface(data->renderer, img);
	SDL_RenderCopy(data->renderer, bmp_texture, NULL, &location);
	SDL_FreeSurface(img);
	SDL_DestroyTexture(bmp_texture);
	return (location);
}

// t_buttons	*ft_buttons(t_filler *data)
// {
// 	t_buttons *rect;

// 	if (!rect = ft_memalloc(sizeof(t_buttons)))
// 		ft_error(1);
// 	rect->pause.h = 30;
// 	rect->pause.w = 30;
// 	rect->pause.x = data->win_size.x * 0.8;
// 	rect->pause.y = data->win_size.y * 0.9;
// 	ft_memcpy(rect->play, rect->pause);
// 	return (rect);
// }

void	ft_score(t_filler *filler, char *line)
{
	char **scoreline;

	scoreline = ft_strsplit(line, ' ');
	filler->score_1 = ft_strdup(scoreline[3]);
	ft_strdel(&line);
	ft_free2d((void**)scoreline);
	get_next_line(0, &line);
	scoreline = ft_strsplit(line, ' ');
	filler->score_2 = ft_strdup(scoreline[3]);
	ft_printf("score %s, score %s\n", filler->score_1, filler->score_2);
}

int		game_over(t_filler *filler)
{
	char	*line;

	line = NULL;
	while (!ft_strstr(line, "Plateau") && !ft_strstr(line, "=="))
	{
		ft_strdel(&line);
		if (!get_next_line(0, &line))
			break;
	}
	if (ft_strstr(line, "Plateau"))
	{
		ft_strdel(&line);
		return (0);
	}
	else
	{
		ft_score(filler, line);
//		show_score(filler);
		ft_strdel(&line);
		return (1);
	}
}


void	show_score(t_filler *data)
{
	char *winner;

	text_to_window(data, (SDL_Color){120, 120, 120}, data->score_1, (int[]){(data->w + 1) * data->square_size, data->h * data->square_size * 0.35});
	text_to_window(data, (SDL_Color){120, 120, 120}, data->score_2, (int[]){(data->w + 1) * data->square_size, data->h * data->square_size * 0.65});
	SDL_RenderPresent(data->renderer);
}
