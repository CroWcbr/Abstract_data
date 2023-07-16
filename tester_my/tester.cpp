#include "tester.hpp"

static void printElement(std::string t) {
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

static void testCompile(int *status, std::string func_filename, char **env)
{
	int		fd_log = open("./logs_compile.txt", O_RDWR , 0777 | O_APPEND, S_IRUSR | S_IWUSR);
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		char* const test_args[] = {
			const_cast<char*>(_CXX),
			const_cast<char*>("-o"),
			const_cast<char*>(_EXEC_NAME),
			const_cast<char*>(func_filename.c_str()),
			const_cast<char*>("-std=c++98"),
			const_cast<char*>("-Wall"),
			const_cast<char*>("-Wextra"),
			const_cast<char*>("-Werror"),
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
	waitpid(pid, status, WUNTRACED | WCONTINUED);
	close(fd_log);
}

static void testExecution(int *status, char **env)
{
	pid_t	pid;

	if (*status == 0)
	{
		*status = -1;
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
		waitpid(pid, status, WUNTRACED | WCONTINUED);
		if (*status == 0)
		{
			;
		}
		else if (*status == 11)
		{
			printElement(RED + "SEGFAULT" + RESET);
		}
		else if (*status == 14)
		{
			printElement(YELLOW + "TIMEOUT" + RESET);
		}
	}
	else if (*status == 256)
	{
		printElement(RED + "NOT COMPILED" + RESET);
	}
	else
	{
		printElement(YELLOW + "UNKNOWN" + RESET);
	}
}

static void	testLeak(int *status, std::string func_filename, char **env)
{
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
	waitpid(pid, status, WUNTRACED | WCONTINUED);
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

static void	test(std::vector<std::string> test, char **env)
{
	for(const auto& t : test)
	{
		int	status = 0;
		std::string tmp = t.substr(t.find_last_of('/') + 4);
		std::string output = tmp.erase(tmp.length() - 4);

		printElement(output);
		fflush(stdout);

		testCompile(&status, t, env);
		testExecution(&status, env);
		if (!status)
			testLeak(&status, t, env);

		std::cout << std::endl;
		fflush(stdout);
	}
}

int main(int argc, char **argv, char **env)
{
	if (argc > 1)
		MOD = argv[1];
	if (argc > 2)
		COUNT = std::stoi(argv[2]);
	if (argc > 3)
		SIZE = std::stoi(argv[3]);

	FILE* file;
	file = fopen(_LOGS_COMPILE, "w");
	fclose(file);
	file = fopen(_LOGS_LEAKS, "w");
	fclose(file);

	for(const auto& c : _containers)
	{
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                          " << c.first << "                                          |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		printElement("FUNCTION");
		printElement(WHITE + "RESULT" + RESET);
		printElement(WHITE + "FT TIME" + RESET);
		printElement(WHITE + "STD TIME" + RESET);
		printElement(WHITE + "LEAKS" + RESET);
		std::cout << std::endl;
		test(c.second, env);
	}
	unlink(_LOGS_LEAKS_TMP);
	unlink(_EXEC_NAME);
	return 0;
}
