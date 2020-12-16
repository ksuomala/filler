/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 04:33:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/16 05:28:17 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	show_score(t_filler *data)
{
	char *winner;

	winner = "abc";

	text_to_window(data->renderer, (SDL_Color){120, 120, 120}, data->score_1, (int[]){(data->w + 1)* data->square_size, data->h * data->square_size * 0.35});
	text_to_window(data->renderer, (SDL_Color){120, 120, 120}, data->score_2, (int[]){(data->w + 1)* data->square_size, data->h * data->square_size * 0.65});
	SDL_RenderPresent(data->renderer);
	SDL_Delay(5000);
}
