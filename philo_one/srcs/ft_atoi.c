/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:30:04 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/13 11:42:24 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long	ft_atoi(const char *nptr)
{
	unsigned long			res;

	res = 0;
	if (*nptr < '0' || *nptr > '9')
		return (0);
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' ||
	*nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *nptr != '\0')
	{
		res = (res * 10) + (*nptr - 48);
		nptr++;
	}
	return (res);
}
