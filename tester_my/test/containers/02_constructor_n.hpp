#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT, class STD>
bool test_all()
{
	int	array_size[T_COUNT];
	fill_array_random(array_size, T_COUNT, 0, T_SIZE);

	for (int i = 0; i < T_COUNT; ++i)
	{
		FT	ft_tmp(array_size[i]);
		STD	std_tmp(array_size[i]);

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

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			STD tmp(array_size[i]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		FT tmp(array_size[i]);
	}
	if (!leaks)
		end_ft = timer();
}
