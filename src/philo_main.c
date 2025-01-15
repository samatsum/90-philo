/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 08:19:00 by jergashe          #+#    #+#             */
/*   Updated: 2025/01/16 04:29:32 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int			main(int argc, char **argv);
static int	philosophers(int argc, char **argv);
static int	run_threads(t_data *data);
static int	join_threads(t_data *data);
static void	print_instruction(void);

int	main(int argc, char **argv)
{
	if (check_input(argc, argv) != INPUT_OK)
	{
		print_instruction();
		return (WRONG_INPUT);
	}
	if (philosophers(argc, argv) != ALL_OK)
		return (MALLOC_ERROR);
	return (ALL_OK);
}

/* ************************************************************************** */
static int	philosophers(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != SUCCESS)
		return (MALLOC_ERROR);
	init_philos(&data);
	init_forks(&data);
	run_threads(&data);
	join_threads(&data);
	free_data(&data);
	return (ALL_OK);
}

/* ************************************************************************** */
static int	run_threads(t_data *data)
{
	int	index;

	index = -1;
	data->start_time = get_time();
	while (++index < data->nb_philos)
	{
		if (pthread_create(&data->philo_ths[index], NULL, \
				&routine, &data->philos[index]))
			return (FAIL);
	}
	if (pthread_create(&data->monit_all_alive, NULL, \
			&all_alive_monitor_routine, data))
		return (FAIL);
	if (data->must_eat_meals > 0 && pthread_create(&data->monit_all_full, NULL,
			&all_full_monitor_routine, data))
		return (FAIL);
	return (SUCCESS);
}

/* ************************************************************************** */
static int	join_threads(t_data *data)
{
	int	index;

	index = -1;
	if (pthread_join(data->monit_all_alive, NULL))
		return (FAIL);
	if (data->must_eat_meals > 0 && pthread_join(data->monit_all_full, NULL))
		return (FAIL);
	while (++index < data->nb_philos)
	{
		if (pthread_join(data->philo_ths[index], NULL))
			return (FAIL);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
static void	print_instruction(void)
{
	printf("\t\tWRONG INPUT!\n\n");
	printf("./philo nb_philos time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("number_of_times_each_philosopher_must_eat ");
	printf("(optional argument)\n");
	printf("Example:\n\n");
	printf("./philo 4 800 200 200 5\n\n");
	printf("nb_philos: +1~\n");
	printf("time_to_die: +11~\n");
	printf("time_to_eat: +11~\n");
	printf("time_to_sleep: +11~\n");
	printf("number_of_times_each_philosopher_must_eat: +1~");
	printf("\n");
}
