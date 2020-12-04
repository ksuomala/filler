#include "filler.h"

void    filler_test(int fd, t_board filler)
{
    int i;
    int ii;

    i = 0;
    ii = 0;
 //   ft_dprintf(fd, "\nwhaaaattestiiiis height = %d\n", filler.height);

    while (i < filler.height)
    {
        ft_n(1);
 //       ft_dprintf(fd, "hereeeeee\n");
        while(ii < filler.width)
        {
            ft_printf("%4d", filler.map[i][ii]);
            ii++;
        }
        ii = 0;
        i++;
    }
   i = -1;
    while (++i < filler.piece->len)
    {
        ft_dprintf(fd, "coordinate %d x|%d| y|%d|\n", i, filler.piece->cr[i].x, filler.piece->cr[i].y);
    }
     }