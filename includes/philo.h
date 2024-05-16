/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erramos <erramos@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:51:04 by erramos           #+#    #+#             */
/*   Updated: 2024/05/16 12:52:57 by erramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int					index;
	int					status;
	pthread_t			philo;
	t_mutex				fork;
	t_mutex				meal_check;
	t_mutex				dead_check;
	long int			last_time_eat;
	int					i_eat;
	struct s_philo		*previous;
	struct s_philo		*next;
	t_data				*data;
}						t_philos;

typedef struct s_data
{
	int					nb_philo;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	int					times_must_eat;
	int					flag_can_eat;
	int					philos_dead;
	int					end_dinner;
	int					start_simulation;
	long int			time_start;
	t_mutex				table_mutex;
	t_mutex				print_mutex;
	pthread_t			monitor;
	t_philos			*philo;
	t_philos			*head;
}						t_data;

int						ft_atoi(const char *nptr);
long					ft_atol(const char *nptr);
int						ft_isdigit(int c);

void					init_infos(t_data *infos, char **args, int argc);
void					*philos_routine(void *arg);
long int				get_real_time(void);
int						valid_args(int argc, char **args);
void					free_list(t_philos *philo);

int						new_sleep(long time);
void					*monitor(void *arg);

void					print_status(char *msg, long time_current,
							int index_philo, t_mutex *print_mutex);

void					set_status(int *status, int new_status,
							t_mutex *status_mutex);

int						taken_left_fork(t_philos *philo);
int						taken_right_fork(t_philos *philo);
void					unlock_forks(t_philos *philo);
int						philo_eat_all(t_philos *philo);
void					add_another_meal(t_philos *philo);

int						philo_alive(t_philos *philo);
void					start_routine(t_data *data);

#endif
