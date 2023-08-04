#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

//can be different ft != std
template<class FT, class STD>
bool test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		int size = rand() % T_SIZE;
		int new_size = rand() % T_SIZE;
		int value = rand();
		int	array_iter[size];
		fill_array_random(array_iter, size, 0, RAND_MAX);

		FT	ft_tmp(array_iter, array_iter + size);
		STD	std_tmp(array_iter, array_iter + size);

		if (ft_tmp.capacity() != std_tmp.capacity())
		{
			return false;
		}

		ft_tmp.resize(new_size, value);
		std_tmp.resize(new_size, value);

		if (ft_tmp.capacity() != std_tmp.capacity())
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

	if (!leaks)
	{
		STD array_test_std[T_COUNT];
		fill_array_conteiner<STD>(array_test_std, T_COUNT, array_size, array_value);
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			array_test_std[i].capacity();
		}
		end_std = timer();
	}

	FT array_test_ft[T_COUNT];
	fill_array_conteiner<FT>(array_test_ft, T_COUNT, array_size, array_value);
	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		array_test_ft[i].capacity();
	}
	if (!leaks)
		end_ft = timer();
}
