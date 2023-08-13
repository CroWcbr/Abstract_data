#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

struct CompareMod
{
	int mod;

	CompareMod(int m) : mod(m) {}

	bool operator()(int x, int y) const
	{
		return (x % mod) == (y % mod);
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
		if (ft_test[i].size() < 2)
			continue;
		int mod = rand() % 10 + 5;

		CompareMod compareMod(mod);

		ft_test[i].unique(compareMod);
		std_test[i].unique(compareMod);

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

	int array_mod[T_COUNT];
	fill_array_random(array_mod, T_COUNT, 5, 15);

	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			CompareMod compareMod(array_mod[i]);
			std_test[i].unique(compareMod);
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		CompareMod compareMod(array_mod[i]);
		ft_test[i].unique(compareMod);
	}
	if (!leaks)
		end_ft = timer();
}
