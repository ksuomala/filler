/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_filler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:27:18 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/23 12:32:25 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	Same as kill_filler, but returns a pointer.
*/

void	*kill_filler_ptr(char *error, t_board *filler)
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
	return (NULL);
}

/*
** Frees all the allocated pointers and returns 0.
*/

int		kill_filler(char *error, t_board *filler)
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
	return (0);
}
