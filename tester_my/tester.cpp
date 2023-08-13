#include "_config.hpp"
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
#include <algorithm>
#include <random>

const std::string	GREEN = "\x1B[1;32m";
const std::string	RED = "\x1B[1;31m";
const std::string	YELLOW = "\x1B[1;33m";
const std::string	WHITE = "\x1B[1;39m";
const std::string	RESET = "\033[0m";

static void printElement(std::string t)
{
	if (t == "OK")
	{
		t = GREEN + t + RESET;
	}
	else if (t == "FAILED")
	{
		t = RED + t + RESET;
	}
	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
}

static bool	testCompile(std::string func_filename, char **env, std::string container, bool leak)
{
	int		status = 0;
	int		fd_log = open("./logs_compile.txt", O_RDWR , 0777 | O_APPEND, S_IRUSR | S_IWUSR);
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		std::transform(container.begin(), container.end(), container.begin(), ::toupper);
		std::string container_type = "-D " + container;
		std::string count_type = "-D T_COUNT=" + (leak ? std::to_string(T_COUNT_LEAKS) : std::to_string(T_COUNT));
		std::string size_type = "-D T_SIZE=" + (leak ? std::to_string(T_SIZE_LEAKS) : std::to_string(T_SIZE));
		char* const test_args[] = {
			const_cast<char*>(_CXX),
			const_cast<char*>(container == "UNORDERED_SET" || container == "UNORDERED_MULTISET" || \
							container == "UNORDERED_MAP" || container == "UNORDERED_MULTIMAP" ?	\
							_CXX_STANDART_11 : _CXX_STANDART_98),
			const_cast<char*>(_CXX_WALL),
			const_cast<char*>(_CXX_WEXTRA),
			const_cast<char*>(_CXX_WERROR),
			const_cast<char*>(_MAIN_PROG),
			const_cast<char*>("-include"),
			const_cast<char*>(func_filename.c_str()),
			const_cast<char*>("-o"),
			const_cast<char*>(_EXEC_NAME),
			const_cast<char*>(container_type.c_str()),
			const_cast<char*>(count_type.c_str()),
			const_cast<char*>(size_type.c_str()),
			NULL
		};
		lseek(fd_log, 0, SEEK_END);
		for(int i = 0; test_args[i]; ++i)
		{
			dprintf(fd_log, "%s ", test_args[i]);
		}
		dprintf(fd_log, "\n");
		dup2(fd_log, 2);
		close(fd_log);
		execve(_CXX, test_args, env);
		std::cout << "execve: error: " << strerror(errno) << std::endl;
		exit(errno);
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	close(fd_log);

	if (status == 0)
		return true;
	else if (status == 256)
	{
		printElement(RED + "NOT COMPILED" + RESET);
	}
	else
	{
		printElement(YELLOW + "UNKNOWN" + RESET);
	}
	return false;
}

