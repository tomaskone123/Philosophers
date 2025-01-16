NAME		=	philo

HEADER		=	./inc

CC			=	gcc

CFLAGS		=	-fsanitize=address -Werror -Wall -Wextra -g -I $(HEADER) -pthread

SRCS		=	src/main.c \
				src/init.c \
				src/utils.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
