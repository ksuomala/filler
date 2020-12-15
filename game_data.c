/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:01:55 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/12 20:03:22 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

char    **get_board(size_t height, size_t width)
{
    int y;
    char    *line;
    char    **board;

    y = -1;
    if (!(board = ft_memalloc(sizeof(char**) * (height + 1))))
        ft_error(0);
    get_next_line(0, &line);
    ft_strdel(&line);
    while (++y < height)
    {
        get_next_line(0, &line);
        if (!(board[y] = ft_strsub(line, 4, width)))
            ft_error(1);
        ft_strdel(&line);
    }
    return (board);
}

t_filler get_data(SDL_Window *w)
{
    t_filler    new;
    char        *line;
    char        **size;
    
 //   new.win = w;
    while(get_next_line(0, &line))
    {
        if (ft_strstr(line, "exec p1"))
            if (!(new.p1 = ft_strdup(ft_strstr(line, "./") + 2)))
                ft_error(3);
        if (ft_strstr(line, "exec p2"))
            if (!(new.p2 = ft_strdup(ft_strstr(line, "./") + 2)))
                ft_error(4);
        if (ft_strstr(line, "Plateau"))
        {
            if (!(size = ft_strsplit(line, ' ')))
                ft_error(2);
            new.h = ft_atoi(size[1]);
            new.w = ft_atoi(size[2]);
            ft_free2d((void**)size);
            free(line);
            break;
        }
        free(line);
    }
    return (new);
}

char **cpy_board(char **board, size_t n)
{
    int     i;
    char    **cpy;

    cpy = ft_memalloc(sizeof(char**) * n);
    if (!cpy)
        return (NULL);
    i = -1;
    while (++i < n - 1)
        if (!(cpy[i] = ft_strdup(board[i])))
            return (NULL);
    return (cpy);
}