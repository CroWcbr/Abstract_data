#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

int max_num_del = 10;

template<class FT, class STD>
bool test_all()
{
	FT	ft_test[T_COUNT];
	STD	std_test[T_COUNT];
	if (!fill_array_conteiner_from_file<FT, STD>(ft_test, std_test, T_COUNT))
		return false;

	typename FT::iterator ft_it;
	typename FT::iterator ft_it_end;
	typename STD::iterator std_it;
	typename STD::iterator std_it_end;
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			continue;

		int	iter_pos = rand() % ft_test[i].size();
		int n_erase = rand() % max_num_del;
		if (n_erase > ft_test[i].size() - iter_pos)
			n_erase = ft_test[i].size() - iter_pos;

		ft_it = ft_test[i].begin();
		std_it = std_test[i].begin();
		ft::advance(ft_it, iter_pos);
		std::advance(std_it, iter_pos);

		ft_it_end = ft_it;
		std_it_end = std_it;

		ft::advance(ft_it_end, n_erase);
		std::advance(std_it_end, n_erase);

		ft_test[i].erase(ft_it, ft_it_end);
		std_test[i].erase(std_it, std_it_end);

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
		return ;

	typename FT::iterator ft_it_array[T_COUNT];
	typename STD::iterator std_it_array[T_COUNT];
	typename FT::iterator ft_it_end_array[T_COUNT];
	typename STD::iterator std_it_end_array[T_COUNT];

	int	iter_pos;
	int n_erase;
	for (int i = 0; i < T_COUNT; ++i)
	{	
		if (ft_test[i].empty())
			continue;
		iter_pos = rand() % ft_test[i].size();
		n_erase = rand() % max_num_del;
		if (n_erase > ft_test[i].size() - iter_pos)
			n_erase = ft_test[i].size() - iter_pos;
		ft_it_array[i] = ft_test[i].begin();
		std_it_array[i] = std_test[i].begin();
		ft::advance(ft_it_array[i], iter_pos);
		std::advance(std_it_array[i], iter_pos);
		ft_it_end_array[i] = ft_it_array[i];
		std_it_end_array[i] = std_it_array[i];
		ft::advance(ft_it_end_array[i], n_erase);
		std::advance(std_it_end_array[i], n_erase);
	}

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			if (std_test[i].empty())
				continue;
			std_test[i].erase(std_it_array[i], std_it_end_array[i]);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		if (ft_test[i].empty())
			continue;
		ft_test[i].erase(ft_it_array[i], ft_it_end_array[i]);
	}
	if (!leaks)
		end_ft = timer();
}
