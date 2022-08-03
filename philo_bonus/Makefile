SRCS			=  main.c handle_args.c libft_utils.c print_messages.c start_philo.c timeline_utils.c philo_routine.c gods_overseeing.c routine_utils.c monitoring_loop.c

SRCS_DIR		= srcs/

SRCS_PATH	 	= $(SRCS:%=$(SRCS_DIR)%)

OBJS		 	= $(SRCS_PATH:%.c=%.o)

NAME		 	= philo_bonus

INCS			= includes

RM		 	= rm -f

CC			= cc -Wall -Wextra -Werror -pthread

all:			${NAME}

$(NAME):		${OBJS}
			$(CC) -I $(INCS) $(SRCS_PATH) -o $(NAME)

clean:
			${RM} ${OBJS}

fclean:			clean
			${RM} ${NAME}

re:			fclean ${NAME}

.PHONY:			all clean fclean re bonus
