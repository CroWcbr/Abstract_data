#include "_utility.hpp"

static bool	test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		std::srand(time(0));
		int	size = rand() % T_SIZE;
		int	array[size];
		fill_array(array, size, 0, RAND_MAX);

		std::vector<int>	std_test(array, array + size);
		ft::vector<int>		ft_test(array, array + size);

		std::vector<int> std_tmp = std_test;
		ft::vector<int> ft_tmp = ft_test;

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
	int	array[T_SIZE];
	fill_array(array, T_SIZE, 0, RAND_MAX);

	std::vector<int>	std_test(array, array + T_SIZE);
	ft::vector<int>		ft_test(array, array + T_SIZE);

	if (!g_leaks)
	{
		g_start1 = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std::vector<int> std_tmp = std_test;
		}
		g_end1 = timer();
	}

	g_start2 = timer();
	for (int i = 0; i < T_COUNT; ++i)
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
