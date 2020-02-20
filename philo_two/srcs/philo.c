/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:16:22 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/20 11:22:18 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char		*philo_sem_name(unsigned i)
{
	char	*name;

	name = ft_strjoin("philosopher_", ft_itoa(i));
	return (name);
}

int			launch_free_return(t_semaph semaphores,
pthread_t *philosophers, t_params *params, sem_t **philo_eating)
{
	unsigned	i;

	if (thread_launch(params[0].philo_nb, philosophers, params) == -1)
		return (-1);
	sem_post(semaphores.output);
	sem_close(semaphores.fork);
	sem_close(semaphores.output);
	i = 0;
	while (i < params[0].philo_nb)
	{
		sem_close(params[i].philo_eating);
		i++;
	}
	free(params);
	free(philosophers);
	free(philo_eating);
	return (0);
}

int			params_init_sem(t_params *params,  pthread_t *philosophers, t_semaph semaphores)
{
	sem_t			**philo_eating;
	unsigned long	philo_nb;
	unsigned		i;
	char *			name;

	i = 0;
	philo_nb = params[i].philo_nb;
	if (!(philo_eating = malloc(sizeof(sem_t *) * philo_nb)))
		return (-1);
	while (i < philo_nb)
	{
		name = philo_sem_name(i);
		philo_eating[i] = sem_open(name, O_CREAT, O_RDWR, 1);
		free(name);
		params[i].fork = semaphores.fork;
		params[i].output = semaphores.output;
		params[i].philo_eating = philo_eating[i];
		i++;
	}
	return (launch_free_return(semaphores, philosophers, params, philo_eating));
}

void		params_init_values(t_params *params,
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

int			main(int ac, char **av)
{
	pthread_t				*philosophers;
	t_params				*params;
	t_semaph				semaphores;
	int						death[1];
	unsigned long			philo_nb;

	if (ac < 5 || ac > 6)
		return (0);
	*death = 0;
	philo_nb = ft_atoi(av[1]);
	if (!(params = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	if (!(philosophers = malloc(sizeof(pthread_t) * philo_nb)))
		return (-1);
	semaphores.fork = sem_open("fork", O_CREAT, O_RDWR, philo_nb);
	semaphores.output = sem_open("output", O_CREAT, O_RDWR, 1);
	params_init_values(params, ac, av, death);
	return (params_init_sem(params, philosophers, semaphores));
}
