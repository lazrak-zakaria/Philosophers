/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:34 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/07 17:25:52 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_philo_life(void *ph)
{
	t_philosopher	*philo;

	philo = ph;
	while (1)
	{
		pthread_mutex_lock(philo->fork_1);
		pthread_mutex_lock(philo->m_print);
		printf("%lld %d has taken a fork\n",
			get_time() - philo->time_start, philo->id);
		pthread_mutex_unlock(philo->m_print);
		pthread_mutex_lock(philo->fork_2);
		pthread_mutex_lock(philo->m_print);
		printf("%lld %d has taken a fork\n",
			get_time() - philo->time_start, philo->id);
		pthread_mutex_unlock(philo->m_print);
		ft_eat_sleep_think(philo);
	}
	return (NULL);
}

void	ft_eat_sleep_think(t_philosopher *philo)
{
	long long	time;

	time = get_time();
	pthread_mutex_lock(philo->m_time);
	philo->time_last_eat = time;
	if (philo->eat_flag)
		philo->num_of_eat--;
	pthread_mutex_unlock(philo->m_time);
	pthread_mutex_lock(philo->m_print);
	printf("%lld %d is eating\n",
		time - philo->time_start, philo->id);
	pthread_mutex_unlock(philo->m_print);
	ft_time (philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_1);
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_lock(philo->m_print);
	printf("%lld %d is sleeping\n",
		get_time() - philo->time_start, philo->id);
	pthread_mutex_unlock(philo->m_print);
	ft_time (philo->time_to_sleep);
	pthread_mutex_lock(philo->m_print);
	printf("%lld %d is thinking\n",
		get_time() - philo->time_start, philo->id);
	pthread_mutex_unlock(philo->m_print);
}

int	philosopher(t_super_philo *super_philo)
{
	if (!ft_step_1(super_philo))
		return (1);
	if (!ft_step_2(super_philo))
		return (1);
	return (0);
}

void	ft_time(long long num)
{
	long long	time;

	time = get_time();
	while (get_time() - time < num)
		usleep(500);
}

void	ft_memfree(t_super_philo *s)
{
	free (s->philos_threads);
	free (s->philos);
	free (s->m_forks);
}
