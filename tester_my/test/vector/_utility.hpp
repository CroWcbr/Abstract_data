#pragma once
#include "../../_config.hpp"
#include "../_test_config.hpp"

#include <vector>

template<class T>
bool	check_equel_vector(ft::vector<T> ft, std::vector<T> std)
{
	if (ft.size() != std.size())
	{
		return false;
	}
	for (size_t i = 0; i < ft.size(); ++i)
	{
		if (ft[i] != std[i])
		{
			std::cerr << i << "\t" << ft[i] << "\t" << std[i] << std::endl;
			return false;
		}
	}
	return true;
}
