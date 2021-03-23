/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/23 20:05:21 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

/*
** Reading the first line to see which player to play (p_).
*/

char	get_player(void)
{
	char *line;
	char *p;
	char c;

	if (get_next_line(0, &line) < 1)
		return (kill_filler("No more lines\n", NULL, NULL));
	if (!(p = ft_strchr(line, 'p')))
		return (kill_filler("invalid input from vm\n", NULL, NULL));
	p += 1;
	c = *p;
	ft_strdel(&line);
	if (c == '1')
		return ('o');
	else if (c == '2')
		return ('x');
	else
		return (kill_filler("Invalid player\n", NULL, NULL));
	return (0);
}

/*
** Reading the stdin and saving the board and the next game piece.
** Minesweeper converts the board into numbers for the algorithm.
*/

int		get_data(t_board *filler)
{
	if (!filler->p)
		filler->p = get_player();
	if (!filler->p)
		return (0);
	if (!get_board(filler))
		return (0);
	if (filler->reverse_move == -1)
		if (!move_priority(filler))
			return (kill_filler("Invalid board\n", filler, NULL));
	if (!(filler->piece = get_piece(filler)))
		return (0);
	if (!(filler->map = minesweeper(*filler)))
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
	filler.reverse_move = -1;
	while (1)
	{
		if (!get_data(&filler))
			return (0);
		move = ft_next_move(filler, filler.piece);
		out = ft_parse_coord(move);
		if (!out)
		{
			kill_filler("Parsing coordinates failed\n", &filler, NULL);
			return (0);
		}
		ft_cleanup(filler);
		ft_printf("%s\n", out);
		ft_strdel(&out);
	}
	return (0);
}
