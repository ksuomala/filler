/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/18 19:30:07 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

void	kill_filler(char *error, t_board *filler)
{
	if (filler)
	{
		ft_free2d((void**)filler->board);
		if (filler->piece)
		{
			ft_memdel((void**)&filler->piece->cr);
			ft_memdel((void**)&filler->piece);
		}
		ft_free2d((void**)filler->map);
	}
	ft_putendl("ERROR:");
	ft_putstr(error);
	exit(0);
}

/*
** Reading the stdin and saving the board and the next game piece.
** Minesweeper converts the board into numbers for the algorithm.
*/

int		get_data(t_board *filler)
{
	if (!filler->p)
		filler->p = get_player();
	get_board(filler);
	if (!(filler->piece = get_piece(filler->w, filler->h))) //before or after minesweeper?
		return (0);
	filler->map = minesweeper(*filler);
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
		if (!get_data(&filler))
			kill_filler("Failed to get data\n", &filler);
		move = ft_next_move(filler, filler.piece);
		out = ft_parse_coord(move);
		if (!out)
			kill_filler("Parsing coordinates failed\n", &filler);
		ft_cleanup(filler);
		ft_printf("%s\n", out);
		ft_strdel(&out);
	}
	return (0);
}
