/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:43:26 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/20 15:50:12 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//1 thread pour wait 1 pid

int			main(int ac, char **av)
{
	pid_t					*philosophers;
	t_params				*params;
	t_semaph				semaphores;
	int						death[1];
	unsigned long			philo_nb;

	if (ac < 5 || ac > 6)
		return (0);
	*death = 0;
	philo_nb = ft_atoi(av[1]);
	sem_close(semaphores.fork);
	sem_close(semaphores.output);
	sem_unlink("philo_fork");
	sem_unlink("philo_output");
	if (!(params = malloc(sizeof(t_params) * philo_nb)))
		return (-1);
	if (!(philosophers = malloc(sizeof(pid_t) * philo_nb)))
		return (-1);
	semaphores.fork = sem_open("philo_fork", O_CREAT, 0666, philo_nb);
	semaphores.output = sem_open("philo_output", O_CREAT, 0666, 1);
	params_init_values(params, ac, av, death);
	return (params_init_sem(params, philosophers, semaphores));
}
