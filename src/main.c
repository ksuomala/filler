/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/14 16:09:56 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

void		kill_all(t_board filler)
{
	ft_free2d((void**)filler.board);
	ft_memdel((void**)&filler.piece->cr);
	ft_memdel((void**)&filler.piece);
	ft_free2d((void**)filler.map);
	exit(0);
}

/*
** Reading the stdin and saving the board and the next game piece.
** Minesweeper converts the board into numbers for the algorithm.
*/

int		ft_get_data(t_board *filler)
{
	if (!filler->p)
		if (!(filler->p = get_player()))
			return (0);
	if (!get_board(filler))
		exit(0);
	filler->map = ft_minesweeper(*filler);
	if (!(filler->piece = get_piece()))
		return (0);
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
	if (!first)
		return (NULL);
	second = ft_itoa(crd.x);
	if (!second)
		return (NULL);
	first = ft_strfjoin(first, second);
	return (first);
}

/*
** ft_cleanup frees all the allocated memory after every move.
*/

void	ft_cleanup(t_board filler)
{
	ft_free2d((void**)filler.board);
	ft_memdel((void**)&filler.piece->cr);
	ft_memdel((void**)&filler.piece);
	ft_free2d((void**)filler.map);
}

int		main(void)
{
	t_board		filler;
	t_crd		move;
	char		*out;

	ft_bzero(&filler, sizeof(filler));
	while (1)
	{
		if (!ft_get_data(&filler))
			kill_all(filler);
		move = ft_next_move(filler, filler.piece->cr);
		out = ft_parse_coord(move);
		if (!out)
			kill_all(filler);
		ft_cleanup(filler);
		ft_printf("%s\n", out);
		ft_strdel(&out);
	}
	return (0);
}
