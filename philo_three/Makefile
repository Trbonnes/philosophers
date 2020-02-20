CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

SRCS = ./srcs/philo.c ./srcs/philo2.c ./srcs/monitor.c ./srcs/ft_atoi.c ./srcs/ft_putendl_fd.c ./srcs/ft_putnbr_fd.c ./srcs/ft_putstr_fd.c ./srcs/ft_itoa.c ./srcs/ft_strjoin.c
OBJS = ${SRCS:.c=.o}

NAME =	philo_three

LIB =	philo_three.a

LINK = ar rcs

${NAME}:	${OBJS}
			${LINK} ${LIB} ${OBJS}
			ranlib philo_three.a
			${CC} ${CFLAGS} ${LIB} -o ${NAME}
			rm ${LIB}



all:		${NAME}

bonus:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f a.out

re: 		fclean all

.PHONY: all clean fclean re
