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
		int elem;
		if (ft_test[i].empty())
			elem = rand();
		else
		{
			int pos = rand() % ft_test[i].size();
			typename STD::iterator it = std_test[i].begin();
			std::advance(it, pos);
#if defined(MAP) || defined(MULTIMAP)
			elem = it->first;
#else
			elem = *it;
#endif
		}

		typename FT::size_type ft_count = ft_test[i].count(elem);
		typename STD::size_type std_count = std_test[i].count(elem);

		if (ft_count != std_count)
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

	int array_elem[T_COUNT];
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			array_elem[i] = rand();
		else
		{
			int pos = rand() % ft_test[i].size();
			typename STD::iterator it = std_test[i].begin();
			std::advance(it, pos);
#if defined(MAP) || defined(MULTIMAP)
			array_elem[i]  = it->first;
#else
			array_elem[i]  = *it;
#endif
		}
	}

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_test[i].count(array_elem[i]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[i].count(array_elem[i]);
	}
	if (!leaks)
		end_ft = timer();
}
