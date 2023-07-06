
#include "_utility.hpp"


static bool	test_equel_vector()
{
	std::vector<int> std_tmp;
	ft::vector<int> ft_tmp;

	if (!check_equel_vector(ft_tmp, std_tmp))
	{
		g_result = "FAILED";
		return false;
	}
	g_result = "OK";
	return true;
}

static void	test_time()
{
	g_start1 = timer();
	std::vector<int> tmp1;
	g_end1 = timer();

	g_start2 = timer();
	ft::vector<int> tmp2;
	g_end2 = timer();
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
