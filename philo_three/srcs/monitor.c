/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:40:56 by trbonnes          #+#    #+#             */
/*   Updated: 2020/07/06 18:30:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_curr_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void			wait_children(t_params *params)
{
	int			status;
	unsigned	i;

	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status))
		{
			i = -1;
			while (++i < params[0].philo_nb)
				kill(params[i].pid, SIGINT);
			exit(WEXITSTATUS(status));
		}
	}
}

int				ft_philo_death(t_params *philo_data)
{
	sem_post(philo_data->fork);
	sem_post(philo_data->fork);
	sem_wait(philo_data->output);
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" died", 1);
	exit(1);
	return (1);
}

void			*ft_monitor_thread(void *params)
{
	t_params		*philo_data;
	unsigned long	time;

	philo_data = (t_params *)params;
	while (philo_data->death[0] != 1
	&& philo_data->actual_number_of_time != philo_data->number_of_time)
	{
		sem_wait(philo_data->philo_eating);
		time = get_curr_time_ms() - philo_data->begin_time_ms;
		if (time - philo_data->last_eating_ms > philo_data->time_to_die)
			philo_data->death[0] = ft_philo_death(philo_data);
		if (philo_data->death[0] != 1)
			sem_post(philo_data->philo_eating);
		usleep(8 * 1000);
	}
	exit(0);
	return (NULL);
}

int				thread_launch(unsigned long philo_nb,
pthread_t *philosophers, t_params *params)
{
	unsigned	i;
	pthread_t	*monitor;

	if (!(monitor = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	i = 0;
	while (i < philo_nb)
	{
		if (!(params[i].pid = fork()))
		{
			if (pthread_create(&philosophers[i], NULL,
			ft_philo_thread, &params[i]) != 0)
				return (-1);
			if (pthread_create(&monitor[i], NULL,
			ft_monitor_thread, &params[i]) != 0)
				return (-1);
			while (1)
				;
		}
		usleep(2 * 1000);
		i++;
	}
	wait_children(params);
	free(monitor);
	return (0);
}
