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
		if (ft_test[i].empty())
			continue;

		int element = rand() % ft_test[i].size();

		typename FT::reference ft_ref = ft_test[i].at(element);
		typename STD::reference std_ref = std_test[i].at(element);

		if (ft_ref!= std_ref)
		{
			return false;
		}

		typename FT::const_reference ft_const_ref = ft_test[i].at(element);
		typename STD::const_reference std_const_ref = std_test[i].at(element);

		if (ft_const_ref!= std_const_ref)
		{
			return false;
		}

		int element_incorrect = T_SIZE + element;
		try
		{
			std_test[i].at(element_incorrect);
			return false;
		}
		catch(const std::exception& e)
		{
			try
			{
				ft_test[i].at(element_incorrect);
				return false;
			}
			catch(const ft::exception& e)
			{
				;
			}
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
			std_test[i].at(array_element[i]) = array_element[i];
			typename STD::const_reference std_const_ref = std_test[i].at(array_element[i]);
			(void)std_const_ref;
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (array_element[i] == -1)
			continue;
		ft_test[i].at(array_element[i]) = array_element[i];
		typename FT::const_reference ft_const_ref = ft_test[i].at(array_element[i]);
		(void)ft_const_ref;
	}
	if (!leaks)
		end_ft = timer();
}
