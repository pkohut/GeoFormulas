/** \file TangentFixedRadiusArc.cpp
*   \brief
*/

/****************************************************************************/
/*  TangentFixedRadiusArc.cpp                                               */
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
    int TangentFixedRadiusArc(const LLPoint &pt1, double crs12, const LLPoint &pt3,
                              double crs3, double radius, int &dir,
                              LLPoint &centerPt, LLPoint &tanPt1, LLPoint &tanPt2, double dTol)
    {
        LLPoint pt2;
        bool bVal = CrsIntersect(pt1, crs12, pt3, crs3 + M_PI, dTol, pt2);

        if (bVal == false)
            return 0;

        InverseResult result;
        DistVincenty(pt1, pt2, result);
        double dist12 = result.distance;

        DistVincenty(pt2, pt1, result);
        double crs21 = result.azimuth;

        DistVincenty(pt2, pt3, result);
        double crs23 = result.azimuth;

        double vertexAngle = SignAzimuthDifference(crs21, crs23);

        if (fabs(sin(vertexAngle)) < dTol)
            return 0;

        if (vertexAngle > 0.0)
            dir = -1;
        else
            dir = 1;

        double A = vertexAngle / 2.0;
        if (radius > fabs(kSphereRadius * A))
            return 0;

        double DTA = fabs(kSphereRadius * asin(tan(radius / kSphereRadius) / tan(A)));
        double distToStart = dist12 - DTA;
        int k = 0;
        double dErr = 0.0;
        LLPoint startPt, endPt;
        while (k == 0 || (fabs(dErr) > dTol && k <= 10))
        {
            distToStart = distToStart - dErr / fabs(sin(vertexAngle));
            startPt = DestVincenty(pt1, crs12, distToStart);
            DistVincenty(startPt, pt2, result);
            double perpCrs = result.azimuth;
            if (dir < 0)
                perpCrs = perpCrs + M_PI_2;
            else
                perpCrs = perpCrs - M_PI_2;
            centerPt = DestVincenty(startPt, perpCrs, radius);
            double dCrsFromPt, dDistFromPt;
            endPt = PerpIntercept(pt3, crs3 + M_PI, centerPt, dCrsFromPt, dDistFromPt, dTol);
            DistVincenty(centerPt, endPt, result);
            double perpDist = result.distance;
            dErr = radius - perpDist;
            k++;
        }
        tanPt1 = startPt;
        tanPt2 = endPt;

        DistVincenty(pt2, tanPt2, result);
        if (fabs(SignAzimuthDifference(result.azimuth, crs3)) > M_PI_2)
            return 0;

        return 1;
    }
}
