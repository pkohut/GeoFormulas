/** \file PointToArcTangents.cpp
*   \brief
*/

/****************************************************************************/
/*  PointToArcTangents.cpp                                                  */
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
    int PointToArcTangents(const LLPoint &point, const LLPoint &center, double radius,
                           LLPoint &tanPt1, LLPoint &tanPt2, double dTol)
    {
        InverseResult result;
        DistVincenty(point, center, result);
        const double crsFromCenter = result.reverseAzimuth;

        if (fabs(result.distance - radius) < dTol)
        {
            tanPt1 = point;
            return 1;
        }

        if (result.distance < radius)
        {
            return 0;
        }

        const double a = result.distance / kSphereRadius;
        const double b = radius / kSphereRadius;
        double c = acos(tan(b) / tan(a));

        int k = 0;
        const int maxCount = 15;
        double dErr = 0.0;
        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            tanPt1 = DestVincenty(center, crsFromCenter + c, radius);
            DistVincenty(tanPt1, center, result);
            const double radCrs = result.azimuth;

            DistVincenty(tanPt1, point, result);
            dErr = fabs(SignAzimuthDifference(radCrs, result.azimuth)) - M_PI_2;
            c = c + dErr;
            k++;
        }

        k = 0;
        dErr = 0.0;
        while (k == 0 || (fabs(dErr) > dTol && k < maxCount))
        {
            tanPt2 = DestVincenty(center, crsFromCenter - c, radius);
            DistVincenty(tanPt2, center, result);
            const double radCrs = result.azimuth;

            DistVincenty(tanPt2, point, result);
            dErr = fabs(SignAzimuthDifference(radCrs, result.azimuth)) - M_PI_2;
            c = c + dErr;
            k++;
        }

        return 1;
    }
}
