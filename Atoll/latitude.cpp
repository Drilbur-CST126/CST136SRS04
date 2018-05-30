#include "stdafx.h"
#include "latitude.h"

namespace GPS
{
	Latitude::Latitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second) :
	Angle<-89, 90>(degree, minute, second),
	cardinal_ { cardinal }
	{
	
	}

	bool Latitude::operator<(const Latitude& angle) const noexcept
	{
		auto ret = false;
		if (cardinal_ == Cardinal::S && angle.cardinal_ == Cardinal::N)
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

			if (cardinal_ == Cardinal::S)
			{
				ret = !ret;
			}
		}
		
		return ret;
	}
}