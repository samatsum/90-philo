/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:51:45 by jergashe          #+#    #+#             */
/*   Updated: 2025/01/16 04:22:55 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			ft_eat(t_philo *philo);
static int	take_forks(t_philo *philo);
static int	take_left_fork(t_philo *philo);
static int	take_right_fork(t_philo *philo);
static int	handle_only1_philo(t_philo *philo);

/* ************************************************************************** */
int	ft_eat(t_philo *philo)
{
	if (take_forks(philo) == PHILO_DEATH)
		return (PHILO_DEATH);
	set_philo_status(philo, EATING);
	print_msg(philo->data, philo->id, "is eating");
	philo->last_eat_time = get_time();
	ft_usleep(philo->data->eat_time);
	philo->nb_meals_ate++;
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_forks(t_philo *philo)
{
	if ((philo->data->nb_philos) == 1)
		return (handle_only1_philo(philo));
	if (take_right_fork(philo) == PHILO_DEATH)
		return (PHILO_DEATH);
	if (take_left_fork(philo) == PHILO_DEATH)
	{
		pthread_mutex_unlock(philo->right_f);
		return (PHILO_DEATH);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_left_fork(t_philo *philo)
{
	if (time_over(philo) || philo->status == DEAD)
		return (PHILO_DEATH);
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, "has taken a fork");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	take_right_fork(t_philo *philo)
{
	if (time_over(philo) || philo->status == DEAD)
		return (PHILO_DEATH);
	pthread_mutex_lock(philo->right_f);
	print_msg(philo->data, philo->id, "has taken a fork");
	return (SUCCESS);
}

/* ************************************************************************** */
static int	handle_only1_philo(t_philo *philo)
{
	print_msg(philo->data, philo->id, "has taken a fork");
	ft_usleep(philo->data->die_time);
	set_philo_status(philo, DEAD);
	return (PHILO_DEATH);
}
