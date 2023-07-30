#ifndef TESTER_HPP
#define TESTER_HPP

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
#include <stdio.h>

#define _CXX				"/usr/bin/g++"
#define _CXX_WALL			"-Wall"
#define _CXX_WEXTRA			"-Wextra"
#define _CXX_WERROR			"-Werror"
#define _EXEC_NAME			"test_container"
#define	_CXX_STANDART		"-std=c++98"

#define _VALGRIND			"/usr/bin/valgrind"
#define _VALGRIND_FLAGS1	"--leak-check=full"
#define _VALGRIND_FLAGS2	"--track-origins=yes"
#define _VALGRIND_EXEC_NAME	"./test_container"

#define _LOGS_COMPILE		"./logs_compile.txt"
#define _LOGS_LEAKS			"./logs_leaks.txt"
#define _LOGS_LEAKS_TMP		"./logs_leaks_tmp.txt"

const std::string	GREEN = "\x1B[1;32m";
const std::string	RED = "\x1B[1;31m";
const std::string	YELLOW = "\x1B[1;33m";
const std::string	WHITE = "\x1B[1;39m";
const std::string	RESET = "\033[0m";

const std::vector<std::pair<std::string, std::vector<std::string> > > _containers = 
	{
		{"vector", 
			{
				"./test/containers/01_empty_constructor.cpp"
			},
		}
	};

#endif