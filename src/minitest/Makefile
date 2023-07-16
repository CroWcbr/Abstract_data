.DEFAULT_GOAL := error



PROGRAMS	=	vector_std \
				vector_ft

CC			=	g++
CFLAGS		=	-Wall -Wextra -Werror

STD			=	-D TYPE=1
FT			=	-D TYPE=2

error:
	@echo "Please specify a target : make *****"

all: $(PROGRAMS)

vector_std	:	vector_test.cpp
				$(CC) $(STD) $(CFLAGS) -o $@ $< 

vector_ft	:	vector_test.cpp
				$(CC) $(FT) $(CFLAGS) -o $@ $< 

clean:
	rm -f $(PROGRAMS)

.PHONY: clean