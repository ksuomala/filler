/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:29:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/13 19:08:12 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Finds the right coordinates to start fitting the piece on the board.
** The smallest x coordinate == distance from the left of the board.
** The smallest y coordinate == distance from the top of the board.
** The starting position == x and y times -1.
*/

t_crd			ft_start_crd(t_token *p)
{
	t_crd			start;
	int				i;

	i = 0;
	start.x = p->cr[i].x;
	start.y = p->cr[i].y;
	while (++i < p->len)
	{
		if (start.x > p->cr[i].x)
			start.x = p->cr[i].x;
		if (start.y > p->cr[i].y)
			start.y = p->cr[i].y;
	}
	start.x *= -1;
	start.y *= -1;
	return (start);
}

/*
** Getting the edge values so the piece won't be fitted outside
** of the board.
*/

t_crd			ft_end_crd(t_token *p)
{
	t_crd			end;
	int				i;

	i = 0;
	end.x = p->cr[i].x;
	end.y = p->cr[i].y;
	while (++i < p->len)
	{
		if (end.x < p->cr[i].x)
			end.x = p->cr[i].x;
		if (end.y < p->cr[i].y)
			end.y = p->cr[i].y;
	}
	return (end);
}

/*
** Adding up the map values of all the coordinates.
*/

int				ft_move_value(int **board, t_crd token_pos, t_crd *token_crd, int len)
{
	int		sum;
	int		i;
	int		x;
	int		y;
// x starts from -1 for some reason.
	i = 0;
	sum = 0;
	x = 0;
	y = 0;
	while (i < len)
	{
		x = token_pos.x + token_crd[i].x;
		y = token_pos.y + token_crd[i].y;
		sum += board[y][x];
		if (sum > 20000 || !board[y][x])
			return (20000);
		i++;
	}
	if (sum < 10000)
		return (20000);
	else
		return (sum);
}

/*
** start and end coordinates define the range where the piece
** fits on the board.
*/

t_crd			ft_next_move(t_board filler, t_crd *token_crd)
{
	t_crd	start;
	t_crd	end;
	t_crd	best_move;
	int		value;

	start = ft_start_crd(filler.piece);
	end = ft_end_crd(filler.piece);
	value = 20000;
	ft_bzero(&best_move, sizeof(t_crd));
	while (start.y < filler.h - end.y)
	{
		while (start.x < filler.w - end.x)
		{
			if (value >= ft_move_value(filler.map, start, token_crd, filler.piece->len))
			{
				value = ft_move_value(filler.map, start, token_crd, filler.piece->len);
				best_move = start;
			}
			start.x++;
		}
		start.x -= (filler.w - end.x);
		start.y++;
	}
	return (best_move);
}
