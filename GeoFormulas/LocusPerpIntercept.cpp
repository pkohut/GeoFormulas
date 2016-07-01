/** \file LocusPerpIntercept.cpp
*   \brief
*/

/****************************************************************************/
/*  LocusPerpIntercept.cpp                                                  */
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
    int LocusPerpIntercept(const Locus &loc, const LLPoint &pt2, double &crsFromPt,
                           double &distFromPt, LLPoint &intPt, double dTol)
    {
        InverseResult result;
        DistVincenty(loc.geoStart, loc.geoEnd, result);
        double gcrs = result.azimuth;
        double gdist = result.distance;

        if (fabs(loc.startDist - loc.endDist) < dTol)
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
        LLPoint geoPt = PerpIntercept(loc.geoStart, gcrs, locPt, crsFromPt, distFromPt, dTol);
        double locAngle = atan((loc.startDist - loc.endDist) / gdist);

        double distarray[2], errarray[2];
        distarray[0] = distarray[1] = errarray[0] = errarray[1] = 0.0;

        DistVincenty(loc.geoStart, geoPt, result);
        distarray[1] = result.distance;

        int k = 0;
        int maxCount = 15;
        double newDist = 0.0;
        while (k == 0 || (!isnan(newDist) && fabs(errarray[1]) > dTol && k < maxCount))
        {
            geoPt = DestVincenty(loc.geoStart, gcrs, distarray[1]);
            locPt = PointOnLocusP(loc /*loc.geoStart*/, geoPt, dTol, kEps);
            lcrs = LocusCrsAtPoint(loc, locPt, geoPt, 1e-8);

            DistVincenty(locPt, pt2, result);

            errarray[1] = -result.distance * cos(fabs(SignAzimuthDifference(lcrs, result.azimuth)));
            if (fabs(errarray[1]) < dTol)
            {
                distFromPt = result.distance;
                crsFromPt = result.reverseAzimuth;
                intPt = locPt;
                break;
            }

            if (k == 0)
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
