/**	\file LocusIntersect.cpp
*	\brief 
*/

/****************************************************************************/
/*	LocusIntersect.cpp													*/
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
	int _stdcall LocusIntersect(const Locus & loc1, const Locus & loc2, LLPoint & intersect,
		double dTol, double dEps)
	{
		InverseResult result;
		DistVincenty(loc1.locusStart, loc1.locusEnd, result);
		double crs1 = result.azimuth;

		DistVincenty(loc2.locusStart, loc2.locusEnd, result);
		double crs2 = result.azimuth;

		LLPoint p1;
		if(!CrsIntersect(loc1.locusStart, crs1, loc2.locusStart, crs2, dTol, p1))
			return 0;

		DistVincenty(loc1.geoStart, loc1.geoEnd, result);
		double tcrs1 = result.azimuth;

		DistVincenty(loc2.geoStart, loc2.geoEnd, result);
		double tcrs2 = result.azimuth;

		double dCrsFromPt, dDistFromP;
		LLPoint pint1 = PerpIntercept(loc1.geoStart, tcrs1, p1, dCrsFromPt, dDistFromP, dTol);
		PtIsOnGeodesicResult ptResult;
		bool bVal = PtIsOnGeodesic(loc1.geoStart, loc1.geoEnd, pint1, 0, ptResult);
		if(!bVal)
			return 0;
		if(!ptResult.result)
			return 0;

		DistVincenty(loc1.geoStart, pint1, result);
		double distbase = result.distance;

		int k = 0;
		int maxCount = 15;
		double dErr = 0.0;
		LLPoint ploc1;
		LLPoint ploc2;
		double distarray[2];
		double errarray[2];
		distarray[0] = distarray[1] = errarray[0] = errarray[1] = 0.0;

		while( (k == 0) || (k < maxCount && fabs(dErr) > dTol))
		{
			if(k > 0)
				pint1 = DestVincenty(loc1.geoStart, tcrs1, distbase);
			ploc1 = PointOnLocusP(loc1, pint1, dTol, dEps);
			LLPoint pint2 = PerpIntercept(loc2.geoStart, tcrs2, ploc1, dCrsFromPt, dDistFromP, dTol);

			ploc2 = PointOnLocusP(loc2, pint2, dTol, dEps);
			DistVincenty(ploc1, ploc2, result);
			dErr = result.distance;

			errarray[0] = errarray[1];
			errarray[1] = dErr;
			distarray[0] = distarray[1];
			distarray[1] = distbase;
			if(k == 0)
			{
				pint1 = PerpIntercept(loc1.geoStart, tcrs1, ploc2, dCrsFromPt, dDistFromP, dTol);
				DistVincenty(loc1.geoStart, pint1, result);
				distbase = result.distance;
			} else {
				FindLinearRoot(distarray, errarray, distbase);
			}
			k++;
		}

		LLPoint projPt;
		bVal = PtIsOnLocus(loc1, ploc1, projPt, 1e-6);
		if(!bVal)
			return 0;
		bVal = PtIsOnLocus(loc2, ploc2, projPt, 1e-6);
		if(!bVal)
			return 0;
		intersect = ploc1;


		return 1;
	}
}