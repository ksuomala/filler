/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:25:01 by ksuomala          #+#    #+#             */
/*   Updated: 2020/07/01 17:17:51 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
