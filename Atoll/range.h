#pragma once
#include <sstream>
#include <exception>

template<typename T, T min, T max>
class Range // You should re-code and simplify your SRS01 RangeInt
{
private:
	using value_type = T;

	value_type value_ { max };

public:
	// Explicitly not explicit; makes managing the Range far easier than having to consistantly call setValue()
	Range(const value_type value) // Initialize to unusable value in case value is out of bounds
	{
		setValue(value);
	}

private:

	static void checkValue(value_type value)
	{
		if(value < min)
		{
			std::ostringstream stream;
			stream << "The value was too small: (" << value << " < " << min << ")";
			throw std::exception(stream.str().c_str());
		}

		if(value >= max)
		{
			std::ostringstream stream;
			stream << "The value was too large: (" << value << " >= " << max << ")";
			throw std::exception(stream.str().c_str());
		}
	}

public:

	value_type getValue() const noexcept
	{
		return value_;
	}

	void setValue(value_type value)
	{
		checkValue(value);
		value_ = value;
	}

	operator value_type() const noexcept
	{
		return value_;
	}
};