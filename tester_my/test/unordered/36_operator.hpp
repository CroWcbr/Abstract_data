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

		if ((ft_test[s1] == ft_test[s2]) != (std_test[s1] == std_test[s2]))
		{
			return false;
		}
		if ((ft_test[s1] != ft_test[s2]) != (std_test[s1] != std_test[s2]))
		{
			return false;
		}
#if defined(UNORDERED_SET) || defined(UNORDERED_MULTISET) || defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)

#else
		if ((ft_test[s1] < ft_test[s2]) != (std_test[s1] < std_test[s2]))
		{
			return false;
		}
		if ((ft_test[s1] > ft_test[s2]) != (std_test[s1] > std_test[s2]))
		{
			return false;
		}
		if ((ft_test[s1] >= ft_test[s2]) != (std_test[s1] >= std_test[s2]))
		{
			return false;
		}
		if ((ft_test[s1] <= ft_test[s2]) != (std_test[s1] <= std_test[s2]))
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
			std_test[array_iter[i]] == std_test[array_iter2[i]];
			std_test[array_iter[i]] != std_test[array_iter2[i]];
#if defined(UNORDERED_SET) || defined(UNORDERED_MULTISET) || defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)

#else
			std_test[array_iter[i]] < std_test[array_iter2[i]];
			std_test[array_iter[i]] > std_test[array_iter2[i]];
			std_test[array_iter[i]] >= std_test[array_iter2[i]];
			std_test[array_iter[i]] <= std_test[array_iter2[i]];
#endif
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		ft_test[array_iter[i]] == ft_test[array_iter2[i]];
		ft_test[array_iter[i]] != ft_test[array_iter2[i]];
#if defined(UNORDERED_SET) || defined(UNORDERED_MULTISET) || defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)

#else
		ft_test[array_iter[i]] < ft_test[array_iter2[i]];
		ft_test[array_iter[i]] > ft_test[array_iter2[i]];
		ft_test[array_iter[i]] >= ft_test[array_iter2[i]];
		ft_test[array_iter[i]] <= ft_test[array_iter2[i]];
#endif
	}
	if (!leaks)
		end_ft = timer();
}
