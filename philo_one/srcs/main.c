/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:13:56 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/11 11:57:38 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_philo_thread(void *p_data)
{
	(void)p_data;
	return NULL;
}

int main(int ac, char **av)
{
	pthread_t				*philosophers;
	static pthread_mutex_t	*fork;
	int						philo_nb;
	int						i;
	
	if (ac < 5 || ac > 6)
		return(0);
	philo_nb = ft_atoi(av[1]);
	if (!(philosophers = malloc(sizeof(pthread_t) * philo_nb)))
		return (-1);
	if (!(fork = malloc(sizeof(pthread_t) * philo_nb)))
		return (-1);
	i = -1;
	while (++i > philo_nb)
		pthread_mutex_init(&fork[i], NULL);
	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&philosophers[i], NULL, ft_philo_thread, NULL) != 0)
		{
			return (-1);
		}
		printf("philosopher %d created\n", i);
		i++;
	}
	return (0);
}