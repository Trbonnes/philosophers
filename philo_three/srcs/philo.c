/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:43:26 by trbonnes          #+#    #+#             */
/*   Updated: 2020/07/06 18:08:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char		*philo_sem_name(unsigned i)
{
	char	*tmp;
	char	*name;

	tmp = ft_itoa(i);
	name = ft_strjoin("philosophers_", tmp);
	free(tmp);
	return (name);
}

int			launch_free_return(pthread_t *philosophers,
t_params *params, sem_t **philo_eating)
{
	if (thread_launch(params[0].philo_nb, philosophers, params) == -1)
		return (-1);
	free(params);
	free(philosophers);
	free(philo_eating);
	return (0);
}

int			params_init_sem(t_params *params,
pthread_t *philosophers, t_semaph semaphores)
{
	sem_t			**philo_eating;
	unsigned long	philo_nb;
	unsigned		i;
	char			*name;

	i = 0;
	philo_nb = params[i].philo_nb;
	if (!(philo_eating = malloc(sizeof(sem_t *) * philo_nb)))
		return (-1);
	while (i < philo_nb)
	{
		name = philo_sem_name(i);
		sem_close(philo_eating[i]);
		sem_unlink(name);
		philo_eating[i] = sem_open(name, O_CREAT, 0666, 1);
		free(name);
		params[i].fork = semaphores.fork;
		params[i].output = semaphores.output;
		params[i].philo_eating = philo_eating[i];
		i++;
	}
	return (launch_free_return(philosophers, params, philo_eating));
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
		params[i].number_of_time = -1;
		if (ac == 6)
			params[i].number_of_time = ft_atoi(av[5]);
		params[i].actual_number_of_time = 0;
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

	if ((ac < 5 || ac > 6) || (ac == 6 && ft_atoi(av[5]) <= 0))
		return (-1);
	*death = 0;
	philo_nb = ft_atoi(av[1]);
	sem_close(semaphores.fork);
	sem_close(semaphores.output);
	sem_unlink("philo_fork");
	sem_unlink("philo_output");
	if (!(params = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	if (!(philosophers = malloc(sizeof(pthread_t) * philo_nb)))
		return (-1);
	semaphores.fork = sem_open("philo_fork", O_CREAT, 0666, philo_nb);
	semaphores.output = sem_open("philo_output", O_CREAT, 0666, 1);
	params_init_values(params, ac, av, death);
	return (params_init_sem(params, philosophers, semaphores));
}
