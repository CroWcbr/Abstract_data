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
		int new_size = rand() % T_SIZE;
		int value = rand();

		ft_test[i].resize(new_size, value);
		std_test[i].resize(new_size, value);

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

	int	array_new_size[T_COUNT];
	fill_array_random(array_new_size, T_COUNT, 0, T_SIZE);
	int array_new_value[T_COUNT];
	fill_array_random(array_new_value, T_COUNT, 0, RAND_MAX);

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_test[i].resize(array_new_size[i], array_new_value[i]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[i].resize(array_new_size[i], array_new_value[i]);
	}
	if (!leaks)
		end_ft = timer();
}
