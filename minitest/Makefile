.DEFAULT_GOAL := error

PROGRAMS	=	vector_std \
				vector_ft \
				list_std \
				list_ft \
				deque_std \
				deque_ft \
				stack_std \
				stack_ft \
				set_std \
				set_ft \
				multiset_std \
				multiset_ft

CC			=	g++
# CFLAGS		=	-Wall -Wextra -Werror

STD			=	-D TYPE=1
FT			=	-D TYPE=2

error:
	@echo "Please specify a target : make *****"

all: $(PROGRAMS)

vector_std	:	vector_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

vector_ft	:	vector_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

list_std	:	list_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

list_ft	:		list_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

deque_std	:	deque_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

deque_ft	:		deque_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

stack_std	:	stack_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

stack_ft	:	stack_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

set_std		:	set_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

set_ft		:	set_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

multiset_std	:	multiset_test.cpp
					$(CC) $(STD) $(CFLAGS) -o $@ $< 

multiset_ft	:	multiset_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(PROGRAMS)

.PHONY: clean
