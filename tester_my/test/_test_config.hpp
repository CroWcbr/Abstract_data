#pragma once

#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <string>
#include <cstring>
#include <cstdio>

static bool				g_leaks = false;
static std::string		g_result;
static std::string		g_leak;
volatile static time_t	g_start1;
volatile static time_t	g_start2;
volatile static time_t	g_end1;
volatile static time_t	g_end2;

const std::string	GREEN = "\x1B[1;32m";
const std::string	RED = "\x1B[1;31m";
const std::string	YELLOW = "\x1B[1;33m";
const std::string	WHITE = "\x1B[1;39m";
const std::string	RESET = "\033[0m";

void printElement(std::string t) {
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

std::string to_string(int value)
{
	char buffer[16];
	std::sprintf(buffer, "%d", value);
	return std::string(buffer);
}

void printTime()
{
	time_t t1 = ( g_end1 - g_start1 );
	time_t t2 = ( g_end2 - g_start2 );
	if (t1 >= t2)
	{
		printElement(GREEN + to_string(t2) + "ms" + RESET);
	}
	else
	{
		printElement(RED + to_string(t2) + "ms" + RESET);
	}
	if (t1 > t2)
	{
		printElement(RED + to_string(t1) + "ms" + RESET);
	}
	else
	{
		printElement(GREEN + to_string(t1) + "ms" + RESET);
	}

}

time_t timer()
{
	struct timeval start = {};
	gettimeofday(&start, NULL);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}
