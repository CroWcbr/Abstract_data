#include "_utility.hpp"

int	test_equel_vector()
{
	std::vector<int> std_tmp;
	ft::vector<int> ft_tmp;

	if (check_equel_vector(ft_tmp, std_tmp))
	{
		g_result = "FAILED";
		return 0;
	}
	g_result = "OK";
	return 1;
}

void	test_time()
{
	g_start1 = timer();
	std::vector<int> tmp1;
	g_end1 = timer();

	g_start2 = timer();
	ft::vector<int> tmp2;
	g_end2 = timer();
}

void	test_leaks()
{

}

int main()
{
	if (test_equel_vector())
	{
		printElement(g_result);
		test_time();
		printTime2();
		test_leaks();
	}

	std::cout << "02!" << std::endl;
}
