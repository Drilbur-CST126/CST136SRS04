#pragma once
#include <exception>
#include <sstream>
#include "range.h"

template <typename T, T min, T max>
class ValueException : public std::exception
{
private:

	Range<T, min, max> range_;

public:

	ValueException(const char* what, Range<T, min, max> range) :
	std::exception(what),
	range_ { range }
	{
		
	}

	const char* what() const override
	{
		std::ostringstream stream;
		stream << std::exception::what() << "(Value was " << range_ << ", bounds were [" << min << ", " << max << ")";
		return stream.str().c_str();
	}
};