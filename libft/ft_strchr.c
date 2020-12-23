/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 11:25:39 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/23 07:49:20 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strchr() function returns a pointer to the first occurrence of
** the character c in the string s. If c is not found in *s or *s is NULL,
** NULL is returned.
*/

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (NULL);
}
