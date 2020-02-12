/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:14:16 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/12 10:58:58 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

typedef struct	s_philo
{
	int	actual_time_ms;
	int	last_eating_ms;
	int	is_thinking;
	int	is_eating;
	int	is_sleeping;
	int	is_dead;
}				t_philo;


typedef struct	s_params
{
	
	int				philo_nb;
	int				which_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time;
	int				begin_time_ms;
	struct timeval	tv;
	struct timezone	tz;
}				t_params;


int	ft_atoi(const char *nptr);

#endif 