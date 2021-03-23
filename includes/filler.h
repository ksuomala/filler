/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 03:40:52 by ksuomala          #+#    #+#             */
/*   Updated: 2021/03/23 12:33:04 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <fcntl.h>

# define EMPTY 500

typedef struct	s_crd
{
	int y;
	int x;
}				t_crd;

typedef struct	s_token
{
	t_crd		*cr;
	int			len;
	int			w;
	int			h;
}				t_token;

typedef struct	s_grid
{
	t_token	*piece;
	char	**board;
	int		**map;
	char	p;
	int		size;
	int		w;
	int		h;
}				t_board;

int				get_board(t_board *filler);
t_token			*get_piece(int max_w, int max_h);
char			get_player(void);
int				**minesweeper(t_board f);
t_crd			ft_next_move(t_board f, t_token *token);

int				kill_filler(char *str, t_board *filler);
void	*kill_filler_ptr(char *error, t_board *filler);

#endif
