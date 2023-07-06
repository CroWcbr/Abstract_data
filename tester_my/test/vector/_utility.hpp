#pragma once
#include "../../_config.hpp"
#include "../_test_config.hpp"

#include <vector>

template<class T>
bool check_equel_vector(ft::vector<T> ft, std::vector<T> std)
{
	if (ft.size() != std.size())
	{
		return false;
	}
	for (size_t i = 0; i < ft.size(); ++i)
	{
		if (ft[i] != std[i])
		{
			return false;
		}
	}
	return true;
}
