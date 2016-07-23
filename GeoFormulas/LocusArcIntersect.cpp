/** \file LocusArcIntersect.cpp
*   \brief
*/

/****************************************************************************/
/*  LocusArcIntersect.cpp                                                   */
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

    int AdjustIntersects(int nIntersects, const Locus &locus, LLPoint &intPt1, LLPoint &intPt2);

    int LocusArcIntersect(const Locus &locus, const LLPoint &arcCenter, double arcRadius,
                          LLPoint &intersection1, LLPoint &intersection2, double dTol,
                          double dEps)
    {
        int nIntersections = 0;

        InverseResult result;
        DistVincenty(locus.locusStart, locus.locusEnd, result);

        LLPoint intPt1, intPt2;

        const int nIntersects = AdjustIntersects(GeodesicArcIntercept(locus.locusStart, result.azimuth,
                                                                      arcCenter, arcRadius, intPt1, intPt2,
                                                                      dTol),
                                                 locus, intPt1, intPt2);

        if (nIntersects == 0)
            return 0;

        DistVincenty(locus.geoStart, locus.geoEnd, result);
        const double gcrs = result.azimuth;

        for (int i = 0; i < nIntersects; i++)
        {
            LLPoint intPt = i == 0 ? intPt1 : intPt2;
            double dCrsFromPt, dDistFromPt;
            LLPoint perpPt = PerpIntercept(locus.geoStart, gcrs, intPt, dCrsFromPt, dDistFromPt, dTol);

            DistVincenty(perpPt, locus.geoStart, result);
            const double distbase = result.distance;

            LLPoint locPt = PointOnLocusP(locus, perpPt, dTol, dEps);

            DistVincenty(locPt, arcCenter, result);

            double errarray[2], distarray[2];
            errarray[1] = result.distance - arcRadius;

            if (fabs(errarray[1]) >= dTol)
            {
                distarray[1] = distbase;
                const int maxCount = 15;
                double newDistbase = 1.001 * distbase;
                int k = 0;
                while (k < maxCount && !std::isnan(newDistbase) && fabs(errarray[1]) > dTol)
                {
                    locPt = PointOnLocusP(locus, DestVincenty(locus.geoStart, gcrs, newDistbase),
                                          dTol, dEps);
                    DistVincenty(locPt, arcCenter, result);

                    distarray[0] = distarray[1];
                    distarray[1] = newDistbase;
                    errarray[0] = errarray[1];
                    errarray[1] = result.distance - arcRadius;

                    FindLinearRoot(distarray, errarray, newDistbase);
                    k++;
                }
            }

            if (PtIsOnLocus(locus, locPt, 1e-6)) //dTol))
            {
                if (i == 0)
                    intPt1 = locPt;
                else if (i == 1)
                    intPt2 = locPt;
                nIntersections++;
            }
        }
        intersection1 = intPt1;
        intersection2 = intPt2;
        DistVincenty(intersection1, intersection2, result);
        if (nIntersects == 2 && IsNearZero(result.distance, 0.5e-8))
        {
            nIntersections = 1;
        }

        return nIntersections;
    }


    // Returns max of 2 intersects, intPt1 and intPt2 may be modified.
    int AdjustIntersects(int nIntersects, const Locus &locus, LLPoint &intPt1, LLPoint &intPt2)
    {
        switch (nIntersects)
        {
            case 0:
                return 0;
            case 1:
            {
                PtIsOnGeodesicResult ptResult1, ptResult2;
                const bool bVal1 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt1, 0, ptResult1);
                const bool bVal2 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt2, 0, ptResult2);
                if (bVal1 && bVal2)
                {
                    if (!ptResult1.result)
                    {
                        intPt1 = intPt2;
                    }
                }
                else if (bVal2 && ptResult2.result)
                {
                    intPt1 = intPt2;
                }
                else if (bVal1 && !ptResult1.result)
                {
                    nIntersects--;
                }
                break;
            }
            case 2:
            {
                PtIsOnGeodesicResult ptResult1, ptResult2;
                const bool bVal1 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt1, 0, ptResult1);
                const bool bVal2 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt2, 0, ptResult2);
                if (!bVal1 && !bVal2)
                    nIntersects = 0;
                else if (bVal1 && !bVal2)
                {
                    nIntersects = 1;
                    if (!ptResult1.result)
                        nIntersects = 0;
                }
                else if (!bVal1) // && bVal2)
                {
                    nIntersects = 1;
                    if (!ptResult2.result)
                        nIntersects = 0;
                    else
                    {
                        intPt1 = intPt2;
                    }
                }
                else
                {
                    if (!ptResult1.result && ptResult2.result)
                    {
                        nIntersects = 1;
                        intPt1 = intPt2;
                    }
                    else if (ptResult1.result && !ptResult2.result)
                    {
                        nIntersects = 1;
                    }
                }
                break;
            }
            default:
                break;
        }
        return nIntersects;
    }
}
