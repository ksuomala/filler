/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 00:55:48 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



// ft_get_map(char **board)
// {
//     t_board
// 
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
    if (c)
        return (c);
    else
        return (0);
}

/*
** Reading the stdin and saving the board and the next game piece.
** Minesweeper changes the board into numbers for the algorithm.
*/

t_board     ft_get_data(void)
{
    
    t_board filler;
 //   char *line;

    ft_bzero(&filler, sizeof(t_board));
    if (!(filler.p = ft_get_player()))
        ft_printf("playaa");
    if (!(filler.board = ft_get_board()))
        ft_printf("board fail xD");
    // ft_get_piece()
    filler.board = ft_minesweeper(filler);
    int i = 0;
    while (filler.board[i])
    {
        ft_putendl(filler.board[i]);
        i++;
    }
    return (filler);
}

int     main(void)
{
    t_board filler;

    // while (1)
    // {
    // here I will loop get data and solve.
    // }
    
    filler = ft_get_data();
    return (0);
}