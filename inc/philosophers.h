/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:54:23 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 21:12:35 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define USAGE "usage: the program should take the following arguments:\n\
	\t1/ number_of_philosophers\n\
	\t2/ ttdie\n\
	\t3/ tteat\n\
	\t4/ ttsleep\n\
	\t5/ number_of_time_each_philosopher_must_eat(optional)\n"

# define R_FORK "has taken a fork"
# define L_FORK "has taken a fork"
# define EAT "is eating"
# define DROP "has drop forks"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_philo
{
	int				id;
	int				meals_nb;
	long			last_meal_start;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	struct s_env	*env;
}				t_philo;

typedef struct s_env
{
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				must_eat;
	int				philo_nb;
	pthread_mutex_t	*ate_census;
	int				ate;
	pthread_mutex_t	*death_census;
	int				death;
	pthread_mutex_t	*print;
	long			init_time;
	pthread_mutex_t	*check_ate;
	pthread_mutex_t	*fork;
	pthread_t		*thrds;
	t_philo			*philo;
}				t_env;

/*parsing*/
int		parse_argv(int argc, char **argv);
int		atoi_parser(char *arg);

/*initialisation*/
int		alloc_env(t_env *env);
int		init_mutex(t_env *env, int i, int ret);
int		fill_env(t_env *env, int argc, char **argv);
void	fill_argv(t_env *env, int argc, char **argv);
void	fill_philos(t_env *env);

/*time management*/
long	pinned_time(void);
long	get_time_since_pinned_time(long start);
void	waiting_act(int time_to);

/*routine*/
void	*routine(void *philo_env);
void	take_forks(t_philo *philo, t_env *env);
void	dining_moment(t_philo *philo, t_env *env);
int		run_threads(t_env *env);
int		ate(t_philo *philo, t_env *env);

/*runtime_watcher*/
int		fatal_issue(t_env *env);
int		empty_meals_stock(t_env *env);
void	runtime_watcher(t_env *env);

/*print*/
void	print_die(t_env *env, int i);
void	print_state(t_philo *philo, t_env *env, char *print);

/*clean_exit*/
int		threads_end(t_env *env);
int		mutex_end(t_env *env, int i, int ret);
void	free_env(t_env *env);
void	*mainthrd(void *philo_env);

/*utils*/
int		is_digit(int c);
int		str_len(char *str);
void	*mem_set(void *b, int c, size_t len);
void	send_error(int error, char *error_message);

#endif