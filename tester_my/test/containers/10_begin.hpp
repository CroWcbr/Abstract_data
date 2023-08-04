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
		if (std_test[i].empty())
			continue;

		typename FT::iterator ft_it = ft_test[i].begin();
		typename STD::iterator std_it = std_test[i].begin();

		if (*ft_it != *std_it)
			return false;

		typename FT::const_iterator ft_it_const = ft_test[i].begin();
		typename STD::const_iterator std_it_const = std_test[i].begin();

		if (*ft_it_const != *std_it_const)
			return false;
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

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			if (std_test[i].empty())
				continue;

			typename STD::iterator tmp_it = std_test[i].begin();
			typename STD::const_iterator tmp_it_const = std_test[i].begin();
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			continue;

		typename FT::iterator tmp_it = ft_test[i].begin();
		typename FT::const_iterator tmp_it_const = ft_test[i].begin();
	}
	if (!leaks)
		end_ft = timer();
}
