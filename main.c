/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 13:57:15 by ksuomala         ###   ########.fr       */
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
    if (c == '1')
        return ('o');
    else if (c == '2')
        return ('x');
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
    char    player;
 //   char *line;

    ft_bzero(&filler, sizeof(t_board));
    if (!(player = ft_get_player()))
        ft_printf("playaa");
    filler = ft_get_board();
    filler.p = player;
    ft_printf("playa is %c", filler.p);
    // ft_get_piece()
    filler.map = ft_minesweeper(filler);
    int i = 0;
    int ii = 0;
    while (i < filler.columns)
    {
        ft_n(1);
        while(ii < filler.width)
        {
            ft_putnbr(filler.map[i][ii]);
            ii++;
        }
        ii = 0;
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