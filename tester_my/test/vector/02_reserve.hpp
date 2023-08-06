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

		ft_test[i].reserve(new_size);
		std_test[i].reserve(new_size);

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

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			ft_test[i].reserve(array_new_size[i]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		std_test[i].reserve(array_new_size[i]);
	}
	if (!leaks)
		end_ft = timer();
}
