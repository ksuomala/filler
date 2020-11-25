/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/25 22:17:39 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// typedef struct  s_grid
// {
//     char    **board;
//     char    **piece;
//     char    player;
//     int     size;
// }               t_board;

// ft_get_map(char **board)
// {
//     t_board
// 
#include "libft/libft.h"

int     main(void)
{
    char *line;
    int fd;

    fd = open("debug.txt", O_RDWR);
    while (get_next_line(0, &line))
    {
        ft_dprintf(fd, "%s\n", line);
    }
    ft_dprintf(1, "8 2");
    return (0);
}