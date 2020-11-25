/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:26:38 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 01:21:58 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Finding the distance of the nearest enemy square for every coordinate.
*/

static unsigned char ft_opp(char c, char p)
{
    char opponent;

    if (p == '1')
        opponent = 'x';
    else
        opponent = 'o';
    if (ft_tolower(c) != opponent)
        return (0);
    else
        return (1);
}

static char ft_mapvalue(char **str, int y, int x, char p)
{
    unsigned char value;

    if (strchr("oOxX", str[y][x]))
        return (str[y][x]);
    value = 1;
    while (1)
    {
        if (!ft_opp(str[y - 1][x - 1], p))
            break;
        if (!ft_opp(str[y - 1][x], p))
            break;
        if (!ft_opp(str[y - 1][x + 1], p))
            break;
        if (!ft_opp(str[y][x - 1], p))
            break;
        if (!ft_opp(str[y][x + 1], p))
            break;
        if (!ft_opp(str[y + 1][x - 1], p))
            break;
        if (!ft_opp(str[y + 1][x], p))
            break;
        if (!ft_opp(str[y + 1][x + 1], p))
            break;
        value++;
    }
    return (value);
}

char **ft_minesweeper(t_board f)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (f.board[y])
    {
        while (f.board[y][x])
        {
            f.board[y][x] = ft_mapvalue(f.board, y, x, f.p);
            x++;
        }
        y++;
        x = 0;
    }
    return (f.board);
}