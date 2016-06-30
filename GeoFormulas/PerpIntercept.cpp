/** \file PerpIntercept.cpp
*   \brief 
*/

/****************************************************************************/
/*  PerpIntercept.cpp                                                   */
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
    LLPoint PerpIntercept(const LLPoint &llPt1, double dCrs13, const LLPoint &llPt2,
                          double &dCrsFromPt, double &dDistFromPt, double dTol)
    {
        InverseResult result;
        LLPoint pt1 = llPt1;
        LLPoint pt2 = llPt2;
        DistVincenty(pt1, pt2, result);

        double dist12 = result.distance;
        double crs12 = result.azimuth;
        double crs13 = dCrs13;

        double dAngle = fabs(SignAzimuthDifference(crs13, crs12));

        if (dist12 <= dTol)
        {
            // pt1, pt2 and projected pt3 are all the same;
            dCrsFromPt = dDistFromPt = 0.0;
            return pt1;
        }
        double dA = dist12 / kSphereRadius;
        double dist13 = kSphereRadius * atan(tan(dA) * fabs(cos(dAngle)));

        if (dAngle > M_PI_2)
        {
            LLPoint newPoint;
            newPoint = DestVincenty(pt1, crs13 + M_PI, dist13 + NmToMeters(150.0));
            dist13 = NmToMeters(150.0);
            DistVincenty(newPoint, pt1, result);

            crs13 = result.azimuth;
            pt1 = newPoint;
        }
        else if (fabs(dist13) < NmToMeters(150.0))
        {
            LLPoint newPoint;
            newPoint = DestVincenty(pt1, crs13 + M_PI, NmToMeters(150.0));
            dist13 = dist13 + NmToMeters(150.0);
            DistVincenty(newPoint, pt1, result);

            crs13 = result.azimuth;
            pt1 = newPoint;
        }

        LLPoint pt3 = DestVincenty(pt1, crs13, dist13);
        DistVincenty(pt3, pt1, result);
        double crs31 = result.azimuth;

        DistVincenty(pt3, pt2, result);
        double crs32 = result.azimuth;
        double dist23 = result.distance;

        dAngle = fabs(SignAzimuthDifference(crs31, crs32));

        double errarray[2];
        double distarray[2];
        errarray[0] = dAngle - M_PI;
        distarray[0] = dist13;
        distarray[1] = fabs(distarray[0] + errarray[0] * dist23);


        pt3 = DestVincenty(pt1, crs13, distarray[1]);
        DistVincenty(pt3, pt1, result);
        crs31 = result.azimuth;

        DistVincenty(pt3, pt2, result);
        crs32 = result.azimuth;

        errarray[1] = fabs(SignAzimuthDifference(crs31, crs32)) - M_PI_2;

        int k = 0;
        double dError = 0;

        while (k == 0 || ((dError > dTol) && (k < 15)))
        {
            double oldDist13 = dist13;
            FindLinearRoot(distarray, errarray, dist13);
            if (isnan(dist13))
                dist13 = oldDist13;
            pt3 = DestVincenty(pt1, crs13, dist13);

            DistVincenty(pt3, pt1, result);
            crs31 = result.azimuth;

            DistVincenty(pt3, pt2, result);
            dist23 = result.distance;
            crs32 = result.azimuth;

            distarray[0] = distarray[1];
            distarray[1] = dist13;
            errarray[0] = errarray[1];
            errarray[1] = fabs(SignAzimuthDifference(crs31, crs32)) - M_PI_2;
            dError = fabs(distarray[1] - distarray[0]);
            k++;
        }

        dCrsFromPt = crs32;
        dDistFromPt = dist23;
        return pt3;
    }
}
