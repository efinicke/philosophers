
NAME					=		philo
SRC_DIR					=		./srcs/
INC_DIR					=		./inc/
SRCS					=		00_main.c \
										01_parsing.c \
										02_fill_env.c \
										03_run_threads.c \
										04_philo_routine.c \
										05_runtime_watcher.c \
										06_time.c \
										07_clean.c \
										08_print.c \
										09_utils.c

SRC_BASENAME			=       $(addprefix $(SRC_DIR), $(SRCS))
OBJS					=		$(SRC_BASENAME:.c=.o)
CC						=		gcc
FLAGS					=		-Wall -Wextra -Werror -pthread -I $(INC_DIR)

.c.o			:
						$(CC) $(FLAGS) -c $< -o $@

all				:		$(NAME)

$(NAME)			:		$(OBJS)
						$(CC) $(FLAGS) -o $(NAME) $(OBJS)
						@echo "$(NAME) created !"

clean			:
						rm -rf $(OBJS)
						@echo "objects deleted"

fclean			:		clean
						rm -f $(NAME)
						@echo "$(NAME) deleted"

re		:		fclean all