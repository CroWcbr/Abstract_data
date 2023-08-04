#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT, class STD>
bool test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		int	size = rand() % T_SIZE;

#if defined(MAP) || defined(MULTIMAP)
		ft::pair<int,int>	ft_array_iter[T_COUNT];
		std::pair<int,int>	std_array_iter[T_COUNT];
		fill_array_random_pair(ft_array_iter, std_array_iter, size, 0, RAND_MAX);
		FT	ft_tmp(ft_array_iter, ft_array_iter + size);
		STD	std_tmp(std_array_iter, std_array_iter + size);
#else
		int	array_iter[size];
		fill_array_random(array_iter, size, 0, RAND_MAX);
		FT	ft_tmp(array_iter, array_iter + size);
		STD	std_tmp(array_iter, array_iter + size);
#endif

		if (!check_equel_container(ft_tmp, std_tmp))
		{
			return false;
		}
	}
	return true;
}

template<class FT, class STD>
void	test_time(bool leaks, time_t& start_ft, time_t& start_std, time_t& end_ft, time_t& end_std)
{
	int	array_size[T_COUNT];
	fill_array_random(array_size, T_COUNT, 0, T_SIZE);

#if defined(MAP) || defined(MULTIMAP)
	ft::pair<int,int>	ft_array_iter[T_COUNT];
	std::pair<int,int>	std_array_iter[T_COUNT];
	fill_array_random_pair(ft_array_iter, std_array_iter, T_SIZE, 0, RAND_MAX);
#else
	int	array_iter[T_SIZE];
	fill_array_random(array_iter, T_SIZE, 0, RAND_MAX);
#endif

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
#if defined(MAP) || defined(MULTIMAP)
			STD	tmp(std_array_iter, std_array_iter + array_size[i]);
#else
			STD tmp(array_iter, array_iter + array_size[i]);
#endif
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
#if defined(MAP) || defined(MULTIMAP)
		FT	tmp(ft_array_iter, ft_array_iter + array_size[i]);
#else
		FT tmp(array_iter, array_iter + array_size[i]);
#endif
	}
	if (!leaks)
		end_ft = timer();
}
