#include "libft/libft.h"

typedef struct s_coordinate
{
    int y;
    int x;
}              t_coordinate;

int fd;


typedef struct  s_token
{
    t_coordinate    *cr;
    int             len;
    int             w;
    int             h;
}               t_token;

typedef struct  s_grid
{
    t_token *piece;
    char    **board;
    int     **map;
    char    p;
    int     size;
    int     width;
    int     height;
}               t_board;

int              ft_get_board(t_board *filler);
t_token         *ft_get_piece(void);
char            ft_get_player(void);
int             **ft_minesweeper(t_board f);

void            filler_test(int fd, t_board filler);
t_coordinate    ft_next_move(t_board f);