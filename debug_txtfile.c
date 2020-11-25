/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:49:30 by ksuomala          #+#    #+#             */
/*   Updated: 2020/11/25 19:47:26 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    to_debug_file(char *str)
{
    int fd = open("debug.txt");
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
    close(fd);
}