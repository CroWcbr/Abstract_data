#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT, class STD>
bool test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		int size = rand() % T_SIZE;
		int value = rand();
		int new_size = rand() % T_SIZE;

		FT	ft_tmp(size, value);
		STD	std_tmp(size, value);

		ft_tmp.reserve(new_size);
		std_tmp.reserve(new_size);

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
	int array_value[T_COUNT];
	fill_array_random(array_value, T_COUNT, 0, RAND_MAX);
	int	array_new_size[T_COUNT];
	fill_array_random(array_new_size, T_COUNT, 0, T_SIZE);

	if (!leaks)
	{
		STD array_test_std[T_COUNT];
		fill_array_conteiner<STD>(array_test_std, T_COUNT, array_size, array_value);
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			array_test_std[i].reserve(array_new_size[i]);
		}
		end_std = timer();
	}

	FT array_test_ft[T_COUNT];
	fill_array_conteiner<FT>(array_test_ft, T_COUNT, array_size, array_value);
	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		array_test_ft[i].reserve(array_new_size[i]);
	}
	if (!leaks)
		end_ft = timer();
}
