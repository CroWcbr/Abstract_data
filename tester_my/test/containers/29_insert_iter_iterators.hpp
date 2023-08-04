#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

int max_num_del = 10;

template<class FT, class STD>
bool test_all()
{
	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return false;

	int array_iter[T_SIZE];
	fill_array_random(array_iter, T_SIZE, 0, RAND_MAX);

	for (int i = 0; i < T_COUNT; ++i)
	{
		int n_add = rand() % max_num_del;
		int iter_pos = rand() % (T_SIZE - n_add);

		int iter_insert_pos;
		if (ft_test[i].empty())
			iter_insert_pos = 0;
		else
			iter_insert_pos = rand() % ft_test[i].size();

		typename FT::iterator ft_it_tmp = ft_test[i].begin();
		typename STD::iterator std_it_tmp = std_test[i].begin();

		ft::advance(ft_it_tmp, iter_insert_pos);
		std::advance(std_it_tmp, iter_insert_pos);

		ft_test[i].insert(ft_it_tmp, array_iter + iter_pos, array_iter + iter_pos + n_add);
		std_test[i].insert(std_it_tmp,  array_iter + iter_pos, array_iter + iter_pos + n_add);
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

	int array_iter[T_SIZE];
	fill_array_random(array_iter, T_SIZE, 0, RAND_MAX);
	int array_n_add[T_COUNT];
	fill_array_random(array_n_add, T_COUNT, 0, max_num_del);
	int iter_pos[T_COUNT];
	fill_array_random(iter_pos, T_COUNT, 0, T_SIZE - max_num_del);

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
		typename STD::iterator std_it_tmp;
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_it_tmp = std_test[i].begin();
			std::advance(std_it_tmp, array_iter_pos[i]);
			std_test[i].insert(std_it_tmp, array_iter + iter_pos[i], array_iter + iter_pos[i] + array_n_add[i]);
		}
		end_std = timer();
	}

	typename FT::iterator ft_it_tmp;
	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_it_tmp = ft_test[i].begin();
		ft::advance(ft_it_tmp, array_iter_pos[i]);
		ft_test[i].insert(ft_it_tmp, array_iter + iter_pos[i], array_iter + iter_pos[i] + array_n_add[i]);
	}
	if (!leaks)
		end_ft = timer();
}
