#pragma once
#include "range.h"

namespace GPS
{
	template<int min, int max>
	class Angle
	{
		static_assert(min < max);

	private:
		using base_degree_type = int;
		using base_minute_type = unsigned;
		using base_second_type = unsigned;

	protected:
		using degree_type = Range<base_degree_type, min, max>;
		using minute_type = Range<base_minute_type, 0, 60>;
		using second_type = Range<base_second_type, 0, 60>;

		const degree_type degree_;
		const minute_type minute_;
		const second_type second_;

		static constexpr double PI = 3.14159;

	public:
		/*Angle() = delete;
		Angle(const Angle&) = default;
		Angle(Angle&&) = default;
		Angle& operator=(const Angle&) = default;
		Angle& operator=(Angle&&) = default;*/
		virtual ~Angle() = default;

		Angle(const degree_type degree, const minute_type minute, const second_type second) noexcept : 
		degree_ { degree },
		minute_ { minute },
		second_ { second }
		{
		}

		double getRadians() const noexcept
		{
			const auto minutesInDegrees = minute_ / 60.0;
			const auto secondsInDegrees = second_ / 360.0;
			const auto radians = (degree_ + minutesInDegrees + secondsInDegrees) * PI / 180.0;
			return radians;
		}
	};
}