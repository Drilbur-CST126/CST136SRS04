#include "stdafx.h"
#include "distancefunctor.h"

DistanceFunctor::DistanceFunctor(double& distance) noexcept :
	distance_{ distance }
{

}

void DistanceFunctor::operator() (const GPS::Location& location) noexcept
{
	if (previous_ != nullptr)
	{
		distance_ += location.getDistance(*previous_);
	}
	previous_ = &location;
}

void DistanceFunctor::operator()(const std::pair<const GPS::Location, std::string>& pair) noexcept
{
	const auto& location{ pair.first };
	if (previous_ != nullptr)
	{
		distance_ += location.getDistance(*previous_);
	}
	previous_ = &location;
}