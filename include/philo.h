/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:57:35 by samatsum          #+#    #+#             */
/*   Updated: 2025/01/16 04:43:52 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:14:34 by samatsum         #+#    #+#             */
/*   Updated: 2025/01/14 18:25:58 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

# define SUCCESS 0
# define INPUT_OK 0
# define FAIL	1
# define PHILO_DEATH 1

# define ALL_OK 0
# define WRONG_INPUT 1
# define MALLOC_ERROR 2
//一般に０が正常終了の値だが、異常終了は１～２５５の間ならなんでもいいらしい。

//  ./philo 4 410 200 200 5
// 4 - 哲学の数
// 410 - 死ぬ時間
// 200 - 食事の時間
// 200 - 就寝時間
// 5 - 終了までの食事の数。

enum e_status
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	IDLE = 4
};

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				nb_meals_ate;
	t_data			*data;
	enum e_status	status;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	size_t			last_eat_time;
}t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				must_eat_meals;
	int				nb_full_p;
	bool			keep_iterating;
	size_t			eat_time;
	size_t			die_time;
	size_t			sleep_time;
	size_t			start_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_keep_iter;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}t_data;

// check_input.c
int			check_input(int argc, char **argv);
// ft_atoi.c
int			ft_atoi(char *str);
// ft_eat.c
int			ft_eat(t_philo *philo);
// init_data.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);
int			init_forks(t_data *data);
// monitor.c
void		*all_full_monitor_routine(void *data_p);
void		*all_alive_monitor_routine(void *data_p);
bool		time_over(t_philo *philo);
// philo_main.c
int			main(int argc, char **argv);
// routine.c
void		*routine(void *philo_p);
// time.c
size_t		get_time(void);
void		ft_usleep(size_t time);
// utils.c
void		free_data(t_data *data);
void		print_msg(t_data *data, int id, char *msg);
bool		get_keep_iterating(t_data *data);
void		set_keep_iterating(t_data *data, bool set_to);
void		set_philo_status(t_philo *philo, enum e_status status);

#endif