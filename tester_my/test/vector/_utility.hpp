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
		// std::cout << "\t\t" << i << "\t" << ft[i] << "\t" << std[i] << std::endl;
		if (ft[i] != std[i])
		{
			// std::cout << "\t\t\t" << (ft[i] != std[i]) << "\t" << ft[i] << "\t" << std[i] << std::endl;
			return false;
		}
	}
	// std::cout << "\t\t\treturn true;" << std::endl;
	return true;
}
