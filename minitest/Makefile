.DEFAULT_GOAL := error

PROGRAMS	=	vector_std \
				vector_ft \
				list_std \
				list_ft \
				deque_std \
				deque_ft \
				set_std \
				set_ft \
				multiset_std \
				multiset_ft \
				map_std \
				map_ft \
				multimap_std \
				multimap_ft \
				stack_std \
				stack_ft \
				queue_std \
				queue_ft \
				priority_queue_std \
				priority_queue_ft \
				unordered_set_std \
				unordered_set_ft


CC			=	g++ -std=c++98
CC11		=	g++ -std=c++11
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

set_std		:	set_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

set_ft		:	set_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

multiset_std	:	multiset_test.cpp
					$(CC) $(STD) $(CFLAGS) -o $@ $< 

multiset_ft	:	multiset_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $<

map_std		:	map_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $<

map_ft		:	map_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $<

multimap_std:	multimap_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $<

multimap_ft	:	multimap_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $<

stack_std	:	stack_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

stack_ft	:	stack_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

queue_std	:	queue_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

queue_ft	:	queue_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

priority_queue_std	:	priority_queue_test.cpp
						$(CC) $(STD) $(CFLAGS) -o $@ $< 

priority_queue_ft	:	priority_queue_test.cpp
						$(CC) $(FT) $(CFLAGS) -o $@ $< 

unordered_set_std	:	unordered_set_test.cpp
						$(CC11) $(STD) $(CFLAGS) -o $@ $< 

unordered_set_ft	:	unordered_set_test.cpp
						$(CC) $(FT) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(PROGRAMS)

.PHONY: clean
