#include "tester.hpp"

void printElement(std::string t) {
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
	int		fd_log = open("./logs.txt", O_RDWR | O_CREAT , 0777 | O_APPEND, S_IRUSR | S_IWUSR);
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

		dup2(fd_log, 2);
		close(fd_log);
		execve(_CXX, test_args, env);
		std::cout << "execve: error: " << strerror(errno) << std::endl;
		exit(errno);
	}
	close(fd_log);
	waitpid(pid, status, WUNTRACED | WCONTINUED);
}

static void testExecution(int *status, std::string output, char **env)
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
			printElement(output);
			printElement(RED + "SEGFAULT" + RESET);
			std::cout << std::endl;
		}
		else if (*status == 14)
		{
			printElement(output);
			printElement(YELLOW + "TIMEOUT" + RESET);
			std::cout << std::endl;
		}
	}
	else if (*status == 256)
	{
		printElement(output);
		printElement(RED + "NOT COMPILED" + RESET);
		std::cout << std::endl;
	}
	else
	{
		printElement(output);
		printElement(YELLOW + "UNKNOWN" + RESET);
		std::cout << std::endl;
	}
}

static void	test(std::vector<std::string> test, char **env)
{
	for(const auto& t : test)
	{
		int	status = 0;
		std::string tmp = t.substr(t.find_last_of('/') + 4);
		std::string output = tmp.erase(tmp.length() - 4);

		testCompile(&status, t, env);
		testExecution(&status, output, env);
	}
}

int main(int argc, char **argv, char **env)
{
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

	return 0;
}
