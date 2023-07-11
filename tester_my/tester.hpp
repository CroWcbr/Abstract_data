#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <fstream>

#define _CXX				"/usr/bin/g++"
#define _CXX_FLAGS			"-Wall -Wextra -Werror"
#define _EXEC_NAME			"test_container"

#define _VALGRIND			"/usr/bin/valgrind"
#define _VALGRIND_FLAGS1	"--leak-check=full"
#define _VALGRIND_FLAGS2	"--track-origins=yes"
#define _VALGRIND_EXEC_NAME	"./test_container"

#define _LOGS_COMPILE		"./logs_compile.txt"
#define _LOGS_LEAKS			"./logs_leaks.txt"

const std::string	GREEN = "\x1B[1;32m";
const std::string	RED = "\x1B[1;31m";
const std::string	YELLOW = "\x1B[1;33m";
const std::string	WHITE = "\x1B[1;39m";
const std::string	RESET = "\033[0m";

const std::vector<std::pair<std::string, std::vector<std::string> > > _containers = 
	{
		{"vector", 
			{
				"./test/vector/01_constructor.cpp",
				"./test/vector/02_constructor(std iterators).cpp"
			},
		}
	};
