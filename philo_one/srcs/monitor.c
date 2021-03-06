/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:33:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/07/13 11:00:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_philo_death(t_params *philo_data)
{
	pthread_mutex_unlock(&(philo_data->fork[philo_data->which_philo]));
	pthread_mutex_unlock(&(philo_data->fork[philo_data->philo_next]));
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	pthread_mutex_lock(philo_data->fd);
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
	while (philo_data->death[0] != 1
	&& philo_data->actual_number_of_time != philo_data->number_of_time)
	{
		time = get_curr_time_ms() - philo_data->begin_time_ms;
		pthread_mutex_lock(
		&(philo_data->philo_eating[philo_data->which_philo]));
		if (time - philo_data->last_eating_ms > philo_data->time_to_die)
			philo_data->death[0] = ft_philo_death(philo_data);
		if (philo_data->death[0] != 1)
			pthread_mutex_unlock(
			&(philo_data->philo_eating[philo_data->which_philo]));
		usleep(1000);
	}
	return (NULL);
}

int		mutex_init(unsigned long philo_nb, t_mutex mutexes)
{
	unsigned	i;

	i = 0;
	while (i < philo_nb)
	{
		pthread_mutex_init(&(mutexes.fork[i]), NULL);
		pthread_mutex_init(&(mutexes.philo_eating[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(mutexes.fd[0]), NULL);
	return (0);
}

int		thread_launch(unsigned long philo_nb,
pthread_t *philosophers, t_params *params)
{
	unsigned	i;
	pthread_t	*monitor;

	if (!(monitor = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&philosophers[i], NULL,
		ft_philo_thread, &params[i]) != 0)
			return (-1);
		if (pthread_create(&monitor[i], NULL,
		ft_monitor_thread, &params[i]) != 0)
			return (-1);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < philo_nb && params->death[0] != 1)
		if (params[i].actual_number_of_time == params[i].number_of_time)
			i++;
	free(monitor);
	return (0);
}
