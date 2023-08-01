#ifndef CONFIG_HPP
#define CONFIG_HPP

#define		_CXX				"/usr/bin/g++"
#define		_CXX_WALL			"-Wall"
#define		_CXX_WEXTRA			"-Wextra"
#define		_CXX_WERROR			"-Werror"
#define		_EXEC_NAME			"test_container"
#define		_CXX_STANDART		"-std=c++98"

#define		_VALGRIND			"/usr/bin/valgrind"
#define		_VALGRIND_FLAGS1	"--leak-check=full"
#define		_VALGRIND_FLAGS2	"--track-origins=yes"
#define		_VALGRIND_EXEC_NAME	"./test_container"

#define		_LOGS_COMPILE		"./logs_compile.txt"
#define		_LOGS_LEAKS			"./logs_leaks.txt"
#define		_LOGS_LEAKS_TMP		"./logs_leaks_tmp.txt"

#define		_MAIN_PROG			"./test/main.cpp"
#define		T_COUNT				10000
#define		T_SIZE				1000

#include <vector>
#include <string>

const std::vector<std::pair<std::string, std::vector<std::string> > > _containers = 
	{
		{"vector", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"list", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"deque", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"set", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"multiset", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"map", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"multimap", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"stack", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"queue", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		},
		{"priority_queue", 
			{
				"./test/containers/01_empty_constructor.hpp"
			},
		}
	};

#endif
