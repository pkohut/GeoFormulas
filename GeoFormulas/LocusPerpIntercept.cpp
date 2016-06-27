/**	\file LocusPerpIntercept.cpp
*	\brief 
*/

/****************************************************************************/
/*	LocusPerpIntercept.cpp													*/
/****************************************************************************/
/*                                                                          */
/*  Copyright 2008 - 2010 Paul Kohut                                        */
/*  Licensed under the Apache License, Version 2.0 (the "License"); you may */
/*  not use this file except in compliance with the License. You may obtain */
/*  a copy of the License at                                                */
/*                                                                          */
/*  http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or         */
/*  implied. See the License for the specific language governing            */
/*  permissions and limitations under the License.                          */
/*                                                                          */
/****************************************************************************/

#include "Conversions.h"
#include "GeoFormulas.h"


namespace GeoCalcs {
	/**
	*
	*/
	int LocusPerpIntercept(const Locus & loc, const LLPoint & pt2, double & crsFromPt,
		double & distFromPt, LLPoint & intPt, double dTol)
	{
		InverseResult result;
		DistVincenty(loc.geoStart, loc.geoEnd, result);
		double gcrs = result.azimuth;
		double gdist = result.distance;

		if(fabs(loc.startDist - loc.endDist) < dTol)
		{		
			LLPoint geoPt = PerpIntercept(loc.geoStart, gcrs, pt2, crsFromPt, distFromPt, dTol);
			intPt = PointOnLocusP(loc, geoPt, dTol, kEps);
			DistVincenty(pt2, intPt, result);
			distFromPt = result.distance;
			crsFromPt = result.azimuth;
			return 1;
		}

		DistVincenty(loc.locusStart, loc.locusEnd, result);
		double lcrs = result.azimuth;

		LLPoint locPt = PerpIntercept(loc.locusStart, lcrs, pt2, crsFromPt, distFromPt, dTol);

		double locAngle = atan((loc.startDist - loc.endDist) / gdist);

		LLPoint geoPt = PerpIntercept(loc.geoStart, gcrs, locPt, crsFromPt, distFromPt, dTol);

		double distarray[2];
		double errarray[2];
		distarray[0] = distarray[1] = errarray[0] = errarray[1] = 0.0;

		DistVincenty(loc.geoStart, geoPt, result);
		distarray[1] = result.distance;

		int k = 0;
		int maxCount = 15;
		while(k == 0 || (fabs(errarray[1]) > dTol && k < maxCount))
		{
			geoPt = DestVincenty(loc.geoStart, gcrs, distarray[1]);
			locPt = PointOnLocusP(loc /*loc.geoStart*/, geoPt, dTol, kEps);

			double dPerpCrs;
			lcrs = LocusCrsAtPoint(loc, locPt, geoPt, dPerpCrs, 1e-8);
			DistVincenty(locPt, pt2, result);

			double crsToPt = result.azimuth;
			double distToPt = result.distance;

			double angle = fabs(SignAzimuthDifference(lcrs, crsToPt));
			errarray[1] = -distToPt * cos(angle);
			if(fabs(errarray[1]) < dTol)
			{
				distFromPt = distToPt;
				crsFromPt = result.reverseAzimuth;
				intPt = locPt;
				break;
			}

			double newDist;
			if(k == 0)
				newDist = distarray[1] + errarray[1] * cos(locAngle);
			else
				FindLinearRoot(distarray, errarray, newDist);
			distarray[0] = distarray[1];
			distarray[1] = newDist;
			errarray[0] = errarray[1];
			k++;
		}

		intPt = locPt;
		DistVincenty(pt2, intPt, result);
		distFromPt = result.distance;
		crsFromPt = result.azimuth;
		return 1;
	}
}