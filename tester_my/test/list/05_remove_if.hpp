#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

struct IsGreaterThan
{
	int value;

	IsGreaterThan(int val)
	: value(val)
	{}

	bool operator()(int n) const
	{
		return n > value;
	}
};

template<class FT, class STD>
bool test_all()
{
	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return false;

	for (int i = 0; i < T_COUNT; ++i)
	{
		int value;
		if (ft_test[i].empty())
		{
			value = rand();
		}
		else
		{
			int pos = rand() % ft_test[i].size();
			typename FT::iterator it = ft_test[i].begin();
			ft::advance(it, pos);
			value = *it;
		}

		IsGreaterThan isGreaterThan(value);

		ft_test[i].remove_if(isGreaterThan);
		std_test[i].remove_if(isGreaterThan);

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

	int array_value[T_COUNT];
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
		{
			array_value[i] = rand();
		}
		else
		{
			int pos = rand() % ft_test[i].size();
			typename FT::iterator it = ft_test[i].begin();
			ft::advance(it, pos);
			array_value[i] = *it;
		}
	}
	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			IsGreaterThan isGreaterThan(array_value[i]);
			std_test[i].remove_if(isGreaterThan);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		IsGreaterThan isGreaterThan(array_value[i]);
		ft_test[i].remove_if(isGreaterThan);
	}
	if (!leaks)
		end_ft = timer();
}
