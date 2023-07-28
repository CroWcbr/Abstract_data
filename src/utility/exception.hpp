#pragma once

namespace ft
{
	class exception
	{
	private:
		const char* message;
	public:
		explicit exception(const char* msg) : message(msg) {}
		const char* what() const throw() { return message; }
	};
}
