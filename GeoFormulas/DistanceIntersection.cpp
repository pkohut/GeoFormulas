/**	\file DistanceIntersection.cpp
*	\brief 
*/

/****************************************************************************/
/*	DistanceIntersection.cpp													*/
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
	int DistanceIntersection(const LLPoint & pt1, const double & dist13, const LLPoint & pt2, const double & dist23,
		LLPoint & intPtC1, LLPoint & intPtC2, const double & dTol)
	{
		InverseResult result;
		DistVincenty(pt1, pt2, result);
		double dist12 = result.distance;
		double crs12 = result.azimuth;

		if( (dist13 + dist23 - dist12 + dTol < 0) ||
			fabs(dist13 - dist23) > dist12)
			return 0;
		if(fabs(dist13 + dist23 - dist12) <= dTol)
		{
			intPtC1 = DestVincenty(pt1, crs12, dist13);
			return 1;
		}

		double a = dist23;
		double b = dist13;
		double c = dist12;

		double cosA_R = cos(a / SphereRadius);
		double cosB_R = cos(b / SphereRadius);
		double cosC_R = cos(c / SphereRadius);
		double sinB_R = sin(b / SphereRadius);
		double sinC_R = sin(c / SphereRadius);

		double A = acos( (cosA_R - cosB_R * cosC_R) / (sinB_R * sinC_R) );

		intPtC1 = DestVincenty(pt1, crs12 - A, dist13);
		intPtC2 = DestVincenty(pt1, crs12 + A, dist13);

		return 2;
	}
}