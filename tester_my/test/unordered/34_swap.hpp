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
		int s1 = rand() % T_COUNT;
		int s2 = rand() % T_COUNT;

		ft::swap(ft_test[s1], ft_test[s2]);
		std::swap(std_test[s1], std_test[s2]);
		if (!check_equel_container(ft_test[s1], std_test[s1]))
		{
			return false;
		}

		ft_test[s1].swap(ft_test[s2]);
		std_test[s1].swap(std_test[s2]);
		if (!check_equel_container(ft_test[s1], std_test[s1]))
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
		return ;

	int	array_iter[T_COUNT];
	fill_array_random(array_iter, T_COUNT, 0, T_COUNT - 1);

	int	array_iter2[T_COUNT];
	fill_array_random(array_iter2, T_COUNT, 0, T_COUNT - 1);

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_test[array_iter[i]].swap(std_test[array_iter2[i]]);
			std::swap(std_test[array_iter[i]], std_test[array_iter2[i]]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[array_iter2[i]].swap(ft_test[array_iter2[i]]);
		ft::swap(ft_test[array_iter2[i]], ft_test[array_iter2[i]]);
	}
	if (!leaks)
		end_ft = timer();
}
