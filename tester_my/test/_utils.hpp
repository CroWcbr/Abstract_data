#pragma once

#include "_define.hpp"
#include <cstdlib>
#include <sys/time.h>

time_t	timer()
{
	struct timeval start = {};
	gettimeofday(&start, NULL);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

void	fill_array_random(int *array, int size, int min, int max)
{
	for(int i = 0; i < size; ++i)
	{
		array[i] = rand() % (max - min + 1) + min;
	}
}

template<class FT, class STD>
bool	check_equel_container(FT ft, STD std)
{
	if (ft.size() != std.size())
	{
		return false;
	}
#if defined(VECTOR) || defined(LIST) || defined(SET) || defined(MULTISET) || defined(MAP) || defined(MULTIMAP)
	typename FT::iterator	ft_it_s = ft.begin();
	typename FT::iterator	ft_it_e = ft.end();
	typename STD::iterator	std_it_s = std.begin();
	typename STD::iterator	std_it_e = std.end();
	while (ft_it_s != ft_it_e)
	{
	#if defined(VECTOR) || defined(LIST) || defined(SET) || defined(MULTISET)
		if (*ft_it_s != *std_it_s)
	#elif defined(MAP) || defined(MULTIMAP)
		if ((*ft_it_s).first != (*std_it_s).first || (*ft_it_s).second != (*std_it_s).second)
	#endif
		{
			return false;
		}
		++ft_it_s;
		++std_it_s;
	}
#elif defined(STACK) || defined(QUEUE) || defined(PRIORITY_QUEUE)
	FT tmp_ft = ft;
	STD tmp_std = std;
	while (!tmp_ft.empty())
	{
	#if defined(STACK) || defined(PRIORITY_QUEUE)
		if (tmp_ft.top() != tmp_std.top())
	#elif defined(QUEUE)
		if (tmp_ft.front() != tmp_std.front())
	#endif
		{
			return false;
		}
		tmp_ft.pop();
		tmp_std.pop();
	}

#endif
	return true;
}