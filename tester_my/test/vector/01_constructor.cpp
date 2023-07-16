#include "_utility.hpp"

static bool	test_all()
{
//(1) empty container constructor (default constructor)
	{
		std::vector<int> std_tmp1;
		ft::vector<int> ft_tmp1;

		if (!check_equel_vector(ft_tmp1, std_tmp1))
		{
			g_result = "FAILED";
			return false;
		}
	}

//(2) fill constructor
	{
		std::vector<int> std_tmp2(T_SIZE, 100);
		ft::vector<int> ft_tmp2(T_SIZE, 100);

		if (!check_equel_vector(ft_tmp2, std_tmp2))
		{
			g_result = "FAILED";
			return false;
		}

//(3) range constructor
		std::vector<int> std_tmp3(std_tmp2.begin(), std_tmp2.end());
		ft::vector<int> ft_tmp3(ft_tmp2.begin(), ft_tmp2.end());
		if (!check_equel_vector(ft_tmp3, std_tmp3))
		{
			g_result = "FAILED";
			return false;
		}

//(4) copy constructor
		std::vector<int> std_tmp4(std_tmp2);
		ft::vector<int> ft_tmp4(ft_tmp2);
		if (!check_equel_vector(ft_tmp4, std_tmp4))
		{
			g_result = "FAILED";
			return false;
		}
	}

// the iterator constructor can also be used to construct from arrays:
	{
		int myints[] = {16,2,77,29};
		std::vector<int> std_tmp5(myints, myints + sizeof(myints) / sizeof(int));
		ft::vector<int> ft_tmp5(myints, myints + sizeof(myints) / sizeof(int));
		if (!check_equel_vector(ft_tmp5, std_tmp5))
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
	g_start1 = timer();
	for (size_t i = 0; i < T_COUNT; ++i)
	{
		std::vector<int> tmp1;
		std::vector<int> tmp2(T_SIZE, 100);
		std::vector<int> tmp3(tmp2);
		std::vector<int> tmp4(tmp3.begin(), tmp3.end());
	}
	g_end1 = timer();

	g_start2 = timer();
	for (size_t i = 0; i < T_COUNT; ++i)
	{
		ft::vector<int> tmp1;
		ft::vector<int> tmp2(T_SIZE, 100);
		ft::vector<int> tmp3(tmp2);
		ft::vector<int> tmp4(tmp3.begin(), tmp3.end());
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
