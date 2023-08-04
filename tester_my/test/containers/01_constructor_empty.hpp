#pragma once

#include "../_define.hpp"
#include "../_utils.hpp"

template<class FT, class STD>
bool test_all()
{
	for (int i = 0; i < T_COUNT; ++i)
	{
		FT	ft_tmp;
		STD	std_tmp;

		if (!check_equel_container(ft_tmp, std_tmp))
		{
			return false;
		}
	}
	return true;
}

template<class FT, class STD>
void	test_time(bool leaks, time_t& start_ft, time_t& start_std, time_t& end_ft, time_t& end_std)
{
	if (!leaks)
	{
		start_std = timer();
		for (int i = 0; i < T_COUNT; ++i)
		{
			STD tmp;
		}
		end_std = timer();
	}

	if (!leaks)
		start_ft = timer();
	for (int i = 0; i < T_COUNT; ++i)
	{
		FT tmp;
	}
	if (!leaks)
		end_ft = timer();
}
