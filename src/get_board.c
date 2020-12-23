/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/23 08:41:11 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Reading the first line to see which player to play (p_).
*/

char		ft_get_player(void)
{
	char *line;
	char *p;
	char c;

	if (get_next_line(0, &line) < 1)
		return (0);
	if (!(p = ft_strchr(line, 'p')))
		ft_printf("what");
	p += 1;
	c = *p;
	ft_strdel(&line);
	if (c == '1')
		return ('o');
	else if (c == '2')
		return ('x');
	else
		return (0);
}

/*
** Saving the token as coordinates into an array of t_crd structs.
*/

t_crd		*ft_get_coordinates(t_token *token)
{
	t_crd			arr[100];
	char			*line;
	int				y;
	int				x;

	y = -1;
	x = -1;
	while (++y < token->h)
	{
		x = -1;
		get_next_line(0, &line);
		while (++x < token->w)
		{
			if (line[x] == '*')
			{
				arr[token->len].x = x;
				arr[token->len].y = y;
				token->len++;
			}
		}
		ft_strdel(&line);
	}
	return (ft_memdup((t_crd*)arr, sizeof(t_crd) * token->len));
}

/*
** Getting the token that has to be placed on the board.
*/

t_token		*ft_get_piece(void)
{
	char		*line;
	char		**token_size;
	t_token		*new;

	new = ft_memalloc(sizeof(t_token));
	if (!get_next_line(0, &line))
		ft_printf("no more lines");
	token_size = ft_strsplit(line, ' ');
	new->h = ft_atoi(token_size[1]);
	new->w = ft_atoi(token_size[2]);
	ft_strdel(&line);
	ft_free2d((void*)token_size);
	new->cr = ft_get_coordinates(new);
	return (new);
}

/*
** Reading and saving the board as char**. The first 4 characters
** of every line are skipped.
*/

int			ft_get_board(t_board *filler)
{
	char	**board_size;
	char	*line;
	int		i;

	if (!get_next_line(0, &line))
		ft_printf("line full\n");
	if (!(board_size = ft_strsplit(line, ' ')))
		ft_printf("failed split\n");
	ft_strdel(&line);
	filler->w = ft_atoi(board_size[2]);
	filler->h = ft_atoi(board_size[1]);
	ft_free2d((void*)board_size);
	filler->board = ft_memalloc(sizeof(char*) * (filler->h + 1));
	if (!get_next_line(0, &line))
		return (0);
	ft_strdel(&line);
	i = 0;
	while (i < filler->h)
	{
		if (!get_next_line(0, &line))
			ft_printf("error3");
		filler->board[i] = ft_strsub(line, 4, filler->w);
		free(line);
		i++;
	}
	return (1);
}
