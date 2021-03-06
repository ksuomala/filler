/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:01:55 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/14 20:48:33 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Copying the players name from the path of the player executable. The name is
** copied to the beginning of *line using *sub and a duplicate is returned,
** beacause line is freed later on in the reading loop.
*/

char			*get_player_v(char *line)
{
	char	*sub;
	int		i;

	i = 0;
	sub = ft_strrchr(line, '/') + 1;
	if (sub)
	{
		while (sub[i] && sub[i] != '.')
		{
			line[i] = sub[i];
			i++;
		}
	}
	ft_strclr(line + i);
	return (ft_strdup(line));
}

char			**get_board_v(size_t height, size_t width)
{
	int		y;
	char	*line;
	char	**board;

	y = -1;
	if (!(board = ft_memalloc(sizeof(char**) * (height + 1))))
		ft_error("failed to allocate memory for board\n");
	if (!get_next_line(0, &line))
		ft_error("GNL returned 0 \n");
	ft_strdel(&line);
	while (++y < (int)height)
	{
		if (get_next_line(0, &line) <= 0)
			ft_error("GNL returned 0\n");
		if (!(board[y] = ft_strsub(line, 4, width)))
			ft_error("allocation failure\n");
		ft_strdel(&line);
	}
	return (board);
}

t_filler		get_data(void)
{
	t_filler	new;
	char		*line;
	char		**size;

	while (get_next_line(0, &line) > 0 && !ft_strstr(line, "Plateau"))
	{
		if (ft_strstr(line, "exec p1"))
			if (!(new.p1 = get_player_v(line)))
				ft_error("GNL fail\n");
		if (ft_strstr(line, "exec p2"))
			if (!(new.p2 = get_player_v(line)))
				ft_error("GNL fail\n");
		free(line);
	}
	if (!(size = ft_strsplit(line, ' ')))
		ft_error("failed to split line \n");
	new.h = ft_atoi(size[1]);
	new.w = ft_atoi(size[2]);
	ft_free2d((void**)size);
	free(line);
	return (new);
}
