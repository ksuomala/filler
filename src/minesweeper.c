/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 02:02:33 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/17 13:26:39 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** If yx = opponent, return 1.
*/

static unsigned char	is_opp(t_board f, int y, int x)
{
	char opponent;

	if (y < 0 || x < 0 || x >= f.w || y >= f.h)
		return (0);
	if (f.p == 'o')
		opponent = 'x';
	else
		opponent = 'o';
	if (ft_tolower(f.board[y][x]) != opponent)
		return (0);
	else
		return (1);
}

int						value_to_ptr(int *square, int value)
{
	*square = value;
	return (value);
}

/*
** Checking if the values surrounding the coordinate are equal to
** int value
*/

static int				check_value(t_board f, int y, int x, int value)
{
	int change;

	change = 0;
	if (y && x && f.map[y - 1][x - 1] == EMPTY)
		change = value_to_ptr(&f.map[y - 1][x - 1], value + 1);
	if (y && f.map[y - 1][x] == EMPTY)
		change = value_to_ptr(&f.map[y - 1][x], value + 1);
	if (y && x < f.w - 1 && f.map[y - 1][x + 1] == EMPTY)
		change = value_to_ptr(&f.map[y - 1][x + 1], value + 1);
	if (x && f.map[y][x - 1] == EMPTY)
		change = value_to_ptr(&f.map[y][x - 1], value + 1);
	if (x < f.w - 1 && f.map[y][x + 1] == EMPTY)
		change = value_to_ptr(&f.map[y][x + 1], value + 1);
	if (x && y < f.h - 1 && f.map[y + 1][x - 1] == EMPTY)
		change = value_to_ptr(&f.map[y + 1][x - 1], value + 1);
	if (y < f.h - 1 && f.map[y + 1][x] == EMPTY)
		change = value_to_ptr(&f.map[y + 1][x], value + 1);
	if (y < f.h - 1 && x < f.w - 1 && f.map[y + 1][x + 1] == EMPTY)
		change = value_to_ptr(&f.map[y + 1][x + 1], value + 1);
	return (change);
}

static int				**save_distance(t_board f, int value)
{
	int y;
	int x;
	int count;

	count = 0;
	y = -1;
	while (++y < f.h)
	{
		x = -1;
		while (++x < f.w)
		{
			if (f.map[y][x] == value)
			{
				if (check_value(f, y, x, value))
					count++;
			}
		}
	}
	if (count)
		f.map = save_distance(f, value + 1);
	return (f.map);
}

/*
** Saving the locations of both players pieces. Opponent value = 0, own = 10000
** and everything in between gets the value of 5000.
*/

int						**minesweeper(t_board f)
{
	int y;
	int x;

	y = -1;
	x = -1;
	if (!(f.map = ft_memalloc(sizeof(int*) * (f.h + 1))))
		kill_filler("Failed to malloc map\n", &f);
	while (f.board[++y])
	{
		f.map[y] = ft_memalloc(sizeof(int) * f.w);
		if (!f.map[y])
			kill_filler("failed to malloc map row", &f);
		while (f.board[y][++x])
		{
			if (is_opp(f, y, x))
				f.map[y][x] = 0;
			else if (ft_tolower(f.board[y][x]) == f.p)
				f.map[y][x] = 10000;
			else
				f.map[y][x] = EMPTY;
		}
		x = -1;
	}
	f.map = save_distance(f, 0);
	return (f.map);
}
