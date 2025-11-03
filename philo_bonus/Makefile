CC = cc
NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra -pthread -g
SRC = main.c parser.c utils.c monitor.c thread_utils.c philo_routine.c init.c
OBJ = $(SRC:.c=.o)
OBJ_PATH = obj/
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I.  -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	$(MAKE) CFLAGS="$(CFLAGS) -g" all
