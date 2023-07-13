#include "_utility.hpp"

int	test_equel_vector()
{
	// std::vector<int> std_tmp;
	// ft::vector<int> ft_tmp;

	std::vector<int> tmp(20, 4);
	std::vector<int> std_tmp(tmp.begin(), tmp.end());
	ft::vector<int> ft_tmp(tmp.begin(), tmp.end());

// 	std::cerr << "\t" << std_tmp.size() << std::endl;
// 	std::cerr << "\t" << ft_tmp.size() << std::endl;
// std::cerr << "\t" << std_tmp[0] << "\t" << std_tmp[1] << std::endl;
// std::cerr << "\t" << ft_tmp[0] << "\t" << ft_tmp[1] << std::endl;

	if (!check_equel_vector(ft_tmp, std_tmp))
	{
			// std::cout << "\t\t\treturn FAILED;" << std::endl;
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

int main(int argc, char **argv)
{
	if (argc > 1 && !std::strcmp(argv[1], "leaks"))
	{
		g_leaks = true;
	}
	if (test_equel_vector())
	{
		if (!g_leaks)
			printElement(g_result);
		test_time();
		if (!g_leaks)
			printTime();
	}
	else	if (!g_leaks)
	{
		printElement(g_result);
		return 1;	
	}

	return 0;
}
