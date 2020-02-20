/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:02:22 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/20 11:02:33 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char *dest;
	char *ptr;

	dest = (malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (dest == NULL)
		return (NULL);
	ptr = dest;
	while (*s1 != '\0')
	{
		*dest = *s1;
		dest++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*dest = *s2;
		dest++;
		s2++;
	}
	*dest = '\0';
	return (ptr);
}
