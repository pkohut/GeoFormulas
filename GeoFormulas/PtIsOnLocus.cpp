/**	\file PtIsOnLocus.cpp
*	\brief 
*/

/****************************************************************************/
/*	PtIsOnLocus.cpp													*/
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
	bool PtIsOnLocus(const Locus & loc, const LLPoint & testPt, LLPoint & projPt, const double & dTol)
	{
		InverseResult result;
		if(!DistVincenty(loc.geoStart, loc.geoEnd, result))
			return false;
		double fcrs = result.azimuth;

		double dCrsFromPt, dDistFromPt;

		projPt = PerpIntercept(loc.geoStart, fcrs, testPt, dCrsFromPt, dDistFromPt, dTol);

		PTISONGEODESIC_RESULT ptResult;
		if(!PtIsOnGeodesic(loc.geoStart, loc.geoEnd, projPt, 0, ptResult))
			return false;
		if(!ptResult.result)
			return false;
		LLPoint compPt = PointOnLocusP(loc, projPt, dTol, Eps());

		// step 5 (page A2-28) says to use projPt, but that is in error
		DistVincenty(testPt, compPt, result);
		if(result.distance < dTol)
			return true;
		return false;
	}
}