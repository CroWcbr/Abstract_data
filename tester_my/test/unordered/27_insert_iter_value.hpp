#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT, class STD>
bool test_all()
{
	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return false;

	for (int i = 0; i < T_COUNT; ++i)
	{
		int iter_pos;
		if (ft_test[i].empty())
			iter_pos = 0;
		else
			iter_pos = rand() % ft_test[i].size();

		typename FT::iterator ft_it = ft_test[i].begin();
		typename STD::iterator std_it = std_test[i].begin();

		ft::advance(ft_it, iter_pos);
		std::advance(std_it, iter_pos);

#if defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)
		int key = rand();
		int value = rand();
		ft::pair<int,int>	ft_value(key, value);
		std::pair<int,int>	std_value(key, value);
		ft_test[i].insert(ft_it, ft_value);
		std_test[i].insert(std_it, std_value);
#else
		int value = rand();
		ft_test[i].insert(ft_it, value);
		std_test[i].insert(std_it, value);
#endif

		if (!check_equel_container(ft_test[i], std_test[i]))
		{
			return false;
		}
	}
	return true;
}

template<class FT, class STD>
void	test_time(bool leaks, time_t& start_ft, time_t& start_std, time_t& end_ft, time_t& end_std)
{
	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return;

	int array_iter_pos[T_COUNT];
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			array_iter_pos[i] = 0;
		else
			array_iter_pos[i] = rand() % ft_test[i].size();
	}

#if defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)
	ft::pair<int,int>	ft_array_iter[T_COUNT];
	std::pair<int,int>	std_array_iter[T_COUNT];
	fill_array_random_pair(ft_array_iter, std_array_iter, T_COUNT, 0, RAND_MAX);
#else
	int array_value[T_COUNT];
	fill_array_random(array_value, T_COUNT, 0, RAND_MAX);
#endif

	if (!leaks)
	{
		typename STD::iterator	it;
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			it = std_test[i].begin();
			std::advance(it, array_iter_pos[i]);
#if defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)
			(std_test[i]).insert(it, std_array_iter[i]);
#else
			(std_test[i]).insert(it, array_value[i]);
#endif
		}
		end_std = timer();
	}

	typename FT::iterator	it;
	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		it = ft_test[i].begin();
		ft::advance(it, array_iter_pos[i]);
#if defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)
			(ft_test[i]).insert(it, ft_array_iter[i]);
#else
			(ft_test[i]).insert(it, array_value[i]);
#endif
	}
	if (!leaks)
		end_ft = timer();
}
