#include "_utility.hpp"

static bool	test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		std::srand(time(0));
		int	size = rand() % T_SIZE;
		int	array[size];
		fill_array(array, size, 0, RAND_MAX);

	//(1) empty container constructor (default constructor)
		std::vector<int>	std_tmp1;
		ft::vector<int>		ft_tmp1;

		if (!check_equel_vector(ft_tmp1, std_tmp1))
		{
			g_result = "FAILED";
			return false;
		}

	//(2) fill constructor
		std::vector<int> std_tmp2_1(size);
		ft::vector<int> ft_tmp2_1(size);

		if (!check_equel_vector(ft_tmp2_1, std_tmp2_1))
		{
			g_result = "FAILED";
			return false;
		}

		std::vector<int> std_tmp2_2(size, size);
		ft::vector<int> ft_tmp2_2(size, size);

		if (!check_equel_vector(ft_tmp2_2, std_tmp2_2))
		{
			g_result = "FAILED";
			return false;
		}

	//(3) range constructor
		std::vector<int> std_tmp3(array, array + size);
		ft::vector<int> ft_tmp3(array, array + size);
		if (!check_equel_vector(ft_tmp3, std_tmp3))
		{
			g_result = "FAILED";
			return false;
		}

	//(4) copy constructor
		std::vector<int> std_tmp4(std_tmp3);
		ft::vector<int> ft_tmp4(ft_tmp3);
		if (!check_equel_vector(ft_tmp4, std_tmp4))
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
	fill_array(rand_test, T_COUNT, 0, T_SIZE);
	int	array[T_SIZE];
	fill_array(array, T_SIZE, 0, RAND_MAX);

	if (!g_leaks)
	{
		g_start1 = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std::vector<int> tmp1;
			std::vector<int> tmp2(T_SIZE, rand_test[i]);
			std::vector<int> tmp4(array, array + rand_test[i]);
			std::vector<int> tmp3(tmp4);
		}
		g_end1 = timer();
	}

	g_start2 = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft::vector<int> tmp1;
		ft::vector<int> tmp2(T_SIZE, rand_test[i]);
		ft::vector<int> tmp4(array, array + rand_test[i]);
		ft::vector<int> tmp3(tmp4);
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
