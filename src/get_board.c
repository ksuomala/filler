/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/23 16:34:14 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"


/*
** Saving the token as coordinates into an array of t_crd structs.
*/

t_crd			*get_coordinates(t_token *token)
{
	t_crd			arr[100];
	char			*line;
	t_crd			pos;

	pos.y = -1;
	pos.x = -1;
	while (++pos.y < token->h)
	{
		pos.x = -1;
		if (get_next_line(0, &line) <= 0)
			return (kill_filler_ptr("GNL error\n", NULL, line));
		while (++pos.x < token->w)
		{
			if (line[pos.x] == '*')
			{
				arr[token->len].x = pos.x;
				arr[token->len].y = pos.y;
				token->len++;
			}
			else if (line[pos.x] != '.')
				return (kill_filler_ptr("Invalid char in input\n", NULL, line));
		}
		if (line[pos.x])
			return (kill_filler_ptr("Token line too long\n", NULL, line));
		ft_strdel(&line);
	}
	return (ft_memdup((t_crd*)arr, sizeof(t_crd) * token->len));
}


int				get_piece_size(t_board *filler, t_token *piece)
{
	char	*line;
	char	**size;

	if (!get_next_line(0, &line))
		return (kill_filler("no more lines\n", filler, NULL));
	if (!(size = ft_strsplit(line, ' ')))
	{
		ft_memdel((void**)&piece);
		return (kill_filler("error reading token\n", filler, line));
	}
	if (ft_strcmp("Piece", size[0]) || !size[1] || !size[2] || size[3])
	{
		ft_free2d((void**)size);
		ft_memdel((void**)&piece);
		return (kill_filler("Invalid line before token\n", filler, line));
	}
	piece->h = ft_atoi(size[1]);
	piece->w = ft_atoi(size[2]);
	ft_free2d((void**)size);
	ft_strdel(&line);
	return (1);
}

/*
** Getting the token that has to be placed on the board.
*/

t_token			*get_piece(t_board *filler)
{
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (kill_filler_ptr("Malloc failed get_piece\n", filler, NULL));
	if (!get_piece_size(filler, new))
		return (NULL);
	if (new->h > filler->h || new->w > filler->w)
	{
		ft_memdel((void**)&new);
		return (kill_filler_ptr("The piece is larger than the board\n", filler, NULL));
	}
	new->cr = get_coordinates(new);
	if (!new->cr)
	{
		ft_memdel((void**)&new);
		return (kill_filler_ptr("", filler, NULL));
	}
	return (new);
}

int				get_board_size(t_board *filler)
{
	char **board_size;
	char *line;

	if (get_next_line(0, &line) <= 0)
		return (0);
	if (!(board_size = ft_strsplit(line, ' ')))
		return (kill_filler("failed split\n", NULL, NULL));
	ft_strdel(&line);
	if (ft_strcmp("Plateau", board_size[0]) || !ft_isnumeric_str(board_size[1])
	|| !ft_isdigit(board_size[2][0]) || board_size[3])
	{
		ft_free2d((void*)board_size);
		return (kill_filler("Invalid line before board\n", NULL, NULL));
	}
	filler->w = ft_atoi(board_size[2]);
	filler->h = ft_atoi(board_size[1]);
	ft_free2d((void*)board_size);
	return (1);
}

/*
** Reading and saving the board as char**. The first 4 characters
** of every line are skipped.
*/

int				get_board(t_board *filler)
{
	char	*line;
	int		i;

	if (!get_board_size(filler))
		return (0);
	filler->board = ft_memalloc(sizeof(char*) * (filler->h + 1));
	if (!filler->board)
		return (kill_filler("Failed to allocate memory\n", filler, NULL));
	if (get_next_line(0, &line) <= 0)
		return (kill_filler("GNL error\n", NULL, NULL));
	ft_strdel(&line);
	i = -1;
	while (++i < filler->h)
	{
		if (get_next_line(0, &line) <= 0) //leak
			return (kill_filler("GNL_error 123\n", NULL, NULL));
		filler->board[i] = ft_strsub(line, 4, filler->w);
		if (!filler->board[i] || ft_strlen(line) != (size_t)(filler->w + 4))
			return (kill_filler("Wrong substring or line length\n", filler, line));
		if (!ft_str_isvalid(filler->board[i], ".oOxX"))
			return (kill_filler("Invalid characters in map lines\n", filler, line));
		free(line);
	}
	return (1);
}
