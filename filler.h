#include "libft/libft.h"

typedef struct  s_grid
{
    char    **board;
    char    **piece;
    int     **map;
    char    p;
    int     size;
    int     width;
    int     columns;
}               t_board;

t_board    ft_get_board(void);
int    **ft_minesweeper(t_board f);