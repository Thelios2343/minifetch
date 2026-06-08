NAME = Wired-fetch

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c sysinfo.c
OBJS = $(SRCS:.c=.o)

HEADERS = sysinfo.h ansicolors.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
