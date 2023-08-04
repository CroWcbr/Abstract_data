#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT, class STD>
bool test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		int	size = rand() % T_SIZE;
		int	array_iter[size];
		fill_array_random(array_iter, size, 0, RAND_MAX);

		FT	ft_tmp;
		STD	std_tmp;

		ft_tmp.assign(array_iter, array_iter + size);
		std_tmp.assign(array_iter, array_iter + size);

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
	int	array_iter[T_SIZE];
	fill_array_random(array_iter, T_SIZE, 0, RAND_MAX);

	if (!leaks)
	{
		STD tmp;
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			tmp.assign(array_iter, array_iter + array_size[i]);
		}
		end_std = timer();
	}

	FT tmp;
	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		tmp.assign(array_iter, array_iter + array_size[i]);
	}
	if (!leaks)
		end_ft = timer();
}
