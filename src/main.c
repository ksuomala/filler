/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/18 01:41:42 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Reading the stdin and saving the board and the next game piece.
** Minesweeper converts the board into numbers for the algorithm.
*/

int		ft_get_data(t_board *filler)
{
	if (!filler->p)
		if (!(filler->p = ft_get_player()))
			ft_printf("playaa");
	if (!ft_get_board(filler))
		exit(0);
	filler->map = ft_minesweeper(*filler);
	filler->piece = ft_get_piece();
	return (1);
}

/*
** Changing the coodinates to a string that will be displayed on the stdout
** as "Y X\n"
*/

char	*ft_parse_coord(t_crd crd)
{
	char *first;
	char *second;

	first = ft_strfjoin(ft_itoa(crd.y), ft_strdup(" "));
	second = ft_itoa(crd.x);
	first = ft_strfjoin(first, second);
	return (first);
}

int		main(void)
{
	t_board			filler;
	t_crd	move;
	char			*out;

	ft_bzero(&filler, sizeof(filler));
	while (1)
	{
		ft_get_data(&filler);
		move = ft_next_move(filler);
		out = ft_parse_coord(move);
		ft_printf("%s\n", out);
		ft_strdel(&out);
	}
	return (0);
}
