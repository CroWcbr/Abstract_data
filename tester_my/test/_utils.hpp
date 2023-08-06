#pragma once

#include "_define.hpp"
#include <cstdlib>
#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <sstream>

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

#if defined(MAP) || defined(MULTIMAP)
void	fill_array_random_pair(ft::pair<int,int> *ft_array, std::pair<int,int> *std_array, int size, int min, int max)
{
	for(int i = 0; i < size; ++i)
	{
		int key = rand() % (max - min + 1) + min;
		int value = rand() % (max - min + 1) + min;
		ft_array[i] = ft::pair<int, int>(key, value);
		std_array[i] = std::pair<int, int>(key, value);
	}
}
#endif

template<class CONT_FT, class CONT_STD>
bool	fill_array_conteiner_from_file(CONT_FT *ft_array, CONT_STD *std_array, int size)
{
	std::ifstream inputFile(_DATA_FILE);
	if (!inputFile)
	{
		std::cerr << "ERROR: " << (_DATA_FILE) << std::endl;
		return false;
	}

	std::string line;
	for (int i = 0; i < size; ++i)
	{
		std::getline(inputFile, line);
		std::stringstream  ss(line);
		int number;
		while (ss >> number)
		{
#if defined(VECTOR) || defined(LIST) || defined(DEQUE)
			ft_array[i].push_back(number);
			std_array[i].push_back(number);
#elif defined(SET) || defined(MULTISET) || defined(UNORDERED_SET)
			ft_array[i].insert(number);
			std_array[i].insert(number);
#elif defined(MAP) || defined(MULTIMAP)
			int value;
			ss >> value;
			ft_array[i].insert(ft::pair<int, int>(number, value));
			std_array[i].insert(std::pair<int, int>(number, value));
#endif
		}
	}

	inputFile.close();
	return true;
}

template<class FT, class STD>
bool	check_equel_container(FT ft, STD std)
{
	if (ft.size() != std.size())
	{
		return false;
	}
#if defined(VECTOR) || defined(LIST) || defined(SET) || defined(MULTISET) || defined(MAP) || defined(MULTIMAP) || defined(SET)
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
#elif defined(UNORDERED_SET)
	ft::set<int>	tmp(ft.begin(), ft.end());
	typename ft::set<int>::iterator	ft_it_s = tmp.begin();
	typename ft::set<int>::iterator	ft_it_e = tmp.end();
	typename STD::iterator	std_it_s = std.begin();
	typename STD::iterator	std_it_e = std.end();
	while (ft_it_s != ft_it_e)
	{
		if (*ft_it_s != *std_it_s)
		{		
			{
				return false;
			}
		}
		++ft_it_s;
		++std_it_s;
	}

#endif
	return true;
}
