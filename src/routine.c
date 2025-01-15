/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:09:44 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/16 05:02:41 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		*routine(void *philo_p);
void		*special_routine(void *philo_p);
static void	routine_while(t_philo	*philo);
static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);

/* ************************************************************************** */
void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	philo->last_eat_time = get_time();
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time - 10);
	routine_while(philo);
	return (NULL);
}

/* ************************************************************************** */
void	*special_routine(void *philo_p)
{
	t_philo	*philo;
	int		odd_count;
	int		wave_index;
	long	start_offset;

	philo = (t_philo *) philo_p;
	philo->last_eat_time = get_time();
	odd_count = (philo->data->nb_philos + 1) / 2;
	wave_index = 0;
	start_offset = 0;
	if ((philo->id % 2) == 1)
	{
		wave_index = (philo->id - 1) / 2;
		start_offset = wave_index * 100;
	}
	else
	{
		wave_index = (philo->id / 2) - 1;
		start_offset = (odd_count * 100) + (wave_index * 100);
	}
	if (start_offset > 0)
		ft_usleep(start_offset);
	routine_while(philo);
	return (NULL);
}

/* ************************************************************************** */
static void	routine_while(t_philo	*philo)
{
	while (philo->status != DEAD)
	{
		if (ft_eat(philo) == PHILO_DEATH)
			break ;
		if (philo->status == DEAD)
		{
		//	printf("HELLO 01 Iam %d\n", philo->id);
			break ;
		}
		if (ft_sleep(philo) == PHILO_DEATH)
			break ;
		if (philo->status == DEAD)
		{
		//	printf("HELLO 02 Iam %d\n", philo->id);
			break ;
		}
		if (ft_think(philo) == PHILO_DEATH)
			break ;
	}
}

/* ************************************************************************** */
static int	ft_think(t_philo *philo)
{
	set_philo_status(philo, THINKING);
	if (philo->status == DEAD)
		return (PHILO_DEATH);
	print_msg(philo->data, philo->id, "is thinking");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	ft_sleep(t_philo *philo)
{
	set_philo_status(philo, SLEEPING);
	if (philo->status == DEAD)
		return (PHILO_DEATH);
	print_msg(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->sleep_time);
	return (SUCCESS);
}
