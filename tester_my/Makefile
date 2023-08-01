NAME = mytest
CC = g++
CFLAGS = -Wall -Wextra -Werror

$(NAME): tester.cpp tester.hpp _config.hpp
	$(CC) $(CFLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(NAME) *.txt

re			:	clean all

.PHONY: clean all re
