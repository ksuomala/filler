/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 04:33:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/16 04:53:36 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	show_score(t_filler *data)
{
	char *winner;

	winner = "abc";

	text_to_window(data->renderer, (SDL_Color){120, 120, 120}, data->score_1, (int[]){400, 400});
	text_to_window(data->renderer, (SDL_Color){120, 120, 120}, data->score_2, (int[]){500, 500});
	game_to_window(*data);
}
