#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

int max_num_add = 10;

template<class FT, class STD>
bool test_all()
{
	if (max_num_add > T_SIZE)
		max_num_add = T_SIZE - 1;

	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return false;

#if defined(MAP) || defined(MULTIMAP)
	ft::pair<int,int>	ft_array_iter[T_SIZE];
	std::pair<int,int>	std_array_iter[T_SIZE];
	fill_array_random_pair(ft_array_iter, std_array_iter, T_SIZE, 0, RAND_MAX);
#else
	int array_iter[T_SIZE];
	fill_array_random(array_iter, T_SIZE, 0, RAND_MAX);
#endif

	for (int i = 0; i < T_COUNT; ++i)
	{
		int n_add = rand() % max_num_add;
		int iter_pos = rand() % (T_SIZE - n_add);

#if defined(MAP) || defined(MULTIMAP)
	ft_test[i].insert(ft_array_iter + iter_pos, ft_array_iter + iter_pos + n_add);
	std_test[i].insert(std_array_iter + iter_pos, std_array_iter + iter_pos + n_add);
#else
	ft_test[i].insert(array_iter + iter_pos, array_iter + iter_pos + n_add);
	std_test[i].insert(array_iter + iter_pos, array_iter + iter_pos + n_add);
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
	if (max_num_add > T_SIZE)
		max_num_add = T_SIZE - 1;

	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return;

	int array_n_add[T_COUNT];
	fill_array_random(array_n_add, T_COUNT, 0, max_num_add);
	int array_iter_pos[T_COUNT];
	fill_array_random(array_iter_pos, T_COUNT, 0, T_SIZE - max_num_add);

#if defined(MAP) || defined(MULTIMAP)
	ft::pair<int,int>	ft_array_iter[T_SIZE];
	std::pair<int,int>	std_array_iter[T_SIZE];
	fill_array_random_pair(ft_array_iter, std_array_iter, T_SIZE, 0, RAND_MAX);
#else
	int array_iter[T_SIZE];
	fill_array_random(array_iter, T_SIZE, 0, RAND_MAX);
#endif

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
#if defined(MAP) || defined(MULTIMAP)
			std_test[i].insert(std_array_iter + array_iter_pos[i],  std_array_iter + array_iter_pos[i] + array_n_add[i]);
#else
			std_test[i].insert(array_iter + array_iter_pos[i], array_iter + array_iter_pos[i] + array_n_add[i]);
#endif
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
#if defined(MAP) || defined(MULTIMAP)
		ft_test[i].insert(ft_array_iter + array_iter_pos[i], ft_array_iter + array_iter_pos[i] + array_n_add[i]);
#else
		ft_test[i].insert(array_iter + array_iter_pos[i], array_iter + array_iter_pos[i] + array_n_add[i]);
#endif
	}
	if (!leaks)
		end_ft = timer();
}
