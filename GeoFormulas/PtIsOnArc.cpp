/**	\file PtIsOnArc.cpp
*	\brief 
*/

/****************************************************************************/
/*	PtIsOnArc.cpp													*/
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
	bool PtIsOnArc( const LLPoint & llArcCenter, const double & dArcRadius,
		const double & dArcStartAzimuth, const double & dArcEndAzimuth, const int & nArcDirection,
		const LLPoint & llTestPt, int & bOnArc )

	{
		InverseResult invResult;
		if(!DistVincenty(llArcCenter, llTestPt, invResult))
			return false;
		double dDist = invResult.distance;
		double dCrs = invResult.azimuth;

		bOnArc = false;

		if(fabs(dDist - dArcRadius) > 0.5e-3) //Tol())
			bOnArc = false;
		else {
			double dArcExtent = GetArcExtent(dArcStartAzimuth, dArcEndAzimuth, nArcDirection, Tol());

			if(dArcExtent == M_2PI)
				bOnArc = true;
			else
			{
				double dSubExtent = GetArcExtent(dArcStartAzimuth, dCrs, nArcDirection, Tol());

				if(nArcDirection > 0) {
					if(dSubExtent <= dArcExtent)
						bOnArc = true;
				} else {
					if(dSubExtent >= dArcExtent)
						bOnArc = true;
				}
			}		
		}
		return true;
	}
}