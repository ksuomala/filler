#include "libft/libft.h"

typedef struct  s_grid
{
    char    **board;
    char    **piece;
    char    p;
    int     size;
}               t_board;

char    **ft_get_board(void);
char    **ft_minesweeper(t_board f);