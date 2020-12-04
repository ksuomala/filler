/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_txtfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/04 15:34:58 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"

int main (void)
{
    char *line;
    int     fd;

    fd = open("debug.txt", O_RDWR);
    while (get_next_line(0, &line))
        ft_dprintf(fd, "%s\n", line);
    return (0);
}