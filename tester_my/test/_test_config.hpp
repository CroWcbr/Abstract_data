#pragma once

#include "_define.hpp"
#include <cstring>
#include <iostream>

#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int			delta_time = 10;
const std::string	GREEN = "\x1B[1;32m";
const std::string	RED = "\x1B[1;31m";
const std::string	YELLOW = "\x1B[1;33m";
const std::string	WHITE = "\x1B[1;39m";
const std::string	RESET = "\033[0m";

void	printElement(std::string t) {
	if (t == "OK")
	{
		t = GREEN + t + RESET;
	}
	else if (t == "FAILED")
	{
		t = RED + t + RESET;
	}
	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
}

std::string	time_to_string(int value)
{
	char buffer[16];
	std::sprintf(buffer, "%d", value);
	return std::string(buffer);
}

void	printTime(time_t& start_ft, time_t& start_std, time_t& end_ft, time_t& end_std)
{
	time_t t_ft = (end_ft - start_ft);
	time_t t_std = (end_std - start_std);
	if (t_std + delta_time >= t_ft)
	{
		printElement(GREEN + time_to_string(t_ft) + "ms" + RESET);
	}
	else
	{
		printElement(RED + time_to_string(t_ft) + "ms" + RESET);
	}
	if (t_std - delta_time > t_ft)
	{
		printElement(RED + time_to_string(t_std) + "ms" + RESET);
	}
	else
	{
		printElement(GREEN + time_to_string(t_std) + "ms" + RESET);
	}

}
