/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/25 17:15:27 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

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
void    to_debug_file(char *str)
{
    int fd = open("debug.txt");
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
    close(fd);
}

int     main(int argc, char **argv)
{
    char *outPut;
    
    open("debug.txt");
    
    printf("%s", outPut);
    return (0);
}