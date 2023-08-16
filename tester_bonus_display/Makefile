.DEFAULT_GOAL := error

PROGRAMS	=	unordered_set \
				unordered_multiset \
				unordered_map \
				unordered_multimap \
				fibonacci_heap

CC			=	g++ -std=c++11
CFLAGS		=	-Wall -Wextra -Werror

error:
	@echo "Please specify a target : make *****"

all: $(PROGRAMS)

unordered_set	:	test_unordered_set.cpp
					$(CC) $(STD) $(CFLAGS) -o $@ $< 

unordered_multiset	:	test_unordered_multiset.cpp
						$(CC) $(STD) $(CFLAGS) -o $@ $< 

unordered_map	:	test_unordered_map.cpp
					$(CC) $(STD) $(CFLAGS) -o $@ $< 

unordered_multimap	:	test_unordered_multimap.cpp
						$(CC) $(STD) $(CFLAGS) -o $@ $< 

fibonacci_heap	:	test_fibonacci_heap.cpp
					$(CC) $(STD) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(PROGRAMS)

re: clean all

.PHONY: clean all
