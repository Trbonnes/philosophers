/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:13:56 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/12 13:29:31 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


pthread_t		*g_philosophers;
pthread_mutex_t	*g_fork;
pthread_mutex_t	*g_philo_eating;
int				g_death;

void	*ft_philo_thread(void *params)
{
	static t_philo	philosopher_x;
	static t_params *philo_data;
	static int		philo_next;
	static int		which_philo;

	philosopher_x = (t_philo) { 0 };
	philo_data = (t_params *)params;
	which_philo = philo_data->which_philo;
	if (which_philo == philo_data->philo_nb - 1)
		philo_next = 0;
	else
		philo_next = which_philo + 1;
	printf("this is %d thread\n", which_philo);
	printf("philo_next is %d\n", philo_next);
	gettimeofday(&philo_data->tv, &philo_data->tz);
	philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
	while (philosopher_x.is_dead != 1)
	{
		if (pthread_mutex_lock(&g_fork[which_philo]) == 0)
		{
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			//printf("%dms %d has taken a fork\n", philosopher_x.actual_time_ms, which_philo);
			ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
			ft_putendl_fd("ms", 1);
			ft_putnbr_fd(which_philo, 1);
			ft_putendl_fd("has taken a fork", 1);
			if (pthread_mutex_lock(&g_fork[philo_next]) == 0)
			{
				gettimeofday(&philo_data->tv, &philo_data->tz);
				philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
				//printf("%dms %d has taken a fork\n", philosopher_x.actual_time_ms, which_philo);
				ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
				ft_putstr_fd("ms", 1);
				ft_putnbr_fd(which_philo, 1);
				ft_putstr_fd("has taken a fork", 1);
				philosopher_x.is_eating = 1;
			}
		}
		if (philosopher_x.is_eating == 1)
		{
			pthread_mutex_lock(&g_philo_eating[which_philo]);
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			//printf("%dms %d is eating\n", philosopher_x.actual_time_ms, which_philo);
			ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
			ft_putendl_fd("ms", 1);
			ft_putnbr_fd(which_philo, 1);
			ft_putendl_fd("is eating", 1);
			while (philosopher_x.last_eating_ms - philosopher_x.actual_time_ms < philo_data->time_to_eat)
			{
				gettimeofday(&philo_data->tv, &philo_data->tz);
				philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
			}
			pthread_mutex_unlock(&g_fork[which_philo]);
			pthread_mutex_unlock(&g_fork[philo_next]);
			pthread_mutex_unlock(&g_philo_eating[which_philo]);
			philosopher_x.is_eating = 0;
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.last_eating_ms = philo_data->tv.tv_sec * 1000;
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			//printf("%dms %d is sleeping\n", philosopher_x.actual_time_ms, which_philo);
			ft_putnbr_fd(philosopher_x.actual_time_ms, 1);
			ft_putendl_fd("ms", 1);
			ft_putnbr_fd(which_philo, 1);
			ft_putendl_fd("is sleeping", 1);
			while (philosopher_x.actual_time_ms - philosopher_x.last_eating_ms < philo_data->time_to_sleep)
			{
				gettimeofday(&philo_data->tv, &philo_data->tz);
				philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			}
		}
		if (philosopher_x.is_eating == 0)
		{
			pthread_mutex_unlock(&g_fork[which_philo]);
			pthread_mutex_unlock(&g_fork[philo_next]);
			gettimeofday(&philo_data->tv, &philo_data->tz);
			philosopher_x.actual_time_ms = philo_data->tv.tv_sec * 1000;
			//printf("%dms %d is thiking\n", philosopher_x.actual_time_ms, which_philo);
		}
	}
	g_death = 1;
	return NULL;
}

int main(int ac, char **av)
{
	t_params				*params;
	int						i;
	
	if (ac < 5 || ac > 6)
		return(0);
	g_death = 0;
	params = malloc(sizeof(t_params));
	params->philo_nb = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		params->number_of_time = ft_atoi(av[5]);
	else
		params->number_of_time = 0;
	gettimeofday(&params->tv, &params->tz);
	params->begin_time_ms = params->tv.tv_sec * 1000;
	if (!(g_philosophers = malloc(sizeof(pthread_t) * params->philo_nb)))
		return (-1);
	if (!(g_fork = malloc(sizeof(pthread_mutex_t) * params->philo_nb)))
		return (-1);
	if (!(g_philo_eating = malloc(sizeof(pthread_mutex_t) * params->philo_nb)))
		return (-1);
	i = -1;
	while (++i < params->philo_nb)
		pthread_mutex_init(&g_fork[i], NULL);
	i = 0;
	while (i < params->philo_nb)
	{
		params->which_philo = i;
		if (pthread_create(&g_philosophers[i], NULL, ft_philo_thread, params) != 0)
		{
			//printf("error\n");
			return (-1);
		}
		printf("philosopher %d created\n", i);
		usleep(10);
		i++;
	}
	while (g_death != 1)
		;
	return (0);
}