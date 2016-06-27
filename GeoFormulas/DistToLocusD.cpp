/**	\file DistToLocusD.cpp
*	\brief 
*/

/****************************************************************************/
/*	DistToLocusD.cpp													*/
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

using namespace std;

namespace GeoCalcs {
	/**
	*
	*/
	double DistToLocusD(const Locus & loc, double dDistance, double dEps)
	{
		InverseResult result;
		double distToLoc = 0.0;

		if(!DistVincenty(loc.geoStart, loc.geoEnd, result))
			distToLoc = numeric_limits<double>::signaling_NaN();
		double geoLen = result.distance;
		if(geoLen > 0.0)
		{
			distToLoc = loc.startDist + (dDistance / geoLen) * (loc.endDist - loc.startDist);
		}
		return distToLoc;
	}
}