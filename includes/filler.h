/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 03:40:52 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/24 04:46:33 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define EMPTY 500
# define WIN_WT 1280
# define WIN_HT 720

int fd; //test

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

int				ft_get_board(t_board *filler);
t_token			*ft_get_piece(void);
char			ft_get_player(void);
int				**ft_minesweeper(t_board f);
void			filler_test(int fd, t_board filler);
t_crd			ft_next_move(t_board f);

#endif
