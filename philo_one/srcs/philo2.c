/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:57:37 by trbonnes          #+#    #+#             */
/*   Updated: 2020/07/06 16:16:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_philo_thinking(t_params *philo_data)
{
	pthread_mutex_lock(philo_data->fd);
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" is thinking", 1);
	pthread_mutex_unlock(philo_data->fd);
	return (0);
}

int		ft_takinfork(t_params *philo_data)
{
	pthread_mutex_lock(&(philo_data->fork[philo_data->which_philo]));
	pthread_mutex_lock(philo_data->fd);
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" has taken a fork", 1);
	pthread_mutex_unlock(philo_data->fd);
	pthread_mutex_lock(&(philo_data->fork[philo_data->philo_next]));
	pthread_mutex_lock(philo_data->fd);
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" has taken a fork", 1);
	pthread_mutex_unlock(philo_data->fd);
	return (0);
}

int		ft_eating(t_params *philo_data)
{
	pthread_mutex_lock(&(philo_data->philo_eating[philo_data->which_philo]));
	pthread_mutex_lock(philo_data->fd);
	philo_data->last_eating_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	philo_data->actual_time_ms = philo_data->last_eating_ms;
	philo_data->actual_number_of_time += 1;
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" is eating", 1);
	pthread_mutex_unlock(philo_data->fd);
	usleep(philo_data->time_to_eat * 1000);
	pthread_mutex_unlock(&(philo_data->fork[philo_data->which_philo]));
	pthread_mutex_unlock(&(philo_data->fork[philo_data->philo_next]));
	pthread_mutex_unlock(&(philo_data->philo_eating[philo_data->which_philo]));
	return (0);
}

int		ft_sleeping(t_params *philo_data)
{
	philo_data->actual_time_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	pthread_mutex_lock(philo_data->fd);
	ft_putnbr_fd(philo_data->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" is sleeping", 1);
	pthread_mutex_unlock(philo_data->fd);
	usleep(philo_data->time_to_sleep * 1000);
	return (0);
}

void	*ft_philo_thread(void *params)
{
	t_params *philo_data;

	philo_data = (t_params *)params;
	philo_data->last_eating_ms = get_curr_time_ms() - philo_data->begin_time_ms;
	while (philo_data->death[0] != 1 && philo_data->actual_number_of_time != philo_data->number_of_time)
	{
		ft_philo_thinking(philo_data);
		ft_takinfork(philo_data);
		ft_eating(philo_data);
		ft_sleeping(philo_data);
	}
	return (NULL);
}
