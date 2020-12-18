/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 02:02:33 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/18 03:21:23 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Finding the distance of the nearest enemy square for every coordinate.
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

/*
** Checking the values of every square next to the coordinate.
*/

static void				ft_check_value(t_board f, int y, int x)
{
	if (y && x && f.map[y - 1][x - 1] < f.map[y][x])
		f.map[y][x] = f.map[y - 1][x - 1] + 1;
	if (y && f.map[y - 1][x] < f.map[y][x])
		f.map[y][x] = f.map[y - 1][x] + 1;
	if (y && x < f.w - 1 && f.map[y - 1][x + 1] < f.map[y][x])
		f.map[y][x] = f.map[y - 1][x + 1] + 1;
	if (x && f.map[y][x - 1] < f.map[y][x])
		f.map[y][x] = f.map[y][x - 1] + 1;
	if (x < f.w - 1 && f.map[y][x + 1] < f.map[y][x])
		f.map[y][x] = f.map[y][x + 1] + 1;
	if (x && y < f.h - 1 && f.map[y + 1][x - 1] < f.map[y][x])
		f.map[y][x] = f.map[y + 1][x - 1] + 1;
	if (y < f.h - 1 && f.map[y + 1][x] < f.map[y][x])
		f.map[y][x] = f.map[y + 1][x] + 1;
	if (y < f.h - 1 && x < f.w - 1 && f.map[y + 1][x + 1] < f.map[y][x])
		f.map[y][x] = f.map[y + 1][x + 1] + 1;
	if (f.map[y][x] == 50)
		f.map[y][x] += 1;
}

static int				**ft_save_distance(t_board f)
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
			if (f.map[y][x] == 50)
			{
				ft_check_value(f, y, x);
				count++;
			}
		}
	}
	if (count)
		f.map = ft_save_distance(f);
	return (f.map);
}

/*
** Saving the locations of both players pieces. Opponent value = 0, own = 100
** and everything in between gets the value of 50.
*/

int						**ft_minesweeper(t_board f)
{
	int y;
	int x;

	y = 0;
	x = 0;
	if (!(f.map = ft_memalloc(sizeof(int*) * (f.h + 1))))
		exit(0);
	while (f.board[y])
	{
		f.map[y] = ft_memalloc(sizeof(int) * f.w);
		while (f.board[y][x])
		{
			if (is_opp(f, y, x))
				f.map[y][x] = 0;
			else if (ft_tolower(f.board[y][x]) == f.p)
				f.map[y][x] = 10000;
			else
				f.map[y][x] = 50;
			x++;
		}
		y++;
		x = 0;
	}
	f.map = ft_save_distance(f);
	return (f.map);
}
