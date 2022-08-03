SRCS			=  main.c handle_args.c libft_utils.c print_messages.c start_philo.c timeline_utils.c philo_routine.c gods_overseeing.c routine_utils.c

BONUS			= checker.c \

SRCS_DIR		= srcs/

BONUS_DIR		= srcs_bonus/

SRCS_PATH	 	= $(SRCS:%=$(SRCS_DIR)%)

SRCS_B_PATH 		= $(BONUS:%=$(BONUS_DIR)%)

OBJS		 	= $(SRCS_PATH:%.c=%.o)

OBJS_BONUS		= $(SRCS_B_PATH:%.c=%.o)

NAME		 	= philo

NAME_BONUS		= philo

INCS			= includes

RM		 	= rm -f

CC			= cc -Wall -Wextra -Werror -pthread

all:			${NAME}

$(NAME):		${OBJS}
			$(CC) -I $(INCS) $(SRCS_PATH) -o $(NAME)

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:			clean
			${RM} ${NAME} ${NAME_BONUS}

re:			fclean ${NAME}

bonus:			${OBJS_BONUS}
			$(CC) -I $(INCS) $(SRCS_B_PATH) -o $(NAME_BONUS)

.PHONY:			all clean fclean re bonus
