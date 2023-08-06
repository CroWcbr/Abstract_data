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
		int	size;
		if (ft_test[i].empty())
			size = 0;
		else
			size = rand() % ft_test[i].size();

		typename FT::iterator ft_it_tmp = ft_test[i].begin();
		typename STD::iterator std_it_tmp = std_test[i].begin();
		ft::advance(ft_it_tmp, size);
		std::advance(std_it_tmp, size);

		ft_test[i].splice(ft_it_tmp, ft_test_splice[i]);
		std_test[i].splice(std_it_tmp, std_test_splice[i]);

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

	int array_iter_pos[T_COUNT];
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			array_iter_pos[i] = 0;
		else
			array_iter_pos[i] = rand() % ft_test[i].size();
	}

	if (!leaks)
	{
		start_std = timer();
		typename STD::iterator std_it_tmp;
		for (int i = 0; i < T_COUNT; ++i)
		{
			std_it_tmp = std_test[i].begin();
			std::advance(std_it_tmp, array_iter_pos[i]);
			std_test[i].splice(std_it_tmp, std_test_splice[i]);
		}
		end_std = timer();
	}

	typename FT::iterator ft_it_tmp;
	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_it_tmp = ft_test[i].begin();
		ft::advance(ft_it_tmp, array_iter_pos[i]);
		ft_test[i].splice(ft_it_tmp, ft_test_splice[i]);
	}
	if (!leaks)
		end_ft = timer();
}
