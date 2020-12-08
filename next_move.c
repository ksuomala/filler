/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:29:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/08 20:00:15 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Finds the right coordinates to start fitting the piece on the board.
*/

t_coordinate    ft_start_crd(t_token *p)
{
    t_coordinate start;
    int i;

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
    return (start);
}

/*
** Getting the edge values so the piece won't be fitted outside
** of the board.
*/

t_coordinate    ft_end_crd(t_token *p)
{
    t_coordinate end;
    int i;

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

int ft_move_value(int **board, t_coordinate token, t_coordinate *lst, int len)
{
    int     sum;
    int     i;
    int     x;
    int     y;

    i = 0;
    sum = 0;
    x = 0;
    y = 0;
    while (i < len)
    {
        x = token.x + lst[i].x;
        y = token.y + lst[i].y;
        sum += board[y][x];
        if (sum > 200 || !board[y][x])
            return (200);
        i++;
    }
   // ft_printf("sum of y%d x%d = %d", token.y, token.x, sum);
    if (sum < 100)
        return (200);
    else
        return (sum);
}

/*
** start and end coordinates define the range where the piece
** fits on the board.
*/

t_coordinate        ft_next_move(t_board f)
{
    t_coordinate    *crd;
    t_coordinate    start;
    t_coordinate    end;
    t_coordinate    best_move;
    int             value;
    int             x = 0;

    crd = f.piece->cr;
    start = ft_start_crd(f.piece);
    end = ft_end_crd(f.piece);
    value = 200;
    x = start.x;
    while (start.y < f.height - end.y)
    {
        while (start.x < f.width - end.x)
        {
            if (value > ft_move_value(f.map, start, crd, f.piece->len))
            {
                value = ft_move_value(f.map, start, crd, f.piece->len);
                best_move = start;
            }
            start.x++;
        }
        start.x = x;
        start.y++;
    }
    return (best_move);
}