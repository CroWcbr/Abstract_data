#include "tester.hpp"
#include "_config.hpp"

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

static bool	testCompile(std::string func_filename, char **env, std::string container)
{
	int		status = 0;
	int		fd_log = open("./logs_compile.txt", O_RDWR , 0777 | O_APPEND, S_IRUSR | S_IWUSR);
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		std::transform(container.begin(), container.end(), container.begin(), ::toupper);
		std::string container_type = "-D " + container;
		std::string count_type = "-D T_COUNT=" + std::to_string(T_COUNT);
		std::string size_type = "-D T_SIZE=" + std::to_string(T_SIZE);
		char* const test_args[] = {
			const_cast<char*>(_CXX),
			const_cast<char*>(_CXX_STANDART),
			// const_cast<char*>(_CXX_WALL),
			// const_cast<char*>(_CXX_WEXTRA),
			// const_cast<char*>(_CXX_WERROR),
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
		printElement(RED + "UNKNOWN" + RED);
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

static void	test(std::string container, std::vector<std::string> test, char **env)
{
	for(const auto& t : test)
	{
		std::string tmp = t.substr(t.find_last_of('/') + 4);
		std::string output = tmp.erase(tmp.length() - 4);

		printElement(output);
		fflush(stdout);

		if (testCompile(t, env, container) && testExecution(env))
			testLeak(t, env);

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
			// std::cout << "|                                          " << c.first << "                                          |" << std::endl;
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
	return 0;
}
