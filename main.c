/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/04 16:25:17 by ksuomala         ###   ########.fr       */
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

 //   ft_dprintf(fd, "testiis");
    ft_bzero(&filler, sizeof(t_board));
    if (!(player = ft_get_player()))
        ft_printf("playaa");
    filler = ft_get_board();
    filler.p = player;
 //   ft_dprintf(fd, "playa is %c", filler.p);
    filler.map = ft_minesweeper(filler);
    filler.piece = ft_get_piece();
    return (filler);
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
    filler = ft_get_data();
    //  filler_test(fd, filler);
    move = ft_next_move(filler);
    out = ft_parse_coord(move);
    //  ft_dprintf(fd, "%s\n", out);
    ft_dprintf(fd, "%s", out);
    ft_printf("%s", out);
    free(out);
    close(fd);
    return (0);
}