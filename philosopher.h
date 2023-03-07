/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:19 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/07 15:57:08 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				eat_flag;
	long long		time_last_eat;
	long long		time_start;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	*m_time;
}	t_philosopher;

typedef struct s_threads_state
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				eat_flag;
	long long		time_start;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_finish;
	pthread_mutex_t	m_time;
	pthread_mutex_t	*m_forks;
	t_philosopher	*philos;
	pthread_t		*philos_threads;
}	t_super_philo;

int			ft_atoi(char *s);
long long	get_time(void);
void		ft_time(long long num);

int			philosopher(t_super_philo *super_philo);
int			ft_step_1(t_super_philo *super_philo);
int			ft_step_2(t_super_philo *super_philo);
void		*ft_philo_life(void *ph);
void		ft_eat_sleep_think(t_philosopher *philo);
void		*ft_super_life(void *s_p);
int			ft_sub_step1(t_super_philo *super_philo, pthread_mutex_t *f, int i);
void		ft_s_life(t_super_philo *super_philo, int *c, int i);
void		ft_memfree(t_super_philo *s);
#endif
