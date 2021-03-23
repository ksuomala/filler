/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_filler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:27:18 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/23 15:33:37 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	Same as kill_filler, but returns a pointer.
*/

void	free_token_resources(char **split, t_token *token)
{
	ft_free2d((void**)split);
	ft_memdel((void**)&token);
}

void	*kill_filler_ptr(char *error, t_board *filler, char *line)
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
	ft_strdel(&line);
	ft_putstr_fd("ERROR:\n", 2);
	ft_putstr_fd(error, 2);
	return (NULL);
}

/*
** Frees all the allocated pointers and returns 0.
*/

int		kill_filler(char *error, t_board *filler, char *line)
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
	ft_strdel(&line);
	ft_putstr_fd("ERROR:\n", 2);
	ft_putstr_fd(error, 2);
	return (0);
}
