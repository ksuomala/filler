/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:26:38 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 14:14:49 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Finding the distance of the nearest enemy square for every coordinate.
*/

static unsigned char is_opp(t_board f, int y, int x)
{
    char opponent;

    if (y < 0 || x < 0 || x >= f.width || y >= f.columns)
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

static void ft_check_value(t_board f, int y, int x)
{
    ft_printf("board check around %d %d\n", y, x);
    if (y && x && f.map[y - 1][x - 1] < f.map[y][x])
        f.map[y][x] = f.map[y - 1][x - 1] + 1;
    if (y && f.map[y - 1][x] < f.map[y][x])
        f.map[y][x] = f.map[y - 1][x] + 1;
    if (y && x < f.width - 1 && f.map[y - 1][x + 1] < f.map[y][x])
        f.map[y][x] = f.map[y - 1][x + 1] + 1;
    if (x && f.map[y][x - 1] < f.map[y][x])
        f.map[y][x] = f.map[y][x - 1] + 1;
    if (x < f.width - 1 && f.map[y][x + 1] < f.map[y][x])
        f.map[y][x] = f.map[y][x + 1] + 1;
    if (x && y < f.columns - 1 && f.map[y + 1][x - 1] < f.map[y][x])
        f.map[y][x] = f.map[y + 1][x - 1] + 1;
    if (y < f.columns - 1 && f.map[y + 1][x] < f.map[y][x])
        f.map[y][x] = f.map[y + 1][x] + 1;
    if (y < f.columns - 1 && x < f.width - 1 && f.map[y + 1][x + 1] < f.map[y][x])
        f.map[y][x] = f.map[y + 1][x + 1] + 1;
}

static int **ft_save_distance(t_board f)
{
    int y;
    int x;
    int count;

    ft_printf("saave disance");
    count = 0;
    y = -1;
    while (++y < f.columns)
    {
      x = -1;
        while (++x < f.width)
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

int **ft_minesweeper(t_board f)
{
    int y;
    int x;

    y = 0;
    x = 0;
    f.map = ft_memalloc(sizeof(int*) * (f.columns + 1));
    while (f.board[y])
    {
        f.map[y] = ft_memalloc(sizeof(int) * f.width);
        while (f.board[y][x])
        {
            if (is_opp(f, y, x))
            {
                ft_printf("%d | %d is opponent", y, x);
                ft_printf("playa is %c", f.p);
                f.map[y][x] = 0;
            }
            else if (ft_tolower(f.board[y][x]) == f.p)
            {
                ft_printf("%d | %d is me\n", y, x);
                f.map[y][x] = 100;
            }
            else
            {
                ft_printf("%d | %d is %c\n", y, x, ft_tolower(f.board[y][x]));
                f.map[y][x] = 50;
            }
            ft_printf("%d\n", f.map[y][x]);
            x++;
        }
        y++;
        x = 0;
    }
    f.map = ft_save_distance(f);
    return (f.map);
}