/** \file DiscretizedArcLength.cpp
*   \brief
*/

/****************************************************************************/
/*  DiscretizedArcLength.cpp                                                */
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

    double DiscretizedArcLength(const LLPoint &center, double dRadius,
                                double dStartCrs, double dEndCrs,
                                int nOrient, int nSegments, double dTol)
    {
        nSegments = clamp(nSegments, 1, 128);

        double dError = 0.0;
        double dArcLength = 0.0;
        double dOldArcLength = 0.0;
        const double dSubtendedAngle = GetArcExtent(dStartCrs, dEndCrs, nOrient, dTol);

        // with k equal to 0 then there will only be nSegments subsegments calculated.
        // need to figure out how to make this flexible based on the value in dRadius.
        // Bigger radius need more segments than 16 and smaller segments need less.
        // For now 16 is enough to pass the 8260.54A test case.
        int k = 0;
        while (k == 0 || ((dError > kTol) && (k <= 0)))
        {
            double dTheta = dSubtendedAngle / nSegments;
            const double dAltitude = 0.0;
            dArcLength = 0.0;

            for (int i = 0; i < nSegments; i++)
            {
                double theta = dStartCrs + i * dTheta;
                LLPoint p1 = DestVincenty(center, theta, dRadius);
                LLPoint p2 = DestVincenty(center, theta + 0.5 * dTheta, dRadius);
                LLPoint p3 = DestVincenty(center, theta + dTheta, dRadius);

                VMath::Vector3 v1 = ECEF(p1, dAltitude);
                VMath::Vector3 v2 = ECEF(p2, dAltitude);
                VMath::Vector3 v3 = ECEF(p3, dAltitude);
                VMath::Vector3 vChord1 = v2 - v1;
                VMath::Vector3 vChord2 = v2 - v3;
                double x1 = VMath::Vector3::Length(vChord1); //v2 - v1);
                double x2 = VMath::Vector3::Length(vChord2); //v2 - v3);
                double d = VMath::Vector3::Dot(vChord1, vChord2);

                if (IsNearZero(x1, kTol) && IsNearZero(x2, kTol) && IsNearZero(d, kTol))
                {
                    dArcLength = 0.0;
                    break;
                }

                double xi = d / (x1 * x2);
                double _x1_x2Sq = x1 / x2 - xi;
                double sigma = sqrt(1.0 - (xi * xi));
                double R = (x2 * sqrt((_x1_x2Sq * _x1_x2Sq) + (sigma * sigma))) / (2.0 * sigma);
                double A = 2 * (M_PI - acos(xi));
                double L = R * A;
                dArcLength += L;
            }
            nSegments = 2 * nSegments;
            dError = fabs(dArcLength - dOldArcLength);
            dOldArcLength = dArcLength;
            k++;
        }
        return dArcLength;
    }
}
