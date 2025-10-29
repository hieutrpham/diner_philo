CC = cc
NAME = philo
CFLAGS = -Wall -Werror -Wextra -pthread -g
SRC = main.c parser.c utils.c monitor.c thread_utils.c philo_routine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$.o: $.c
	$(CC) $(CFLAGS) -I.  -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -g" all
