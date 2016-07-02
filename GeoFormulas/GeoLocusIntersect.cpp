/** \file GeoLocusIntersect.cpp
*   \brief
*/

/****************************************************************************/
/*  GeoLocusIntersect.cpp                                                   */
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
    int GeoLocusIntersect(const LLPoint &gStart, const LLPoint &gEnd, const Locus &loc, LLPoint &intersect,
                          double dTol, double dEps)
    {
        InverseResult result;
        DistVincenty(gStart, gEnd, result);
        const double gAz = result.azimuth;

        DistVincenty(loc.locusStart, loc.locusEnd, result);
        const double locStAz = result.azimuth;
        const double locLength = result.distance;

        double crs31, crs32, dist13, dist23;
        LLPoint pt1;
        if (!CrsIntersect(loc.locusStart, locStAz, crs31, dist13, gStart, gAz, crs32, dist23, dTol, pt1))
            return 0;

        DistVincenty(loc.geoStart, loc.geoEnd, result);

        const double tcrs = result.azimuth;
        double crsFromPt, distFromPt;
        LLPoint ptInt = PerpIntercept(loc.geoStart, tcrs, pt1, crsFromPt, distFromPt, dTol);

        double distLoc = DistToLocusP(loc, ptInt, dTol, dEps);

        double distarray[2];
        double errarray[2];
        errarray[1] = distFromPt - fabs(distLoc);
        distarray[1] = dist23;

        double distBase = dist23 - errarray[1] / cos(fabs(SignAzimuthDifference(crsFromPt, crs32)));

        int k = 0;
        const int maxCount = 10;
        while (!isnan(distBase) && fabs(errarray[1]) > dTol && k < maxCount)
        {
            pt1 = DestVincenty(gStart, gAz, distBase);
            errarray[0] = errarray[1];
            distarray[0] = distarray[1];
            distarray[1] = distBase;

            ptInt = PerpIntercept(loc.geoStart, tcrs, pt1, crsFromPt, distFromPt, dTol);
            distLoc = DistToLocusP(loc, ptInt, dTol, dEps);
            errarray[1] = distFromPt - fabs(distLoc);

            FindLinearRoot(distarray, errarray, distBase);
            k++;
        }
        intersect = pt1;

        DistVincenty(intersect, loc.locusStart, result);
        const double distLocStPt1 = result.distance;
        DistVincenty(intersect, loc.locusEnd, result);

        // found intersect point must be on or between locus
        // If 5e-3 is to tight a tolerance then try setting to 5e-2
        // For the 8260.54A Appendix test cases 1e-3 was to tight, 5e-3
        // works just fine.
        if (!IsNearZero(locLength - (distLocStPt1 + result.distance), 5e-3))
            return 0;
        return 1;
    }
}
