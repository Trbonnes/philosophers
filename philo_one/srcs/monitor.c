/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:33:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/19 16:58:45 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_philo_death(t_params *philo_data)
{
	pthread_mutex_unlock(&(philo_data->fork[philo_data->which_philo]));
	pthread_mutex_unlock(&(philo_data->fork[philo_data->philo_next]));
	pthread_mutex_lock(philo_data->fd);
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" died", 1);
	return (1);
}

void	*ft_monitor_thread(void *params)
{
	t_params		*philo_data;
	unsigned long	time;

	philo_data = (t_params *)params;
	while (philo_data->death[0] != 1)
	{
		pthread_mutex_lock(
		&(philo_data->philo_eating[philo_data->which_philo]));
		time = get_curr_time_ms() - philo_data->begin_time_ms;
		if (time - philo_data->last_eating_ms > philo_data->time_to_die)
			philo_data->death[0] = ft_philo_death(philo_data);
		if (philo_data->death[0] != 1)
			pthread_mutex_unlock(
			&(philo_data->philo_eating[philo_data->which_philo]));
		usleep(8 * 1000);
	}
	return (NULL);
}

int		ft_monitor_create(t_params *params, unsigned long philo_nb)
{
	unsigned long			i;
	pthread_t				*monitor;

	if (!(monitor = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&monitor[i], NULL,
		ft_monitor_thread, &params[i]) != 0)
			return (-1);
		i++;
	}
	while (params->death[0] != 1)
		;
	free(monitor);
	return (0);
}

int		thread_launch(unsigned long philo_nb,
pthread_t *philosophers, t_params *params)
{
	unsigned	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&philosophers[i], NULL,
		ft_philo_thread, &params[i]) != 0)
			return (-1);
		usleep(10);
		i++;
	}
	if (ft_monitor_create(params, philo_nb) == -1)
		return (-1);
	return (0);
}
