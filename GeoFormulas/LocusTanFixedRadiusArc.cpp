/** \file LocusTanFixedRadiusArc.cpp
*   \brief 
*/

/****************************************************************************/
/*  LocusTanFixedRadiusArc.cpp                                                  */
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
    int LocusTanFixedRadiusArc(const Locus & loc1, const Locus & loc2, double radius,
        int & dir, LLPoint & center, LLPoint & intersection1, LLPoint & intersection2,
        double dTol, double dEps)
    {
        InverseResult result;
        DistVincenty(loc1.locusStart, loc1.locusEnd, result);
        double crs12 = result.azimuth;

        DistVincenty(loc1.geoStart, loc1.geoEnd, result);
        double gcrs1 = result.azimuth;
        double geoLen1 = result.distance;

        DistVincenty(loc2.locusEnd, loc2.locusStart, result);
        double crs32 = result.azimuth + M_PI;

        int nVal = TangentFixedRadiusArc(loc1.locusStart, crs12, loc2.locusEnd, crs32, radius, dir, center, intersection1, intersection2, dTol);
        if(nVal == 0)
            return 0;

        DistVincenty(center, intersection1, result);
        double rcrs1 = result.azimuth;
        DistVincenty(center, intersection2, result);
        double rcrs2 = result.azimuth;

        double angle = fabs(SignAzimuthDifference(rcrs1, rcrs2));

        double vertexAngle = 2 * acos(sin(angle / 2.0) * cos(radius / kSphereRadius));

        double locAngle = atan((loc1.endDist - loc1.startDist) / geoLen1);

        double dCrsFromPt, dDistFromPt;
        LLPoint geoPt1 = PerpIntercept(loc1.geoStart, gcrs1, intersection1, dCrsFromPt, dDistFromPt, dTol);

        DistVincenty(loc1.geoStart, geoPt1, result);
        double distbase = result.distance;

        int k = 0;
        int maxCount = 15;
        double dErr = 0.0;
        double distarray[2];
        double errarray[2];
        distarray[0] = distarray[1] = errarray[0] = errarray[1] = 0.0;
        while(k == 0 || (!_isnan(distbase) && k < maxCount && fabs(dErr) > dTol))
        {
            if(k > 0)
            {
                geoPt1 = DestVincenty(loc1.geoStart, gcrs1, distbase);
            }
            intersection1 = PointOnLocusP(loc1, geoPt1, dTol, dEps);
            LLPoint geoPt;
            double dPerpCrs;
            double lcrs1 = LocusCrsAtPoint(loc1, intersection1, geoPt, dPerpCrs, 1e-8); //dTol);
            lcrs1 = lcrs1 - dir * M_PI_2;

            center = DestVincenty(intersection1, lcrs1, radius);

            if(!LocusPerpIntercept(loc2, center, dCrsFromPt, dDistFromPt, intersection2, dTol))
            {
                intersection2.Set(-HUGE_VAL, -HUGE_VAL);
            }

            DistVincenty(center, intersection2, result);
            double r2 = result.distance;

            dErr = r2 - radius;
            distarray[0] = distarray[1];
            distarray[1] = distbase;
            errarray[0] = errarray[1];
            errarray[1] = dErr;

            if(k == 0)
                distbase = distbase + dErr * (cos(locAngle) / sin(vertexAngle));
            else
                FindLinearRoot(distarray, errarray, distbase);
            k++;
        }
        return 1;
    }
}