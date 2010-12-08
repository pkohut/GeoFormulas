/**	\file ArcIntercept.cpp
*	\brief 
*/

/****************************************************************************/
/*	ArcIntercept.cpp													*/
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
	int _stdcall ArcIntercept(const LLPoint & center1, double radius1,
		const LLPoint & center2, double radius2,
		LLPoint & intPtC1, LLPoint & intPtC2, double dTol)
	{

		int nIntersects = DistanceIntersection(center1, radius1, center2, radius2, intPtC1, intPtC2, dTol);
		if(nIntersects == 0)
			return 0;


		for(int i = 0; i < nIntersects; i++)
		{
			LLPoint pt;
			if(i == 0)
				pt = intPtC1;
			else if(i == 1)
				pt = intPtC2;
			else
				break;

			int k = 0;
			InverseResult result;
			DistVincenty(center2, pt, result);
			double crs2x = result.azimuth;
			pt = DestVincenty(center2, crs2x, radius2);
			DistVincenty(center1, pt, result);
			double dist1x = result.distance;
			double crs1x = result.azimuth;
			double dErr = radius1 - dist1x;
			double errarray[2];
			double crsarray[2];
			errarray[1] = dErr;
			crsarray[1] = crs1x;
			while(k <= 10 && !_isnan(crs1x) && fabs(errarray[1]) > dTol)
			{
				pt = DestVincenty(center1, crs1x, radius1);
				DistVincenty(center2, pt, result);
				crs2x = result.azimuth;
				pt = DestVincenty(center2, crs2x, radius2);
				DistVincenty(center1, pt, result);
				dist1x = result.distance;
				crs1x = result.azimuth;
				crsarray[0] = crsarray[1];
				crsarray[1] = crs1x;
				errarray[0] = errarray[1];
				errarray[1] = radius1 - dist1x;
				FindLinearRoot(crsarray, errarray, crs1x);
				k++;
			}
			if(i == 0)
				intPtC1 = pt;
			else if(i== 1)
				intPtC2 = pt;
			else
				break;
		}

		return nIntersects;
	}
}