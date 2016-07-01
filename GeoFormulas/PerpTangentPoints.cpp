/** \file PerpTangentPoints.cpp
*   \brief
*/

/****************************************************************************/
/*  PerpTangentPoints.cpp                                                   */
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
    void PerpTangentPoints(const LLPoint &lineStart, double crs,
                           const LLPoint &center, double radius,
                           LLPoint *linePts, LLPoint *tanPts, double dTol)
    {
        InverseResult result;
        DistVincenty(lineStart, center, result);
        const double signAngle1 = SignAzimuthDifference(crs, result.azimuth) >= 0.0 ? 1.0 : -1.0;

        if (fabs(result.distance * (result.azimuth - crs)) < dTol)
        {
            tanPts[0] = DestVincenty(lineStart, crs, result.distance - radius);
            tanPts[1] = DestVincenty(lineStart, crs, result.distance + radius);
            linePts[0] = tanPts[0];
            linePts[1] = tanPts[1];
            return;
        }

        double dCrsFromPt, dDistFromPt;
        LLPoint perpPt = PerpIntercept(lineStart, crs, center, dCrsFromPt, dDistFromPt, dTol);

        DistVincenty(perpPt, lineStart, result);
        const double crs21 = result.azimuth;

        double delta = radius;
        const int maxCount = 15;
        double dErr = 0.0;
        int k = 0;
        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            linePts[0] = DestVincenty(perpPt, crs21 + M_PI, delta);
            DistVincenty(linePts[0], perpPt, result);

            tanPts[0] = PerpIntercept(linePts[0], result.azimuth - signAngle1 * M_PI_2,
                                      center, dCrsFromPt, dDistFromPt, dTol);
            dErr = dDistFromPt - radius;
            delta = delta - dErr;
            k++;
        }

        dErr = 0.0;
        k = 0;
        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            linePts[1] = DestVincenty(perpPt, crs21, delta);
            DistVincenty(linePts[1], perpPt, result);

            tanPts[1] = PerpIntercept(linePts[1], result.azimuth - signAngle1 * M_PI_2,
                                      center, dCrsFromPt, dDistFromPt, dTol);
            dErr = dDistFromPt - radius;
            delta = delta - dErr;
            k++;
        }

        return;
    }
}
