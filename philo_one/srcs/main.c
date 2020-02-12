/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:13:56 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/12 17:07:29 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


pthread_t		*g_philosophers;
pthread_mutex_t	*g_fork;
pthread_mutex_t	g_fd;
pthread_mutex_t	*g_philo_eating;
int				g_death;

void	*ft_philo_thread(void *params)
{
	static t_philo	philosopher_x;
	static t_params *philo_data;

	philosopher_x = (t_philo) { 0 };
	philo_data = (t_params *)params;
	gettimeofday(&philo_data->tv, &philo_data->tz);
	philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
	while (philosopher_x.is_dead != 1)
	{
		if (pthread_mutex_lock(&g_fork[philo_data->which_philo]) == 0)
		{
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			while (pthread_mutex_lock(&g_fd) != 0)
				usleep(5);
			ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
			ft_putstr_fd("ms ", 1);
			ft_putnbr_fd(philo_data->which_philo, 1);
			ft_putendl_fd(" has taken a fork ", 1);
			pthread_mutex_unlock(&g_fd);
			if (pthread_mutex_lock(&g_fork[philo_data->philo_next]) == 0)
			{
				gettimeofday(&philo_data->tv, &philo_data->tz);
				philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
				while (pthread_mutex_lock(&g_fd) != 0)
					usleep(5);
				ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
				ft_putstr_fd("ms ", 1);
				ft_putnbr_fd(philo_data->which_philo, 1);
				ft_putendl_fd(" has taken a fork ", 1);
				pthread_mutex_unlock(&g_fd);
				philosopher_x.is_eating = 1;
			}
		}
		if (philosopher_x.is_eating == 1)
		{
			pthread_mutex_lock(&g_philo_eating[philo_data->which_philo]);
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			while (pthread_mutex_lock(&g_fd) != 0)
				usleep(5);
			ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
			ft_putstr_fd("ms ", 1);
			ft_putnbr_fd(philo_data->which_philo, 1);
			ft_putendl_fd(" is eating ", 1);
			pthread_mutex_unlock(&g_fd);
			while (philosopher_x.last_eating_ms - philosopher_x.actual_time_ms < philo_data->time_to_eat)
			{
				gettimeofday(&philo_data->tv, &philo_data->tz);
				philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
			}
			pthread_mutex_unlock(&g_fork[philo_data->which_philo]);
			pthread_mutex_unlock(&g_fork[philo_data->philo_next]);
			pthread_mutex_unlock(&g_philo_eating[philo_data->which_philo]);
			philosopher_x.is_eating = 0;
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			while (pthread_mutex_lock(&g_fd) != 0)
				usleep(5);
			ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
			ft_putstr_fd("ms ", 1);
			ft_putnbr_fd(philo_data->which_philo, 1);
			ft_putendl_fd(" is sleeping ", 1);
			pthread_mutex_unlock(&g_fd);
			while (philosopher_x.actual_time_ms - philosopher_x.last_eating_ms < philo_data->time_to_sleep)
			{
				gettimeofday(&philo_data->tv, &philo_data->tz);
				philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			}
		}
		if (philosopher_x.is_eating == 0)
		{
			pthread_mutex_unlock(&g_fork[philo_data->which_philo]);
			pthread_mutex_unlock(&g_fork[philo_data->philo_next]);
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
		}
	}
	g_death = 1;
	return NULL;
}

void	params_init(t_params **params, int philo_nb, int ac, char **av)
{
	int 			i;
	struct timeval	tv;
	struct timezone	tz;

	i = 0;
	gettimeofday(&tv, &tz);
	while (i < philo_nb)
	{
		params[i]->philo_nb = philo_nb;
		params[i]->which_philo = i;
		if (params[i]->which_philo == philo_nb - 1)
			params[i]->philo_next = 0;
		else
			params[i]->philo_next = params[i]->which_philo + 1;
		params[i]->time_to_die = ft_atoi(av[2]);
		params[i]->time_to_eat = ft_atoi(av[3]);
		params[i]->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			params[i]->number_of_time = ft_atoi(av[5]);
		else
			params[i]->number_of_time = 0;
		params[i]->begin_time_ms = tv.tv_sec * 1000;
		i++;
	}
}

int 	main(int ac, char **av)
{
	t_params				*params;
	int						i;
	int						philo_nb;
	
	if (ac < 5 || ac > 6)
		return(0);
	g_death = 0;
	philo_nb = ft_atoi(av[1]);
	params = malloc(sizeof(t_params) * philo_nb);
	params_init(&params, philo_nb, ac, av);
	if (!(g_philosophers = malloc(sizeof(pthread_t) * philo_nb)))
		return (-1);
	if (!(g_fork = malloc(sizeof(pthread_mutex_t) * philo_nb)))
		return (-1);
	if (!(g_philo_eating = malloc(sizeof(pthread_mutex_t) * philo_nb)))
		return (-1);
	i = -1;
	while (++i < philo_nb)
		pthread_mutex_init(&g_fork[i], NULL);
	pthread_mutex_init(&g_fd, NULL);
	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&g_philosophers[i], NULL, ft_philo_thread, &params[i]) != 0)
			return (-1);
		usleep(10);
		i++;
	}
	while (g_death != 1)
		;
	return (0);
}