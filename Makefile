NAME = philo
SRCS = utils.c check_args.c get_info_philos.c routine.c
FLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=thread

NAME: all

all:
	cc -g $(FLAGS) $(addprefix src/, $(SRCS)) main.c -o philo -pthread
clean:
		rm philo

fclean:

re: clean NAME
