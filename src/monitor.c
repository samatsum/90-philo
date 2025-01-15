/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:47:58 by jergashe          #+#    #+#             */
/*   Updated: 2025/01/16 05:33:21 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*all_full_monitor_routine(void *data_p);
static bool	check_all_philos_full(t_data *data);
void		*all_alive_monitor_routine(void *data_p);
bool		time_over(t_philo *philo);
static bool	is_philo_full(t_data *data, t_philo *philo);
static void	notify_all_philos(t_data *data);

// The reason for not using ft_usleep() is that the philosopher enters 
// the next loop while ft_usleep() is +500.
/* ************************************************************************** */
// usleep(1000) for ALL philosophers sleeping
void	*all_full_monitor_routine(void *data_p)
{
	t_data	*data;

	data = (t_data *)data_p;
	while (get_keep_iterating(data))
	{
		usleep(1000);
		if (check_all_philos_full(data) == SUCCESS)
			break ;
	}
	if (get_keep_iterating(data))
	{
		set_keep_iterating(data, false);
		notify_all_philos(data);
	}
	return (NULL);
}

/* ************************************************************************** */
static bool	check_all_philos_full(t_data *data)
{
	int	index;
	int	full_flag;

	index = -1;
	full_flag = 1;
	while (++index < data->nb_philos && get_keep_iterating(data))
	{
		full_flag *= is_philo_full(data, &data->philos[index]);
		if (full_flag == 0)
			return (FAIL);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
void	*all_alive_monitor_routine(void *data_p)
{
	int		index;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)data_p;
	philos = data->philos;
	index = -1;
	while (++index < data->nb_philos && get_keep_iterating(data))
	{
		if (time_over(&philos[index]) && get_keep_iterating(data))
		{
			print_msg(data, philos[index].id, "died");
			set_keep_iterating(data, false);
			notify_all_philos(data);
			break ;
		}
		if (index == data->nb_philos - 1)
			index = -1;
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
bool	time_over(t_philo *philo)
{
	bool		result;
	t_data		*data;

	data = philo->data;
	result = false;
	if ((get_time() - philo->last_eat_time) > data->die_time)
	{
		set_philo_status(philo, DEAD);
		result = true;
	}
	return (result);
}

/* ************************************************************************** */
static bool	is_philo_full(t_data *data, t_philo *philo)
{
	bool	result;

	result = false;
	if (philo->nb_meals_ate >= data->must_eat_meals)
		result = true;
	return (result);
}

/* ************************************************************************** */
static void	notify_all_philos(t_data *data)
{
	t_philo	*philos;
	int		index;

	philos = data->philos;
	index = -1;
	while (++index < data->nb_philos)
		set_philo_status(&philos[index], DEAD);
}
