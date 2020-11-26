/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 12:49:18 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_board ft_get_board(void)
{
    t_board filler;
    char    **board_size;
    char    *line;
    int     i;

    get_next_line(0, &line);
    board_size = ft_strsplit(line, ' ');
    free(line);
    filler.width = ft_atoi(board_size[2]);
    filler.columns = ft_atoi(board_size[1]);
    ft_free2d((void*)board_size);
    filler.board = ft_memalloc(sizeof(char*) * (filler.columns + 1));
    if (!get_next_line(0, &line))
        ft_printf("error2");
    i = 0;
    while (i < filler.columns)
    {
        if (!get_next_line(0, &line))
            ft_printf("error3");
        filler.board[i] = ft_strsub(line, 4, filler.width);
        free(line);
        i++;
    }
    return (filler);
}