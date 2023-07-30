#include "_utility.hpp"

static bool	test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		std::srand(time(0));
		int	size = rand() % T_SIZE;
		int	array[size];
		fill_array(array, size, 0, RAND_MAX);
		int size_big = size * (rand() % 10 + 1) ;
		int size_small = size / (rand() % 10 + 1);

		std::vector<int>	std_tmp(array, array + size);
		ft::vector<int>		ft_tmp(array, array + size);

		std_tmp.reserve(size_big);
		ft_tmp.reserve(size_big);

		if (!check_equel_vector(ft_tmp, std_tmp))
		{
			g_result = "FAILED";
			return false;
		}

		std_tmp.reserve(size_small);
		ft_tmp.reserve(size_small);

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
	std::srand(time(0));
	int rand_test[T_COUNT];
	fill_array(rand_test, T_COUNT, 1, T_SIZE * 10);
	int	size = rand() % T_SIZE;
	int	array[size];
	fill_array(array, size, 0, RAND_MAX);

	std::vector<int>	std_tmp(array, array + size);
	ft::vector<int>		ft_tmp(array, array + size);

	if (!g_leaks)
	{
		g_start1 = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_tmp.reserve(rand_test[i]);
		}
		g_end1 = timer();
	}

	g_start2 = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_tmp.reserve(rand_test[i]);
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
