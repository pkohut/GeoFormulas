/** \file PtIsOnLocus.cpp
*   \brief
*/

/****************************************************************************/
/*  PtIsOnLocus.cpp                                                         */
/****************************************************************************/
/*                                                                          */
/*  Copyright 2008 - 2016 Paul Kohut                                        */
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

    bool PtIsOnLocus(const Locus &loc, const LLPoint &testPt, double dTol)
    {
        LLPoint projPt;
        return PtIsOnLocus(loc, testPt, projPt, dTol);
    }

    bool PtIsOnLocus(const Locus &loc, const LLPoint &testPt, LLPoint &projPt, double dTol)
    {
        InverseResult result;
        if (!DistVincenty(loc.geoStart, loc.geoEnd, result))
            return false;

        double dCrsFromPt, dDistFromPt;
        projPt = PerpIntercept(loc.geoStart, result.azimuth, testPt, dCrsFromPt, dDistFromPt, dTol);

        PTISONGEODESIC_RESULT ptResult;
        if (!PtIsOnGeodesic(loc.geoStart, loc.geoEnd, projPt, 0, ptResult) || !ptResult.result)
            return false;

        // step 5 (page A2-28) says to use projPt, but that is in error
        DistVincenty(testPt, PointOnLocusP(loc, projPt, dTol, kEps), result);

        return result.distance < dTol;
    }
}
