/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:11:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/16 05:29:20 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* ************************************************************************** */
void	ft_usleep(size_t sleep_time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

/* ************************************************************************** */
size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
