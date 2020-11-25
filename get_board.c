/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:09:45 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/26 00:11:52 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char **ft_get_board(void)
{
    char    **grid;
    char    *line;
    int     columns;
    int     width;
    int     i;

    get_next_line(0, &line);
    grid = ft_strsplit(line, ' ');
    free(line);
    width = ft_atoi(grid[2]);
    columns = ft_atoi(grid[1]);
    free(grid);
    grid = ft_memalloc(sizeof(char*) * (columns + 1));
    if (!get_next_line(0, &line))
        return (NULL);
    i = 0;
    while (i < columns)
    {
        if (!get_next_line(0, &line))
            return (NULL);
        grid[i] = ft_strsub(line, 4, width);
        free(line);
        i++;
    }
    return (grid);
}