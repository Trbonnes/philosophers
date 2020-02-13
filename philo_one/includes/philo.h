/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:14:16 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/13 15:29:26 by trbonnes         ###   ########.fr       */
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

typedef struct		s_params
{
	
	unsigned long	philo_nb;
	unsigned long	which_philo;
	unsigned long	philo_next;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	number_of_time;
	unsigned long	begin_time_ms;
	unsigned long	actual_time_ms;
	unsigned long	last_eating_ms;
}					t_params;


unsigned long		ft_atoi(const char *nptr);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putstr_fd(char *s, int fd);
int					ft_monitor_create(t_params *params, unsigned long philo_nb);
void				*ft_monitor_thread(void *params);
unsigned long		get_curr_time_ms(void);

#endif 