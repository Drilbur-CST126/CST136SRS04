#pragma once
#include "location.h"

class DistanceFunctor
{
private:
	double& distance_;
	const GPS::Location* previous_{ nullptr };

public:
	DistanceFunctor(double& distance) noexcept;

	void operator() (const GPS::Location& location) noexcept;
	void operator() (const std::pair<const GPS::Location, std::string>& pair) noexcept;
};