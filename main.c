/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 15:14:54 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "filler.h"


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
 //   ft_printf("playa is %c", filler.p);
    filler.map = ft_minesweeper(filler);
    filler.piece = ft_get_piece();
    int i = 0;
    int ii = 0;
    while (i < filler.columns)
    {
        ft_n(1);
        while(ii < filler.width)
        {
            ft_printf("%4d", filler.map[i][ii]);
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