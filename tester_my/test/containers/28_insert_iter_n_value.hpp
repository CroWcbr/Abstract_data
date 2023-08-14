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

		int n_add = rand() % T_SIZE;
		int value = rand();

		typename FT::iterator ft_it = ft_test[i].begin();
		typename STD::iterator std_it = std_test[i].begin();

		ft::advance(ft_it, iter_pos);
		std::advance(std_it, iter_pos);

		ft_test[i].insert(ft_it, n_add, value);
		std_test[i].insert(std_it, n_add, value);
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

	int array_value[T_COUNT];
	fill_array_random(array_value, T_COUNT, 0, RAND_MAX);
	int array_n_add[T_COUNT];
	fill_array_random(array_n_add, T_COUNT, 0, T_SIZE);

	int array_iter_pos[T_COUNT];
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			array_iter_pos[i] = 0;
		else
			array_iter_pos[i] = rand() % ft_test[i].size();
	}

	if (!leaks)
	{
		typename STD::iterator	it;
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			it = std_test[i].begin();
			std::advance(it, array_iter_pos[i]);
			std_test[i].insert(it, array_n_add[i], array_value[i]);
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
		ft_test[i].insert(it, array_n_add[i], array_value[i]);
	}
	if (!leaks)
		end_ft = timer();
}
