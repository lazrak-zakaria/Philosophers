/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:10 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/07 14:45:55 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	process_args(t_super_philo *super_philo, char **av)
{
	super_philo->eat_flag = 0;
	super_philo->num_of_eat = 0;
	super_philo->num_of_philo = ft_atoi(av[1]);
	super_philo->time_to_die = ft_atoi(av[2]);
	super_philo->time_to_eat = ft_atoi(av[3]);
	super_philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		super_philo->eat_flag = 1;
		super_philo->num_of_eat = ft_atoi(av[5]);
	}
	if (super_philo->num_of_philo < 0 || super_philo->time_to_die < 0
		|| super_philo->time_to_eat < 0 || super_philo->time_to_sleep < 0
		|| super_philo->num_of_eat < 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_super_philo	super_philo;
	int				e;

	if (ac < 5 || ac > 6)
	{
		write(2, "the number of args must be 5 or 6\n", 34);
		return (1);
	}
	if (!process_args(&super_philo, av))
	{
		write(2, "args are not valid\n", 19);
		return (1);
	}
	if (!super_philo.num_of_philo
		|| (super_philo.eat_flag && super_philo.num_of_eat == 0))
		return (0);
	super_philo.m_forks = NULL;
	super_philo.philos = NULL;
	super_philo.philos_threads = NULL;
	e = philosopher(&super_philo);
	ft_memfree(&super_philo);
	return (e);
}

int	ft_step_1(t_super_philo *super_philo)
{
	if (pthread_mutex_init(&super_philo->m_print, NULL)
		|| pthread_mutex_init(&super_philo->m_finish, NULL)
		|| pthread_mutex_init(&super_philo->m_time, NULL))
		return (0);
	super_philo->time_start = get_time();
	super_philo->philos_threads = malloc(sizeof(pthread_t)
			* super_philo->num_of_philo);
	super_philo->philos = malloc(sizeof(t_philosopher)
			* super_philo->num_of_philo);
	super_philo->m_forks = malloc(sizeof(pthread_mutex_t)
			* super_philo->num_of_philo);
	if (!super_philo->philos_threads || !super_philo->philos
		|| !super_philo->m_forks)
		return (0);
	if (ft_sub_step1(super_philo, super_philo->m_forks, -1))
		return (0);
	return (1);
}

int	ft_sub_step1(t_super_philo *super_philo, pthread_mutex_t *forks, int i)
{
	while (++i < super_philo->num_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (1);
	}
	i = -1;
	while (++i < super_philo->num_of_philo)
	{
		super_philo->philos[i].id = i + 1;
		super_philo->philos[i].time_to_eat = super_philo->time_to_eat;
		super_philo->philos[i].time_to_sleep = super_philo->time_to_sleep;
		super_philo->philos[i].num_of_eat = super_philo->num_of_eat;
		super_philo->philos[i].eat_flag = super_philo->eat_flag;
		super_philo->philos[i].fork_1 = &forks[i];
		super_philo->philos[i].fork_2
			= &forks[((i + 1) != super_philo->num_of_philo) * (i + 1)];
		super_philo->philos[i].m_print = &super_philo->m_print;
		super_philo->philos[i].time_start = super_philo->time_start;
		super_philo->philos[i].time_last_eat = super_philo->time_start;
		super_philo->philos[i].m_time = &super_philo->m_time;
	}
	return (0);
}

int	ft_step_2(t_super_philo *super_philo)
{
	int			i;
	pthread_t	super;

	if (pthread_create(&super, NULL, ft_super_life, super_philo))
		return (0);
	pthread_detach(super);
	i = -1;
	while (++i < super_philo->num_of_philo)
	{
		if (pthread_create(&super_philo->philos_threads[i],
				NULL, ft_philo_life, &super_philo->philos[i]))
			return (0);
		usleep(100);
	}
	i = -1;
	while (++i < super_philo->num_of_philo)
		pthread_detach(super_philo->philos_threads[i]);
	pthread_mutex_lock(&super_philo->m_finish);
	return (1);
}
