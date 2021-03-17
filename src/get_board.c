/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/17 01:43:57 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Reading the first line to see which player to play (p_).
*/

char			get_player(void)
{
	char *line;
	char *p;
	char c;

	if (get_next_line(0, &line) < 1)
		kill_filler("No more lines\n", NULL);
	if (!(p = ft_strchr(line, 'p')))
		kill_filler("invalid input from vm\n", NULL);
	p += 1;
	c = *p;
	ft_strdel(&line);
	if (c == '1')
		return ('o');
	else if (c == '2')
		return ('x');
	else
		kill_filler("Invalid player\n", NULL);
	return (0);
}

/*
** Saving the token as coordinates into an array of t_crd structs.
*/

t_crd			*get_coordinates(t_token *token)
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
		if (get_next_line(0, &line) <= 0)
			kill_filler("GNL error\n", NULL);
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

t_token			*get_piece(void)
{
	char		*line;
	char		**token_size;
	t_token		*new;

	new = ft_memalloc(sizeof(t_token));
	if (!get_next_line(0, &line))
		kill_filler("no more lines\n", NULL);
	if (!(token_size = ft_strsplit(line, ' ')))
		kill_filler("error reading token\n", NULL);
	new->h = ft_atoi(token_size[1]);
	new->w = ft_atoi(token_size[2]);
	ft_free2d((void**)token_size);
	ft_strdel(&line);
	new->cr = get_coordinates(new);
	return (new);
}

void			get_board_size(t_board *filler)
{
	char **board_size;
	char *line;

	if (get_next_line(0, &line) <= 0)
		kill_filler("GNL error\n", NULL);
	if (!(board_size = ft_strsplit(line, ' ')))
		kill_filler("failed split\n", NULL);
	ft_strdel(&line);
	filler->w = ft_atoi(board_size[2]);
	filler->h = ft_atoi(board_size[1]);
	ft_free2d((void*)board_size);
}

/*
** Reading and saving the board as char**. The first 4 characters
** of every line are skipped.
*/

void			get_board(t_board *filler)
{
	char	*line;
	int		i;

	get_board_size(filler);
	filler->board = ft_memalloc(sizeof(char*) * (filler->h + 1));
	if (!filler->board)
		kill_filler("Failed to allocate memory\n", filler);
	if (get_next_line(0, &line) <= 0)
		kill_filler("GNL error\n", NULL);
	ft_strdel(&line);
	i = -1;
	while (++i < filler->h)
	{
		if (get_next_line(0, &line) <= 0)
			kill_filler("GNL_error 123\n", NULL);
		filler->board[i] = ft_strsub(line, 4, filler->w);
		if (!filler->board[i])
			kill_filler("Failed to allocate for board substring\n", filler);
		free(line);
	}
}
