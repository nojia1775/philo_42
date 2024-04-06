CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c \
       src/parsing.c \
       src/utils.c \
       src/init_args.c \
       src/iter.c \
       src/loop_thread.c

OBJS = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

OBJS_DIR = obj

NAME = philo

$(OBJS_DIR)/%.o: src/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $^ -o $@ -g3

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
