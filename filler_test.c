#include "filler.h"

void    filler_test(int fd, t_board filler)
{
    int i;
    int ii;

    i = 0;
    ii = 0;
    while (i < filler.height)
    {
        ft_n(1);
        while(ii < filler.width)
        {
            ft_dprintf(fd, "%4d", filler.map[i][ii]);
            ii++;
        }
        ii = 0;
        i++;
    }
    i = -1;
    while (++i < filler.piece->len)
    {
        ft_printf("coordinate %d x|%d| y|%d|\n", i, filler.piece->cr[i].x, filler.piece->cr[i].y);
    }
}