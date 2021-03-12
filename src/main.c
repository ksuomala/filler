/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/12 20:37:08 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

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
	if (!(filler->piece = ft_get_piece()))
		ft_printf("Failed to get piece");
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

	//test create leak
	char *str;
	str = ft_memalloc(sizeof(char) * 999);
	str = NULL;
	if (str)
		return(0);
	//test create leak

	ft_bzero(&filler, sizeof(filler));
	while (1)
	{
		ft_get_data(&filler);
		move = ft_next_move(filler);
		out = ft_parse_coord(move);
		ft_cleanup(filler);
		ft_printf("%s\n", out);
		ft_strdel(&out);
	}
	return (0);
}
