/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:29:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/17 20:36:04 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Finds the right coordinates to start fitting the piece on the board.
** The smallest x coordinate == distance from the left of the board.
** The smallest y coordinate == distance from the top of the board.
** The starting position == x and y times -1.
*/

t_crd			start_crd(t_token *p)
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
** Getting the highest x and y values so the piece won't be fitted outside
** of the board.
*/

t_crd			end_crd(t_token *p)
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

int				move_value(int **board, t_crd token_pos, t_token *token, int *value)
{
	int		sum;
	int		i;
	int		x;
	int		y;

	i = 0;
	sum = 0;
	x = 0;
	y = 0;
	while (i < token->len)
	{
		x = token_pos.x + token->cr[i].x;
		y = token_pos.y + token->cr[i].y;
		sum += board[y][x];
		if (sum > 20000 || sum > *value || !board[y][x])
			return (0);
		i++;
	}
	if (sum < 10000 || sum > *value)
		return (0);
	else
	{
		*value = sum;
		return (1);
	}
}

/*
** start and end coordinates define the range where the piece
** fits on the board. If the value of the move is <= the value of
** the current best_move, it will be saved as the best move.
*/

t_crd			ft_next_move(t_board f, t_token *token)
{
	t_crd	start;
	t_crd	end;
	t_crd	best_move;
	t_crd	current;
	int		value;

	start = start_crd(f.piece);
	end = end_crd(f.piece);
	value = 20000;
	ft_bzero(&best_move, sizeof(t_crd));
	current = start;
	while (current.y < f.h - end.y)
	{
		while (current.x < (f.w - end.x))
		{
			if (move_value(f.map, current, token, &value))
				best_move = current;
			current.x++;
		}
		current.x = start.x;
		current.y++;
	}
	return (best_move);
}
