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
        double distStartToCenter = result.distance;
        double crsStartToCenter = result.azimuth;
        //        double crsCenterToStart = result.reverseAzimuth;

        double angle1 = SignAzimuthDifference(crs, crsStartToCenter);

        if (fabs(distStartToCenter * (crsStartToCenter - crs)) < dTol)
        {
            tanPts[0] = DestVincenty(lineStart, crs, distStartToCenter - radius);
            tanPts[1] = DestVincenty(lineStart, crs, distStartToCenter + radius);
            linePts[0] = tanPts[0];
            linePts[1] = tanPts[1];
            return;
        }

        double dCrsFromPt, dDistFromPt;
        LLPoint perpPt = PerpIntercept(lineStart, crs, center, dCrsFromPt, dDistFromPt, dTol);

        DistVincenty(perpPt, lineStart, result);
        //        double dist12 = result.distance;
        double crs21 = result.azimuth;

        double delta = radius;

        int k = 0;
        int maxCount = 15;
        double dErr = 0.0;
        double signAngle1 = angle1 >= 0.0 ? 1.0 : -1.0;

        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            linePts[0] = DestVincenty(perpPt, crs21 + M_PI, delta);
            DistVincenty(linePts[0], perpPt, result);
            double strCrs = result.azimuth;


            double perpCrs = strCrs - signAngle1 * M_PI_2;

            tanPts[0] = PerpIntercept(linePts[0], perpCrs, center, dCrsFromPt, dDistFromPt, dTol);
            double radDist = dDistFromPt;

            dErr = radDist - radius;

            delta = delta - dErr;
            k++;
        }

        dErr = 0.0;
        k = 0;
        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            linePts[1] = DestVincenty(perpPt, crs21, delta);
            DistVincenty(linePts[1], perpPt, result);
            double strCrs = result.azimuth;


            double perpCrs = strCrs - signAngle1 * M_PI_2;

            tanPts[1] = PerpIntercept(linePts[1], perpCrs, center, dCrsFromPt, dDistFromPt, dTol);
            double radDist = dDistFromPt;

            dErr = radDist - radius;

            delta = delta - dErr;
            k++;
        }


        return;
    }
}
