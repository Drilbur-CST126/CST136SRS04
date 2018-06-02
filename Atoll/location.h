#pragma once
#include <string>
#include "latitude.h"
#include "longitude.h"

namespace GPS
{
	class Location
	{
	private:
		const std::string name_;
		const Latitude latitude_;
		const Longitude longitude_;

		//friend void swap(GPS::Location& a, GPS::Location& b) noexcept;

	public:
		enum class SortDir { kVertical, kHorizontal, kUnknown };

		Location(const std::string name, const Latitude latitude, const Longitude longitude);

		bool operator<(const Location&) const;

		double getDistance(const Location& dest) const noexcept;
		std::string getName() const noexcept;

		static void setSortDir(const SortDir dir);

		static constexpr std::size_t numIslands = 12;

	private:
		static SortDir sortDir;
	};
}