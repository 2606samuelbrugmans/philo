CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -pthread

NAME = philo

SRCS = main.c routine.c eating.c sleep.c stop.c init.c cleanup.c utils.c

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

