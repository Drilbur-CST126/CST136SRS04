#include "stdafx.h"
#include "longitude.h"
#include "latitude.h"

namespace GPS
{
	Longitude::Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second) :
	Angle<-180, 180>(degree, minute, second),
	cardinal_ { cardinal }
	{

	}

	bool Longitude::operator<(const Longitude& angle) const noexcept
	{
		auto ret = false;
		if (cardinal_ == Cardinal::E && angle.cardinal_ == Cardinal::W)
		{
			ret = true;
		}
		else if (cardinal_ == angle.cardinal_)
		{
			if (degree_ == angle.degree_)
			{
				if (minute_ == angle.minute_)
				{
					ret = second_ < angle.second_;
				}
				else
				{
					ret = minute_ < angle.minute_;
				}
			}
			else
			{
				ret = degree_ < angle.degree_;
			}

			if (cardinal_ == Cardinal::W)
			{
				ret = !ret;
			}
		}

		return ret;
	}
}
