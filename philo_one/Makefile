CC = gcc
CFLAGS = -Wall -Wextra -Werror -D_REENTRANT #-g3 -fsanitize=address

SRCS = ./srcs/main.c ./srcs/ft_atoi.c
OBJS = ${SRCS:.c=.o}

NAME =	philo_one

LIB =	philo_one.a

LINK = ar rcs

${NAME}:	${OBJS}
			${LINK} ${LIB} ${OBJS}
			ranlib philo_one.a
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
