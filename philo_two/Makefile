CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread #-g3 -fsanitize=address

SRCS = ./srcs/philo.c ./srcs/philo2.c ./srcs/monitor.c ./srcs/ft_atoi.c ./srcs/ft_putendl_fd.c ./srcs/ft_putnbr_fd.c ./srcs/ft_putstr_fd.c ./srcs/ft_itoa.c ./srcs/ft_strjoin.c
OBJS = ${SRCS:.c=.o}

NAME =	philo_two

LIB =	philo_two.a

LINK = ar rcs

${NAME}:	${OBJS}
			${LINK} ${LIB} ${OBJS}
			ranlib philo_two.a
			${CC} ${CFLAGS} ${LIB} -o ${NAME}
			rm ${LIB}



all:		${NAME}

bonus:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f philo_one.a
			rm -f a.out

re: 		fclean all

.PHONY: all clean fclean re
