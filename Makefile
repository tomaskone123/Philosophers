NAME		=	Philosophers

HEADER		=	./inc

CC			=	cc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -pthread

SRCS		=	src/main.c \
				src/init.c \
				src/free.c \
				src/error.c \
				src/utils.c \
				src/utils2.c \
				src/log.c \
				src/actions.c \
				src/simulation.c \


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

val			:
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./philo 5 200 200 200 200

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
