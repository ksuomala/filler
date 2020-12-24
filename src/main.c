/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/24 04:06:37 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

/*
** Reading the stdin and saving the board and the next game piece.
** Minesweeper converts the board into numbers for the algorithm.
*/

int fd;

// void	ft_debug_grid(int fd, int **grid, int y, int x, int min_width) //test fuction
// {
// 	int i_x;
// 	int i_y;

// 	i_y = 0;
// 	i_x = 0;
// 	while (i_y < y)
// 	{
// 		while (i_x < x)
// 		{
// 			if (grid[i_y][i_x] == 10000)
// 				ft_dprintf(fd, " P1");
// 			else if (!grid[i_y][i_x])
// 				ft_dprintf(fd, " P2");
// 			else
// 				ft_dprintf(fd, "%*d", min_width, grid[i_y][i_x]);
// 			i_x++;
// 		}
// 		i_x = 0;
// 		i_y++;
// 		ft_dprintf(fd, "\n");
// 	}
// 	ft_dprintf(fd, "\n");
// }


int		ft_get_data(t_board *filler)
{
	if (!fd) //test
		fd = open("txt.txt", O_RDWR); //test
	if (!filler->p)
		if (!(filler->p = ft_get_player()))
			ft_printf("playaa");
	if (!ft_get_board(filler))
		exit(0);
	filler->map = ft_minesweeper(*filler);
	if (!(filler->piece = ft_get_piece()))
		ft_printf("Failed to get piece");
//	ft_debug_grid(fd, filler->map, filler->h, filler->w, 3); //test
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

	ft_bzero(&filler, sizeof(filler));
	while (1)
	{
		ft_dprintf(fd, "gettin data\n");
		ft_get_data(&filler);
		ft_dprintf(fd, "got data\n");
		move = ft_next_move(filler);
		ft_dprintf(fd, "made move\n");
		out = ft_parse_coord(move);
		ft_dprintf(fd, "parsed output \n");
		ft_cleanup(filler);
		ft_printf("%s\n", out);
		ft_strdel(&out);
	}
	return (0);
}
