#include "_test_config.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	#if defined(VECTOR)
		typedef ft::vector<int>				FT;
		typedef std::vector<int>			STD;
	#elif defined(LIST)
		typedef ft::list<int>				FT;
		typedef std::list<int>				STD;
	#elif defined(DEQUE)
		typedef ft::deque<int>				FT;
		typedef std::deque<int>				STD;
	#elif defined(SET)
		typedef ft::set<int>				FT;
		typedef std::set<int>				STD;
	#elif defined(MULTISET)
		typedef ft::multiset<int>			FT;
		typedef std::multiset<int>			STD;
	#elif defined(MAP)
		typedef ft::map<int, int>			FT;
		typedef std::map<int, int>			STD;
	#elif defined(MULTIMAP)
		typedef ft::multimap<int, int>		FT;
		typedef std::multimap<int, int> 	STD;
	#elif defined(STACK)
		typedef ft::stack<int>				FT;
		typedef std::stack<int>				STD;
	#elif defined(QUEUE)
		typedef ft::queue<int>				FT;
		typedef std::queue<int>				STD;
	#elif defined(PRIORITY_QUEUE)
		typedef ft::priority_queue<int>		FT;
		typedef std::priority_queue<int>	STD;
	#elif defined(UNORDERED_SET)
		typedef ft::unordered_set<int>			FT;
		typedef std::unordered_set<int>			STD;
	#elif defined(UNORDERED_MULTISET)
		typedef ft::unordered_multiset<int>		FT;
		typedef std::unordered_multiset<int>	STD;
	#elif defined(UNORDERED_MAP)
		typedef ft::unordered_map<int>			FT;
		typedef std::unordered_map<int>			STD;
	#elif defined(UNORDERED_MULTIMAP)
		typedef ft::unordered_multimap<int>		FT;
		typedef std::unordered_multimap<int>	STD;
	#endif

	bool	leaks = false;
	time_t	start_ft, start_std, end_ft, end_std;

	if (argc == 2 && !std::strcmp(argv[1], "leaks"))
	{
		leaks = true;
	}

	std::srand(time(0));
	if (leaks)
	{
		test_time<FT, STD>(leaks, start_ft, start_std, end_ft, end_std);
	}
	else
	{
		if (test_all<FT, STD>())
		{
			printElement("OK");
			test_time<FT, STD>(leaks, start_ft, start_std, end_ft, end_std);
			printTime(start_ft, start_std, end_ft, end_std);
		}
		else
		{
			printElement("FAILED");
			return 1;
		}
	}

	return 0;
}
