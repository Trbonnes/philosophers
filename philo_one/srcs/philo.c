/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:16:22 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/13 13:24:30 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_t		*g_philosophers;
pthread_mutex_t	*g_fork;
pthread_mutex_t	g_fd;
pthread_mutex_t	*g_philo_eating;
int				g_death;

unsigned long	get_curr_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

int		ft_philo_death(t_philo *philosopher_x, t_params *philo_data)
{
	if (get_curr_time_ms() - philosopher_x->last_eating_ms >= philo_data->time_to_die)
	{
		pthread_mutex_unlock(&g_fork[philo_data->which_philo]);
		pthread_mutex_unlock(&g_fork[philo_data->philo_next]);
		pthread_mutex_lock(&g_fd);
		philosopher_x->actual_time_ms = get_curr_time_ms();
		ft_putnbr_fd(philosopher_x->actual_time_ms, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(philo_data->which_philo, 1);
		ft_putendl_fd(" died", 1);
		pthread_mutex_unlock(&g_fd);
		return (-1);
	}
	return (0);
}

int		ft_philo_thinking(t_philo *philosopher_x, t_params *philo_data)
{
	pthread_mutex_lock(&g_fd);
	if (ft_philo_death(philosopher_x, philo_data) == -1)
		return (-1);
	philosopher_x->actual_time_ms = get_curr_time_ms();
	ft_putnbr_fd(philosopher_x->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" is thinking", 1);
	pthread_mutex_unlock(&g_fd);
	return (0);
}

int		ft_taking_fork(t_philo *philosopher_x, t_params *philo_data)
{
	pthread_mutex_lock(&g_fork[philo_data->which_philo]);
	if (ft_philo_death(philosopher_x, philo_data) == -1)
		return (-1);
	pthread_mutex_lock(&g_fd);
	if (ft_philo_death(philosopher_x, philo_data) == -1)
		return (-1);
	philosopher_x->actual_time_ms = get_curr_time_ms();
	ft_putnbr_fd(philosopher_x->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" has taken a fork", 1);
	pthread_mutex_unlock(&g_fd);
	pthread_mutex_lock(&g_fork[philo_data->philo_next]);
	if (ft_philo_death(philosopher_x, philo_data) == -1)
		return (-1);
	pthread_mutex_lock(&g_fd);
	if (ft_philo_death(philosopher_x, philo_data) == -1)
		return (-1);
	philosopher_x->actual_time_ms = get_curr_time_ms();
	ft_putnbr_fd(philosopher_x->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" has taken a fork", 1);
	pthread_mutex_unlock(&g_fd);
	return (0);
}

int		ft_eating(t_philo *philosopher_x, t_params *philo_data)
{
	pthread_mutex_lock(&g_philo_eating[philo_data->which_philo]);
	philosopher_x->actual_time_ms = get_curr_time_ms();
	pthread_mutex_lock(&g_fd);
	ft_putnbr_fd(philosopher_x->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" is eating", 1);
	pthread_mutex_unlock(&g_fd);
	while (philosopher_x->last_eating_ms - philosopher_x->actual_time_ms < philo_data->time_to_eat)
		philosopher_x->last_eating_ms = get_curr_time_ms();
	pthread_mutex_unlock(&g_fork[philo_data->which_philo]);
	pthread_mutex_unlock(&g_fork[philo_data->philo_next]);
	pthread_mutex_unlock(&g_philo_eating[philo_data->which_philo]);
	philosopher_x->last_eating_ms = get_curr_time_ms();
	philosopher_x->actual_time_ms = philosopher_x->last_eating_ms;
	return (0);
}

int		ft_sleeping(t_philo *philosopher_x, t_params *philo_data)
{
	pthread_mutex_lock(&g_fd);
	if (ft_philo_death(philosopher_x, philo_data) == -1)
		return (-1);
	ft_putnbr_fd(philosopher_x->actual_time_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo_data->which_philo, 1);
	ft_putendl_fd(" is sleeping", 1);
	pthread_mutex_unlock(&g_fd);
	while (philosopher_x->actual_time_ms - philosopher_x->last_eating_ms < philo_data->time_to_sleep)
	{
		if (ft_philo_death(philosopher_x, philo_data) == -1)
			return (-1);
		philosopher_x->actual_time_ms = get_curr_time_ms();
	}
	return (0);
}

void	*ft_philo_thread(void *params)
{
	t_philo	philosopher_x;
	t_params *philo_data;

	philosopher_x = (t_philo) { 0 };
	philo_data = (t_params *)params;
	philosopher_x.last_eating_ms = get_curr_time_ms();
	while (g_death != 1)
	{
		if (ft_philo_thinking(&philosopher_x, philo_data) == -1)
		{
			g_death = 1;
			break;
		}
		if (ft_taking_fork(&philosopher_x, philo_data) == -1)
		{
			g_death = 1;
			break;
		}
		if (ft_eating(&philosopher_x, philo_data) == -1)
		{
			g_death = 1;
			break;
		}
		if (ft_sleeping(&philosopher_x, philo_data) == -1)
		{
			g_death = 1;
			break;
		}
	}
	return NULL;
}

void	params_init(t_params *params, unsigned long philo_nb, int ac, char **av)
{
	unsigned 		i;
	unsigned long	time;

	i = 0;
	time = get_curr_time_ms();
	while (i < philo_nb)
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
		i++;
	}
}

int main (int ac, char **av)
{
	t_params				*params;
	unsigned				i;
	unsigned long			philo_nb;

	if (ac < 5 || ac > 6)
		return(0);
	g_death = 0;
	philo_nb = ft_atoi(av[1]);
	params = malloc(sizeof(t_params) * philo_nb);
	params_init(params, philo_nb, ac, av);
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
	free(params);
	free(g_philosophers);
	free(g_fork);
	free(g_philo_eating);
	return (0);
}
