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

	FT	ft_test_splice[T_COUNT];
	STD	std_test_splice[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test_splice, std_test_splice, T_COUNT))
		return false;

	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[i].merge(ft_test_splice[T_COUNT - i - 1], std::greater<typename FT::value_type>());
		std_test[i].merge(std_test_splice[T_COUNT - i - 1], std::greater<typename STD::value_type>());

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

	FT	ft_test_splice[T_COUNT];
	STD	std_test_splice[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test_splice, std_test_splice, T_COUNT))
		return;

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_test[i].merge(std_test_splice[T_COUNT - i - 1], std::greater<typename STD::value_type>());
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[i].merge(ft_test_splice[T_COUNT - i - 1], std::greater<typename FT::value_type>());
	}
	if (!leaks)
		end_ft = timer();
}
