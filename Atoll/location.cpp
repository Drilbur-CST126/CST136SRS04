#include "stdafx.h"
#include "location.h"

GPS::Location::Location(const std::string name, const Latitude latitude, const Longitude longitude) :
name_ { name },
latitude_ { latitude },
longitude_ { longitude }
{
	
}

bool GPS::Location::operator<(const Location& location) const
{
	bool ret = false;
	if (sortDir == SortDir::kHorizontal)
	{
		ret = longitude_ < location.longitude_;
	}
	else if (sortDir == SortDir::kVertical)
	{
		ret = latitude_ < location.latitude_;
	}
	else
	{
		throw std::exception("Sorting direction not specified.");
	}
	return ret;
}

double GPS::Location::getDistance(const Location& dest) const noexcept
{
	static constexpr auto radius = 6371.0; // km
	const auto lat1 = latitude_.getRadians();
	const auto lat2 = dest.latitude_.getRadians();
	const auto lng1 = longitude_.getRadians();
	const auto lng2 = dest.longitude_.getRadians();

	// Equation broken into pieces for readability
	const auto latSin = std::sin((lat1 - lat2) / 2);
	const auto lngSin = std::sin((lng1 - lng2) / 2);
	const auto cos = std::cos(lat1) * std::cos(lat2);
	const auto sqrt = std::sqrt(latSin * latSin + cos * lngSin * lngSin);
	const auto d = 2 * radius * std::asin(sqrt);
	return d;
}

std::string GPS::Location::getName() const noexcept
{
	return name_;
}


GPS::Location::SortDir GPS::Location::sortDir;

void GPS::Location::setSortDir(const SortDir dir)
{
	sortDir = dir;
}
