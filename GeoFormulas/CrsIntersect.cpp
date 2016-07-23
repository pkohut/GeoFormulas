/** \file CrsIntersect.cpp
*   \brief
*/

/****************************************************************************/
/*  CrsIntersect.cpp                                                        */
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
    bool CrsIntersect(const LLPoint &llPt1, double az13,
                      const LLPoint &llPt2, double az23, double dTol, LLPoint &llIntersect)
    {
        double az31, dist13, az32, dist23;
        az31 = az32 = 0.0;
        dist13 = dist23 = 0.0;
        return CrsIntersect(llPt1, az13, az31, dist13,
                            llPt2, az23, az32, dist23,
                            dTol, llIntersect);

    }


    /**
    *
    */
    bool CrsIntersect(const LLPoint &llPt1, double az13,
                      double &az31, double &dist13, const LLPoint &llPt2, double az23,
                      double &az32, double &dist23, double dTol, LLPoint &llIntersect)
    {
        LLPoint pt1 = llPt1;
        LLPoint pt2 = llPt2;

        InverseResult result;
        DistVincenty(pt1, pt2, result);

        double angle1 = fabs(SignAzimuthDifference(az13, result.azimuth));
        double angle2 = fabs(SignAzimuthDifference(result.reverseAzimuth, az23));
        if (angle1 < 0.0 && angle2 < 0.0)
        {
            angle1 = -angle1;
            angle2 = -angle2;
        }

        if (sin(angle1) == 0.0 && sin(angle2) == 0.0)
            return false;

        // step 7
        // locate approx intersection of point3 using spherical earth model. Section 3.2

        const double cosA = cos(angle1);
        const double sinA = sin(angle1);
        const double cosB = cos(angle2);
        const double sinB = sin(angle2);

        const double C = acos(-cosA * cosB + sinA * sinB * cos(result.distance / kSphereRadius));
        const double cosC = cos(C);
        const double sinC = sin(C);
        const double a = kSphereRadius * acos((cosA + cosB * cosC) / (sinB * sinC));
        const double b = kSphereRadius * acos((cosB + cosA * cosC) / (sinA * sinC));

        if (std::isnan(a) || std::isnan(b))
            return false;

        llIntersect = DestVincenty(pt1, az13, b);
        DistVincenty(pt1, llIntersect, result);
        dist13 = result.distance;

        LLPoint llInv = llIntersect;
        llInv.latitude = -llInv.latitude;
        llInv.longitude = llInv.longitude + M_PI - M_2PI;
        DistVincenty(pt1, llInv, result);

        if (dist13 > result.distance)
        {
            llIntersect = llInv;
            dist13 = result.distance;
            az31 = result.reverseAzimuth;
            az13 = az13 + M_PI;
            az23 = az23 + M_PI;
        }

        DistVincenty(pt2, llIntersect, result);
        dist23 = result.distance;

        if (dist13 < NmToMeters(1))
        {
            pt1 = DestVincenty(pt1, az13 + M_PI, NmToMeters(1.0));
            DistVincenty(pt1, llIntersect, result);
            az13 = result.azimuth;
        }
        if (dist23 < NmToMeters(1))
        {
            pt2 = DestVincenty(pt2, az23 + M_PI, NmToMeters(1.0));
            DistVincenty(pt2, llIntersect, result);
            az23 = result.azimuth;
        }

        bool bSwapped = false;
        if (dist23 < dist13)
        {
            std::swap(pt1, pt2);
            std::swap(az13, az23);
            dist13 = dist23;
            bSwapped = true;
        }

        double distarray[2], errarray[2];
        distarray[0] = dist13;
        distarray[1] = 1.01 * dist13;

        llIntersect = DestVincenty(pt1, az13, dist13);
        DistVincenty(pt2, llIntersect, result);
        errarray[0] = SignAzimuthDifference(result.azimuth, az23);

        llIntersect = DestVincenty(pt1, az13, distarray[1]);
        DistVincenty(pt2, llIntersect, result);
        errarray[1] = SignAzimuthDifference(result.azimuth, az23);

        const int nMaxCount = 15;
        double dErr = 0.0;
        int k = 0;
        while (k == 0 || ((dErr > dTol) && (k <= nMaxCount)))
        {
            FindLinearRoot(distarray, errarray, dist13);
            if (std::isnan(dist13))
                break;

            LLPoint newPt = DestVincenty(pt1, az13, dist13);
            DistVincenty(pt2, newPt, result);
            errarray[0] = errarray[1];
            errarray[1] = SignAzimuthDifference(result.azimuth, az23);
            distarray[0] = distarray[1];
            distarray[1] = dist13;

            DistVincenty(newPt, llIntersect, result);
            dErr = result.distance;
            llIntersect = newPt;
            k++;
        }

        // display if k == maxinteratorcount (10) and show error message
        // because results might not have converged.
        if (k > nMaxCount && dErr > 1e-8)
            return false;

        if (bSwapped)
        {
            std::swap(pt1, pt2);
            std::swap(az13, az23);
            dist13 = dist23;
        }
        DistVincenty(llIntersect, pt1, result);
        az31 = result.azimuth;
        dist13 = result.distance;

        DistVincenty(llIntersect, pt2, result);
        az32 = result.azimuth;
        dist23 = result.distance;

        return true;
    }
}
