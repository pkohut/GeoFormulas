/**	\file PointOnLocusP.cpp
*	\brief 
*/

/****************************************************************************/
/*	PointOnLocusP.cpp													*/
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
	LLPoint _stdcall PointOnLocusP(const Locus & loc, const LLPoint & geoPt, double tol, double eps)
	{
		double distp = DistToLocusP(loc, geoPt, tol, eps);
		if(distp == 0)
			return geoPt;
		InverseResult result;
		DistVincenty(geoPt, loc.geoStart, result);
		double fcrs = result.azimuth;
		double tempcrs;
		if(distp > 0.0)
			tempcrs = fcrs - (M_PI / 2);
		else
			tempcrs = fcrs + (M_PI / 2);
		return DestVincenty(geoPt, tempcrs, fabs(distp));
	}
}