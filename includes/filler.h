#include "libft.h"

#define WIN_WT 1280
#define WIN_HT 720

typedef struct s_crd
{
	int y;
	int x;
}			t_crd;

typedef struct	s_token
{
	t_crd	*cr;
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
