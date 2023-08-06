#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT_IT, class STD_IT>
static bool	operator!=(const FT_IT ft_it_s, const STD_IT std_it_s)
{
	return (ft_it_s.first != std_it_s.first || ft_it_s.second != std_it_s.second);
}

template<class FT, class STD>
bool test_all()
{
	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return false;

	for (int i = 0; i < T_COUNT; ++i)
	{
		int elem = rand() % T_SIZE;

		typename FT::iterator ft_it = ft_test[i].lower_bound(elem);
		typename STD::iterator std_it = std_test[i].lower_bound(elem);

		if (ft_it == ft_test[i].end() && std_it == std_test[i].end())
			continue;

		if (*ft_it != *std_it)
		{
			return false;
		}

		typename FT::const_iterator ft_it_const = ft_test[i].lower_bound(elem);
		typename STD::const_iterator std_it_const = std_test[i].lower_bound(elem);

		if (*ft_it_const != *std_it_const)
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

	int array_elem[T_COUNT];
	fill_array_random(array_elem, T_COUNT, 0, T_SIZE);

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_test[i].lower_bound(array_elem[i]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[i].lower_bound(array_elem[i]);
	}
	if (!leaks)
		end_ft = timer();
}
