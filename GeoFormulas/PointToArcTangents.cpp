/** \file PointToArcTangents.cpp
*   \brief 
*/

/****************************************************************************/
/*  PointToArcTangents.cpp                                                  */
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
    int PointToArcTangents(const LLPoint &point, const LLPoint &center, double radius,
                           LLPoint &tanPt1, LLPoint &tanPt2, double dTol)
    {
        InverseResult result;
        DistVincenty(point, center, result);
        //        double crsToCenter = result.azimuth;
        double crsFromCenter = result.reverseAzimuth;
        double distToCenter = result.distance;

        if (fabs(distToCenter - radius) < dTol)
        {
            tanPt1 = point;
            return 1;
        }

        if (distToCenter < radius)
        {
            return 0;
        }

        double a = distToCenter / kSphereRadius;
        double b = radius / kSphereRadius;
        double c = acos(tan(b) / tan(a));
        //        double orgC = c;
        int k = 0;
        int maxCount = 15;
        double dErr = 0.0;
        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            tanPt1 = DestVincenty(center, crsFromCenter + c, radius);
            DistVincenty(tanPt1, center, result);
            double radCrs = result.azimuth;

            DistVincenty(tanPt1, point, result);
            double tanCrs = result.azimuth;
            double diff = SignAzimuthDifference(radCrs, tanCrs);
            dErr = fabs(diff) - M_PI_2;
            c = c + dErr;
            k++;
        }

        k = 0;
        dErr = 0.0;

        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            tanPt2 = DestVincenty(center, crsFromCenter - c, radius);
            DistVincenty(tanPt2, center, result);
            double radCrs = result.azimuth;

            DistVincenty(tanPt2, point, result);
            double tanCrs = result.azimuth;
            double diff = SignAzimuthDifference(radCrs, tanCrs);
            dErr = fabs(diff) - M_PI_2;
            c = c + dErr;
            k++;
        }


        return 1;
    }
}
