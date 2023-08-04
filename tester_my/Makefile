NAME = mytest
CC = g++ -std=c++11
CFLAGS = -Wall -Wextra -Werror

$(NAME): tester.cpp _config.hpp
	$(CC) $(CFLAGS) -o $@ $^

all: $(NAME)

clean:
	rm -f $(NAME) *.txt

re			:	clean all

.PHONY: clean all re
