/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:16:22 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/19 17:08:28 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_curr_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void			params_init_mutex(t_params *params, pthread_mutex_t *fork,
pthread_mutex_t *fd, pthread_mutex_t *philo_eating)
{
	unsigned long	philo_nb;
	unsigned		i;

	i = 0;
	philo_nb = params[i].philo_nb;
	while (i < philo_nb)
	{
		params[i].fork = fork;
		params[i].fd = fd;
		params[i].philo_eating = philo_eating;
		i++;
	}
}

void			params_init_values(t_params *params,
int ac, char **av, int *death)
{
	unsigned long	philo_nb;
	unsigned		i;
	unsigned long	time;

	i = -1;
	philo_nb = ft_atoi(av[1]);
	time = get_curr_time_ms();
	while (++i < philo_nb)
	{
		params[i].philo_nb = philo_nb;
		params[i].which_philo = i;
		if (params[i].which_philo == philo_nb - 1)
			params[i].philo_next = 0;
		else
			params[i].philo_next = params[i].which_philo + 1;
		params[i].time_to_die = ft_atoi(av[2]);
		params[i].time_to_eat = ft_atoi(av[3]);
		params[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			params[i].number_of_time = ft_atoi(av[5]);
		else
			params[i].number_of_time = 0;
		params[i].begin_time_ms = time;
		params[i].death = death;
	}
}

int				launch_free_return(unsigned long philo_nb,
pthread_t *philosophers, t_mutex mutexes, t_params *params)
{
	if (thread_launch(philo_nb, philosophers, params) == -1)
		return (-1);
	free(params);
	free(philosophers);
	free(mutexes.fork);
	free(mutexes.philo_eating);
	free(mutexes.fd);
	return (0);
}

int				main(int ac, char **av)
{
	int						death[1];
	pthread_t				*philosophers;
	t_mutex					mutexes;
	t_params				*params;
	unsigned long			philo_nb;

	if (ac < 5 || ac > 6)
		return (-1);
	*death = 0;
	philo_nb = ft_atoi(av[1]);
	if (!(params = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	if (!(philosophers = malloc(sizeof(pthread_t) * philo_nb)))
		return (-1);
	if (!(mutexes.fork = malloc(sizeof(pthread_mutex_t) * philo_nb)))
		return (-1);
	if (!(mutexes.philo_eating = malloc(sizeof(pthread_mutex_t) * philo_nb)))
		return (-1);
	if (!(mutexes.fd = malloc(sizeof(pthread_mutex_t) * 1)))
		return (-1);
	mutex_init(philo_nb, mutexes);
	params_init_values(params, ac, av, death);
	params_init_mutex(params, mutexes.fork, mutexes.fd, mutexes.philo_eating);
	return (launch_free_return(philo_nb, philosophers, mutexes, params));
}
