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
		int n_add = rand() % T_SIZE;
		int n_add_end = rand() % T_SIZE;
		if (n_add > n_add_end)
			std::swap(n_add, n_add_end);

#if defined(MAP) || defined(MULTIMAP)
	ft_test[i].insert(ft_array_iter + n_add, ft_array_iter + n_add_end);
	std_test[i].insert(std_array_iter + n_add, std_array_iter + n_add_end);
#else
	ft_test[i].insert(array_iter + n_add, array_iter + n_add_end);
	std_test[i].insert(array_iter + n_add, array_iter + n_add_end);
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

	int array_n_add[T_COUNT];
	fill_array_random(array_n_add, T_COUNT, 0, T_SIZE);
	int array_n_add_end[T_COUNT];
	fill_array_random(array_n_add_end, T_COUNT, 0, T_SIZE);
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (array_n_add[i] > array_n_add_end[i])
			std::swap(array_n_add[i], array_n_add_end[i]);
	}


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
			std_test[i].insert(std_array_iter + array_n_add[i],  std_array_iter + array_n_add_end[i]);
#else
			std_test[i].insert(array_iter + array_n_add[i], array_iter + array_n_add_end[i]);
#endif
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
#if defined(MAP) || defined(MULTIMAP)
		ft_test[i].insert(ft_array_iter + array_n_add[i], ft_array_iter + array_n_add_end[i]);
#else
		ft_test[i].insert(array_iter + array_n_add[i], array_iter + array_n_add_end[i]);
#endif
	}
	if (!leaks)
		end_ft = timer();
}
