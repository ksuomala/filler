/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_priority.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:57:26 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/23 20:02:33 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		move_priority(t_board *filler)
{
	t_crd	pos;

	pos.y = 0;
	while (pos.y < filler->h)
	{
		pos.x = 0;
		while (pos.x < filler->w)
		{
			if (filler->board[pos.y][pos.x] == filler->p)
			{
				if (pos.y > filler->h / 2)
					filler->reverse_move = 0;
				else
					filler->reverse_move = 1;
				return (1);
			}
		}
		pos.y++;
	}
	return (0);
}
