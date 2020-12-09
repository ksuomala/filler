/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/09 03:42:46 by ksuomala         ###   ########.fr       */
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


int     ft_get_data(t_board *filler)
{
    
   // t_board filler;
 //   char    player;
 //   char *line;

 //   ft_dprintf(fd, "testiis");
 //   ft_bzero(&filler, sizeof(t_board));
      if (!filler->p)
        if (!(filler->p = ft_get_player()))
            ft_printf("playaa");
    if (!ft_get_board(filler))
        exit(0);
 //   ft_printf("bored");
//    filler.p = player;
 //   ft_dprintf(fd, "playa is %c", filler.p);
 // HERE is the segfault!
    filler->map = ft_minesweeper(*filler);
    filler->piece = ft_get_piece();
  //  filler_test(fd, *filler);
    return (1);
}

char *ft_parse_coord(t_coordinate crd)
{
    char *first;
    char *second;

    first = ft_strfjoin(ft_itoa(crd.y), ft_strdup(" "));
    second = ft_itoa(crd.x);
    first = ft_strfjoin(first, second);
    return (first);
}

int     main(void)
{
    t_board         filler;
    t_coordinate    move;
    char            *out;

    

    fd = open("debug.txt", O_RDWR);
    ft_bzero(&filler, sizeof(filler));
    while (1)
    {
        ft_get_data(&filler);
        move = ft_next_move(filler);
        out = ft_parse_coord(move);
 //       ft_dprintf(fd, "%s\n", out);
        ft_printf("%s\n", out);
        ft_strdel(&out);
    }
    close(fd);
    return (0);
}