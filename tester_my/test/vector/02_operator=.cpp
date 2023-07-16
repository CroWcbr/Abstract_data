#include "_utility.hpp"

static bool	test_all()
{
	std::vector<int> std_test(T_SIZE);
	ft::vector<int> ft_test(T_SIZE);
	std::srand(std::time(0));

	for (int i = 0; i < T_SIZE; ++i)
	{
		int random = std::rand();
		std_test[i] = random;
		ft_test[i] = random;
	}

	{
		std::vector<int> std_tmp;
		std_tmp = std_test;
		ft::vector<int> ft_tmp;
		ft_tmp = ft_test;

		std::cerr << std::endl << std_test.size() << "\t" << ft_test.size() << std::endl;
		if (!check_equel_vector(ft_tmp, std_tmp))
		{
			g_result = "FAILED";
			return false;
		}
	}
	g_result = "OK";
	return true;
}

static void	test_time()
{
	std::vector<int> std_test(T_SIZE);
	ft::vector<int> ft_test(T_SIZE);
	std::srand(std::time(0));

	for (int i = 0; i < T_SIZE; ++i)
	{
		std_test[i] = std::rand();
		ft_test[i] = std::rand();
	}

	g_start1 = timer();
	for (size_t i = 0; i < T_COUNT; ++i)
	{
		std::vector<int> std_tmp = std_test;
	}
	g_end1 = timer();

	g_start2 = timer();
	for (size_t i = 0; i < T_COUNT; ++i)
	{
		ft::vector<int> ft_tmp = ft_test;
	}
	g_end2 = timer();
}

int main(int argc, char **argv)
{
	if (argc > 1 && !std::strcmp(argv[1], "leaks"))
	{
		g_leaks = true;
	}
	return test(test_all, test_time);
}
