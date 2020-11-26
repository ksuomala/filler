/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 15:12:52 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Reading the first line to see which player to play (p_).
*/

char ft_get_player(void)
{
    char *line;
    char *p;
    char c;
    
    get_next_line(0, &line);
    p = ft_strchr(line, 'p') + 1;
    c = *p;
    free(line);
    if (c == '1')
        return ('o');
    else if (c == '2')
        return ('x');
    else
        return (0);
}

t_token *ft_get_piece(void)
{
    char *line;
    t_token *new;

    new = ft_memalloc(sizeof(t_token));
    if (!get_next_line(0, &line))
        ft_printf("no more lines");
    ft_printf("%s", line);
    return (new);
}

/*
** Reading and saving the board as char**. The first 4 characters
** of every line are skipped.
*/

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