static bool	testExecution(char **env)
{
	pid_t	pid;
	int		status = 0;

	pid = fork();
	if (!pid)
	{
		char* test_args[] = {
			NULL
		};
		alarm(20);
		execve(_EXEC_NAME, test_args, env);
		std::cout << "execve: error: " << strerror(errno) << std::endl;
		exit(errno);
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	if (status == 0)
	{
		return true;
	}
	else if (status == 11)
	{
		printElement(RED + "SEGFAULT" + RESET);
	}
	else if (status == 14)
	{
		printElement(YELLOW + "TIMEOUT" + RESET);
	}
	else if (status != 256)
	{
		printElement(RED + "UNKNOWN" + RESET);
	}
	return false;
}

static void	testLeak(std::string func_filename, char **env)
{
	int		status = 0;
	int		fd_log = open(_LOGS_LEAKS_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		char* const test_args[] = {
			const_cast<char*>(_VALGRIND),
			const_cast<char*>(_VALGRIND_FLAGS1),
			const_cast<char*>(_VALGRIND_FLAGS2),
			const_cast<char*>(_VALGRIND_EXEC_NAME),
			const_cast<char*>("leaks"),
			NULL
		};
		lseek(fd_log, 0, SEEK_END);
		dprintf(fd_log, "%s ", func_filename.c_str());
		for(int i = 0; test_args[i]; ++i)
		{
			dprintf(fd_log, "%s ", test_args[i]);
		}
		dprintf(fd_log, "\n");
		dup2(fd_log, 2);
		close(fd_log);
		execve(_VALGRIND, test_args, env);
		std::cout << "execve: error: " << strerror(errno) << std::endl;
		exit(errno);
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	close(fd_log);

	std::ifstream source_file(_LOGS_LEAKS_TMP);
	if (!source_file.is_open())
	{
		printElement("FAILED OPEN LOG");
	}
	else
	{
		std::string line;
		int	test = 0;
		while (std::getline(source_file, line))
		{
			if (line.find("in use at exit: 0 bytes in 0 blocks") != std::string::npos)
			{
				test++;
			}
			if (line.find("ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)") != std::string::npos)
			{
				test++;
			}
		}
		if (test == 2)
			printElement("OK");
		else
			printElement("FAILED");

		source_file.clear();
		source_file.seekg(0, std::ios::beg);
		std::ofstream destination_file(_LOGS_LEAKS, std::ios::app);
		if (!destination_file)
		{
			std::cerr << "Failed to open: " << _LOGS_LEAKS << std::endl;
		}
		else
		{
			destination_file << std::endl;
			destination_file << source_file.rdbuf();
		}
		destination_file.close();
		source_file.close();
	}
}

void create_int_data_file(std::string container)
{
	std::random_device	rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> numElementsDist(0, T_SIZE);
	std::uniform_int_distribution<int> elementDist(0, T_COUNT);

	std::ofstream outputFile(_DATA_FILE);
	if (!outputFile)
	{
		std::cerr << "ERROR: " << _DATA_FILE << std::endl;
		exit(1);
	}

	for (int i = 0; i < T_COUNT; ++i)
	{
		int numElements = numElementsDist(generator);
		if (container == "map" || container == "multimap" || container == "unordered_map" || container == "unordered_multimap")
			numElements *= 2;
		for (int j = 0; j < numElements; ++j)
		{
			int randomElement = elementDist(generator);
			outputFile << randomElement << " ";
		}
		outputFile << "\n";
	}

	outputFile.close();
}

static void	test(std::string container, std::vector<std::string> test, char **env)
{
	if (test.size() > 0)
	{
		create_int_data_file(container);
	}
	for(const auto& t : test)
	{
		std::string tmp = t.substr(t.find_last_of('/') + 4);
		std::string output = tmp.erase(tmp.length() - 4);

		printElement(output);
		fflush(stdout);

		if (testCompile(t, env, container, false) && testExecution(env))
		{
			if (testCompile(t, env, container, true))
				testLeak(t, env);
		}

		std::cout << std::endl;
		fflush(stdout);
	}
}

int main(int argc, char **argv, char **env)
{
	FILE* file;
	file = fopen(_LOGS_COMPILE, "w");
	fclose(file);
	file = fopen(_LOGS_LEAKS, "w");
	fclose(file);

	std::cout << "Number of Count : \t" << T_COUNT << std::endl;
	std::cout << "Number of Size : \t" << T_SIZE << std::endl;
	for(const auto& c : _containers)
	{
		if (argc == 1 || argv[1] == c.first)
		{
			std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
			int padding = (93 - c.first.length() - 2) / 2;
			std::cout << '|' << std::setw(padding + c.first.length()) << std::right << c.first << std::setw(padding + (c.first.length() % 2 == 0 ? 1 : 0)) << '|' << std::endl;
			std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
			printElement("FUNCTION");
			printElement(WHITE + "RESULT" + RESET);
			printElement(WHITE + "FT TIME" + RESET);
			printElement(WHITE + "STD TIME" + RESET);
			printElement(WHITE + "LEAKS" + RESET);
			std::cout << std::endl;
			test(c.first, c.second, env);
		}
	}
	unlink(_LOGS_LEAKS_TMP);
	unlink(_EXEC_NAME);
	// unlink(_DATA_FILE);
	return 0;
}
