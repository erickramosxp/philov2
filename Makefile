NAME = philo
SRCS = utils.c check_args.c get_info_philos.c routine.c monitor.c action_with_fork.c start_diner.c utils_philos.c
FLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=thread

NAME: all
# $(SANITIZE)
all:
	cc -g $(FLAGS) $(addprefix src/, $(SRCS)) main.c -o philo -pthread # $(SANITIZE)
clean:
		rm philo

fclean:

re: clean NAME
