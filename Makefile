NAME		=	philo

HEADER		=	./inc

CC			=	cc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -pthread

SRCS		=	src/main.c \
				src/init.c \
				src/utils.c \
				src/free.c \
				src/error.c \
				src/simulation.c \
				src/actions.c \


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

git:
	@msg="$(wordlist 2,999,$(MAKECMDGOALS))"; \
	if [ -z "$$msg" ]; then \
		echo "Error: You must provide a commit message."; \
		exit 1; \
	fi; \
	git add .; \
	git commit -m "$$msg"; \
	git push

%:
	@:

re			:	fclean all
