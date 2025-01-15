/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 09:16:17 by jergashe          #+#    #+#             */
/*   Updated: 2025/01/16 04:39:01 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			init_forks(t_data *data);
int			init_philos(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
static int	malloc_data(t_data *data);

/* ************************************************************************** */
int	init_forks(t_data *data)
{
	int		index;
	t_philo	*philos;

	philos = data->philos;
	index = -1;
	while (++index < data->nb_philos)
		pthread_mutex_init(&data->forks[index], NULL);
	index = 0;
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->nb_philos - 1];
	while (++index < data->nb_philos)
	{
		philos[index].left_f = &data->forks[index];
		philos[index].right_f = &data->forks[index - 1];
	}
	return (SUCCESS);
}

/* ************************************************************************** */
int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		index;

	index = -1;
	philos = data->philos;
	while (++index < data->nb_philos)
	{
		philos[index].data = data;
		philos[index].id = index + 1;
		philos[index].nb_meals_ate = 0;
		philos[index].status = IDLE;
		philos[index].last_eat_time = get_time();
	}
	return (SUCCESS);
}

/* ************************************************************************** */
int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_full_p = 0;
	data->keep_iterating = true;
	data->nb_philos = ft_atoi(argv[1]);
	data->die_time = (size_t)ft_atoi(argv[2]);
	data->eat_time = (size_t)ft_atoi(argv[3]);
	data->sleep_time = (size_t)ft_atoi(argv[4]);
	data->must_eat_meals = -1;
	if (argc == 6)
		data->must_eat_meals = ft_atoi(argv[5]);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_keep_iter, NULL);
	return (malloc_data(data));
}

/* ************************************************************************** */
static int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		return (MALLOC_ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
		return (free(data->philos), MALLOC_ERROR);
	data->philo_ths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (data->philo_ths == NULL)
		return (free(data->philos), free(data->forks), MALLOC_ERROR);
	return (SUCCESS);
}
