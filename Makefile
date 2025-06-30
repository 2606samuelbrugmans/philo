CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -pthread

NAME = philo

SRCS = big_meower.c monitor.c philo.c routine.c smol_kind.c

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

