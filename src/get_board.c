/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/21 12:54:08 by ksuomala         ###   ########.fr       */
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
			else if (line[x] != '.')
				kill_filler("Invalid character in piece\n", NULL);
		}
		ft_strdel(&line);
	}
	return (ft_memdup((t_crd*)arr, sizeof(t_crd) * token->len));
}

/*
** Getting the token that has to be placed on the board.
*/

t_token			*get_piece(int max_w, int max_h)
{
	char		*line;
	char		**token_size;
	t_token		*new;

	new = ft_memalloc(sizeof(t_token));
	if (!get_next_line(0, &line))
		kill_filler("no more lines\n", NULL);
	if (!(token_size = ft_strsplit(line, ' ')))
		kill_filler("error reading token\n", NULL);
	if (ft_strcmp("Piece", token_size[0]) || !token_size[1] || !token_size[2] ||
	token_size[3])
		kill_filler("Invalid line before token\n", NULL);
	new->h = ft_atoi(token_size[1]);
	new->w = ft_atoi(token_size[2]);
	if (new->h > max_h || new->w > max_w)
		kill_filler("The piece is larger than the board\n", NULL);
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
		exit(0);
	if (!(board_size = ft_strsplit(line, ' ')))
		kill_filler("failed split\n", NULL);
	ft_strdel(&line);
	if (ft_strcmp("Plateau", board_size[0]) || !ft_isnumeric_str(board_size[1])
	|| !ft_isdigit(board_size[2][0]) || board_size[3])
		kill_filler("Invalid line before board\n", NULL);
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
		if (ft_strlen(line) != (size_t)(filler->w + 4))
			kill_filler("Wrong line length\n", filler);
		filler->board[i] = ft_strsub(line, 4, filler->w);
		if (!filler->board[i])
			kill_filler("Failed to create substring\n", filler);
		if (!ft_str_isvalid(filler->board[i], ".oOxX"))
			kill_filler("Invalid characters in map lines\n", filler);
		free(line);
	}
}
