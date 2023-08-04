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
		if (ft_test[i].empty())
			continue;

		int element = rand() % ft_test[i].size();


#ifdef MAP
		typename FT::mapped_type	ft_ref = (ft_test[i])[element];
		typename STD::mapped_type	std_ref = (std_test[i])[element];
#else
		typename FT::reference	ft_ref = (ft_test[i])[element];
		typename STD::reference	std_ref = (std_test[i])[element];
#endif

		if (ft_ref != std_ref)
		{
			return false;
		}

#ifndef MAP
		typename FT::const_reference ft_const_ref = (ft_test[i])[element];
		typename STD::const_reference std_const_ref = (std_test[i])[element];

		if (ft_const_ref!= std_const_ref)
		{
			return false;
		}
#endif
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

	int	array_element[T_COUNT];
	for(int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			array_element[i] = -1;
		else
			array_element[i] = rand() % ft_test[i].size();
	}

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			if (array_element[i] == -1)
				continue;
			(std_test[i])[array_element[i]] = array_element[i];
#ifndef MAP
			typename STD::const_reference std_const_ref = (std_test[i])[array_element[i]];
#endif
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (array_element[i] == -1)
			continue;
		(ft_test[i])[array_element[i]] = array_element[i];
#ifndef MAP
		typename FT::const_reference std_const_ref = (std_test[i])[array_element[i]];
#endif
	}
	if (!leaks)
		end_ft = timer();
}
