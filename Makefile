NAME = prog

SRCS = main.c get_next_line.c get_next_line_utils.c

BUFFER = -D BUFFER_SIZE=1
# BUFFER = -D BUFFER_SIZE=10

CC = cc -Wall -Werror -Wextra

all: $(NAME)
	./$(NAME)

$(NAME): clean
	$(CC) $(SRCS) $(BUFFER) -o prog

l:
	leaks --atExit -- ./$(NAME)

clean:
	rm -f $(NAME)
