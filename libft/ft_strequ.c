/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 09:38:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/07/01 17:15:07 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (1);
	return (0);
}
