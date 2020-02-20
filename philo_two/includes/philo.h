/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:14:16 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/20 11:17:27 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>

typedef struct		s_semaph
{
	sem_t			*fork;
	sem_t			*output;
}					t_semaph;

typedef struct		s_params
{
	int				*death;
	sem_t			*fork;
	sem_t			*output;
	sem_t			*philo_eating;
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
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
unsigned long		get_curr_time_ms(void);
void				*ft_philo_thread(void *params);
int					thread_launch(unsigned long philo_nb,
pthread_t *philosophers, t_params *params);

#endif 