#include "../_test_config.hpp"

static bool	test_all()
{
	return false;
}

static void	test_time()
{

}

int main(int argc, char **argv)
{
	#ifdef CONTAINER
	
		std::cout << TOSTRING(CONTAINER) << std::endl;
std::cout << TOSTRING(STD) << std::endl;
std::cout << TOSTRING(FT) << std::endl;
		// std::cout << TOSTRING(TYPE) << std::endl;
		// std::CONTAINER<int> tmp;
		if (argc > 1 && !std::strcmp(argv[1], "leaks"))
		{
			g_leaks = true;
		}
		return test(test_all, test_time);
	#else
		return false;
	#endif
}
