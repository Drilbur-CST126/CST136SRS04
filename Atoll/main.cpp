// Atoll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <vector>
#include <forward_list>
#include <map>
#include <algorithm>
#include <functional>
#include "gsl.h"
#include "distancefunctor.h"


double testMap(const std::array<GPS::Location const, GPS::Location::numIslands> islands) noexcept
{
	auto ret = 0.0;
	std::map<const GPS::Location, std::string> islandMap{};
	for (auto island : islands)
	{
		islandMap[island] = island.getName();
	}

	const DistanceFunctor functor{ ret };
	std::for_each(islandMap.begin(), islandMap.end(), functor);
	//ret = functor.getDistance();
	return ret;
}

int main()
{
	const std::array<const GPS::Location, GPS::Location::numIslands> islands
	{
		GPS::Location{ "Faichuk Islands", GPS::Latitude{ GPS::Latitude::Cardinal::N, 7, 21, 8 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 151, 36, 30 } },
		GPS::Location{ "Hawaii", GPS::Latitude{ GPS::Latitude::Cardinal::N, 21, 18, 41 }, GPS::Longitude{ GPS::Longitude::Cardinal::W, 157, 47, 47 } },
		GPS::Location{ "Mariana Islands", GPS::Latitude{ GPS::Latitude::Cardinal::N, 17, 0, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 146, 0, 0 } },
		GPS::Location{ "Johnston Atoll", GPS::Latitude{ GPS::Latitude::Cardinal::N, 16, 44, 13 }, GPS::Longitude{ GPS::Longitude::Cardinal::W, 169, 31, 26 } },
		GPS::Location{ "Kosrae", GPS::Latitude{ GPS::Latitude::Cardinal::N, 5, 19, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 162, 59, 0 } },
		GPS::Location{ "Falalop", GPS::Latitude{ GPS::Latitude::Cardinal::N, 10, 1, 14 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 139, 47, 23 } },
		GPS::Location{ "Guam", GPS::Latitude{ GPS::Latitude::Cardinal::N, 13, 30, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 144, 48, 0 } },
		GPS::Location{ "Pohnpei", GPS::Latitude{ GPS::Latitude::Cardinal::N, 6, 51, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 158, 13, 0 } },
		GPS::Location{ "Marshall Islands", GPS::Latitude{ GPS::Latitude::Cardinal::N, 7, 7, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 171, 4, 0 } },
		GPS::Location{ "Yap", GPS::Latitude{ GPS::Latitude::Cardinal::N, 9, 32, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 138, 7, 0 } },
		GPS::Location{ "Wake Island", GPS::Latitude{ GPS::Latitude::Cardinal::N, 19, 17, 43 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 166, 37, 52 } },
		GPS::Location{ "New Zealand", GPS::Latitude{ GPS::Latitude::Cardinal::S, 41, 17, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 174, 27,  0 } },
	};
	GPS::Location::setSortDir(GPS::Location::SortDir::kUnknown);

	auto vectorLngDist = 0.0;
	auto vectorLatDist = 0.0;
	{ // vector test
		std::vector<std::reference_wrapper<const GPS::Location>> islandVector { islands.begin(), islands.end() };

		GPS::Location::setSortDir(GPS::Location::SortDir::kHorizontal);
		std::sort(islandVector.begin(), islandVector.end(), std::less<GPS::Location>{});

		const DistanceFunctor lng{ vectorLngDist };
		std::for_each(islandVector.begin(), islandVector.end(), lng);

		GPS::Location::setSortDir(GPS::Location::SortDir::kVertical);
		std::sort(islandVector.begin(), islandVector.end(), std::less<GPS::Location>{});

		const DistanceFunctor lat{ vectorLatDist };
		std::for_each(islandVector.begin(), islandVector.end(), lat);
	}

	auto forwardListLngDist = 0.0;
	auto forwardListLatDist = 0.0;
	{ // forward_list test
		std::forward_list<std::reference_wrapper<const GPS::Location>> islandForwardList{};
		//islandVector.reserve(12);
		std::copy(islands.begin(), islands.end(), std::front_inserter(islandForwardList));

		GPS::Location::setSortDir(GPS::Location::SortDir::kHorizontal);
		islandForwardList.sort(std::less<GPS::Location>{});

		const DistanceFunctor lng{ forwardListLngDist };
		std::for_each(islandForwardList.begin(), islandForwardList.end(), lng);

		GPS::Location::setSortDir(GPS::Location::SortDir::kVertical);
		islandForwardList.sort(std::less<GPS::Location>{});

		const DistanceFunctor lat{ forwardListLatDist };
		std::for_each(islandForwardList.begin(), islandForwardList.end(), lat);
	}

	auto mapLngDist = 0.0;
	auto mapLatDist = 0.0;
	{ // Map test
		GPS::Location::setSortDir(GPS::Location::SortDir::kHorizontal);
		mapLngDist = testMap(islands);

		GPS::Location::setSortDir(GPS::Location::SortDir::kVertical);
		mapLatDist = testMap(islands);
	}

	Ensures(abs(vectorLatDist - forwardListLatDist) < 0.000001);
	Ensures(abs(vectorLatDist - mapLatDist) < 0.000001);
	Ensures(abs(vectorLngDist - forwardListLngDist) < 0.000001);
	Ensures(abs(vectorLngDist - mapLngDist) < 0.000001);

    return 0;
}

