NAME		=	philo

HEADER		=	./inc

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -pthread

SRCS		=	src/main.c \
				src/init.c \
				src/utils.c \
				src/free.c \
				src/error.c \
				src/simulation.c \
				src/actions.c \
				src/monitor.c \


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

val			:
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./philo 1 4 5 6 7

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
