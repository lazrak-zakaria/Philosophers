/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:42:25 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/07 14:07:54 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

int	ft_atoi(char *s)
{
	int			i;
	long long	ans;

	i = 0;
	ans = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '-' || s[i] == '+' || !s[i])
	{
		if (s[i] == '-' || !s[i] || !s[i + 1])
			return (-1);
		++i;
	}
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			break ;
		ans = (ans * 10) + (s[i++] - '0');
	}
	if (s[i] || ans > INT_MAX)
		return (-1);
	return (ans);
}

long long	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	*ft_super_life(void *s_p)
{
	t_super_philo	*super_philo;
	int				i;
	int				c;

	super_philo = (t_super_philo *)s_p;
	pthread_mutex_lock(&super_philo->m_finish);
	while (1)
	{
		i = -1;
		c = 0;
		while (++i < super_philo->num_of_philo)
			ft_s_life(super_philo, &c, i);
		if (c == super_philo->num_of_philo)
		{
			pthread_mutex_lock(&super_philo->m_print);
			pthread_mutex_unlock(&super_philo->m_finish);
			return (NULL);
		}
	}
}

void	ft_s_life(t_super_philo *super_philo, int *c, int i)
{
	long long	time;

	time = get_time();
	pthread_mutex_lock(&super_philo->m_time);
	if (time > super_philo->philos[i].time_last_eat
		+ super_philo->time_to_die)
	{
		pthread_mutex_lock(&super_philo->m_print);
		printf("%lld %d died\n",
			time - super_philo->philos[i].time_start,
			super_philo->philos[i].id);
		pthread_mutex_unlock(&super_philo->m_finish);
		pthread_mutex_lock(&super_philo->m_time);
	}
	if (super_philo->eat_flag && super_philo->philos[i].num_of_eat <= 0)
		(*c)++;
	pthread_mutex_unlock(&super_philo->m_time);
	usleep(50);
}
