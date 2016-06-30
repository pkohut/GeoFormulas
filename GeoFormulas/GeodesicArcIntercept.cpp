/** \file GeodesicArcIntercept.cpp
*   \brief
*/

/****************************************************************************/
/*  GeodesicArcIntercept.cpp                                                */
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
    int GeodesicArcIntercept(const LLPoint &pt1, double crs1,
                             const LLPoint &center, double radius,
                             LLPoint &intPtC1, LLPoint &intPtC2, double dTol)
    {
        double dCrsFromPt, dDistFromPt;
        LLPoint perpPt = PerpIntercept(pt1, crs1, center, dCrsFromPt, dDistFromPt, dTol);

        InverseResult result;
        DistVincenty(perpPt, center, result);
        double perpDist = result.distance;

        if (perpDist > radius)
            return 0;

        if (fabs(perpDist - radius) < dTol)
        {
            intPtC1 = perpPt;
            return 1;
        }

        DistVincenty(perpPt, pt1, result);

        if (IsApprox(cos(perpDist / kSphereRadius), 0.0, 1e-8))
            return 0;

        double crs = result.azimuth;
        double dist = kSphereRadius * acos(cos(radius / kSphereRadius) / cos(perpDist / kSphereRadius));
        LLPoint pt = DestVincenty(perpPt, crs, dist);

        const int nIntersects = 2;
        for (int i = 0; i < nIntersects; i++)
        {
            DistVincenty(center, pt, result);
            double rcrs = result.reverseAzimuth;
            double dErr = radius - result.distance;

            double distarray[2], errarray[2];
            distarray[0] = dist;
            errarray[0] = dErr;

            DistVincenty(pt, perpPt, result);
            double bcrs = result.azimuth;

            DistVincenty(center, pt, result);
            double dAngle = fabs(SignAzimuthDifference(result.azimuth, result.reverseAzimuth));
            double B = fabs(SignAzimuthDifference(bcrs, rcrs) + M_PI - dAngle);
            double A = acos(sin(B) * cos(fabs(dErr) / kSphereRadius));
            double c;
            if (fabs(sin(A)) < dTol)
                c = dErr;
            else if (fabs(A) < dTol)
                c = dErr / cos(B);
            else
                c = kSphereRadius * asin(sin(dErr / kSphereRadius) / sin(A));

            if (dErr > 0)
                dist = dist + c;
            else
                dist = dist - c;

            pt = DestVincenty(perpPt, crs, dist);
            DistVincenty(center, pt, result);
            distarray[1] = dist;
            errarray[1] = radius - result.distance;

            while (fabs(dErr) > dTol)
            {
                FindLinearRoot(distarray, errarray, dist);
                if (isnan(dist))
                    break;

                pt = DestVincenty(perpPt, crs, dist);
                DistVincenty(center, pt, result);
                distarray[0] = distarray[1];
                errarray[0] = errarray[1];
                distarray[1] = dist;
                errarray[1] = radius - result.distance;
                break;
            }

            if (i == 0)
                intPtC1 = pt;
            else if (i == 1)
                intPtC2 = pt;
            else
                break;

            crs = crs + M_PI;
            pt = DestVincenty(perpPt, crs, dist);
            DistVincenty(center, pt, result);
            errarray[0] = radius - result.distance;
        }

        return nIntersects;
    }
}
