/** \file LocusArcIntersect.cpp
*   \brief 
*/

/****************************************************************************/
/*  LocusArcIntersect.cpp                                                   */
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
    int LocusArcIntersect(const Locus & locus, const LLPoint & arcCenter, double arcRadius,
        LLPoint & intersection1, LLPoint & intersection2, double dTol,
        double dEps)
    {
        int nIntersections = 0;

        InverseResult result;
        DistVincenty(locus.locusStart, locus.locusEnd, result);
        double fcrs = result.azimuth;

        LLPoint intPt1, intPt2;
        PtIsOnGeodesicResult ptResult1, ptResult2;

        int n1 = GeodesicArcIntercept(locus.locusStart, fcrs, arcCenter, arcRadius, intPt1, intPt2, dTol);

        if(n1 == 0)
            return 0;
        else if(n1 == 1) {      
            bool bVal1 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt1, 0, ptResult1);
            bool bVal2 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt2, 0, ptResult2);
            if(bVal1 && bVal2) {
                if(!ptResult1.result)
                {
                    intPt1 = intPt2;
                }
            } else if(bVal2 && ptResult2.result) {
                intPt1 = intPt2;
            } else if(bVal1 && !ptResult1.result) {
                n1--;           
            }
        } else if(n1 == 2) {
            bool bVal1 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt1, 0, ptResult1);
            bool bVal2 = PtIsOnGeodesic(locus.locusStart, locus.locusEnd, intPt2, 0, ptResult2);
            if(!bVal1 && !bVal2)
                n1 = 0;
            else if(bVal1 && !bVal2) {
                n1 = 1;
                if(!ptResult1.result)
                    n1 = 0;
            }
            else if(!bVal1 && bVal2) {
                n1 = 1;
                if(!ptResult2.result)
                    n1 = 0;
                else {
                    intPt1 = intPt2;
                }
            }
            else {
                if(!ptResult1.result && ptResult2.result)
                {
                    n1 = 1;
                    intPt1 = intPt2;
                }
                else if(ptResult1.result && !ptResult2.result)
                {
                    n1 = 1;
                }
            }
        }



        DistVincenty(locus.geoStart, locus.geoEnd, result);
        double gcrs = result.azimuth;
        //        double gdist = result.distance;

        for(int i = 0; i < n1; i++)
        {
            LLPoint intPt;
            if(i == 0)
                intPt = intPt1;
            if(i == 1)
                intPt = intPt2;
            double dCrsFromPt, dDistFromPt;
            LLPoint perpPt = PerpIntercept(locus.geoStart, gcrs, intPt, dCrsFromPt, dDistFromPt, dTol);

            DistVincenty(perpPt, locus.geoStart, result);
            double distbase = result.distance;

            LLPoint locPt = PointOnLocusP(locus, perpPt, dTol, dEps);

            DistVincenty(locPt, arcCenter, result);
            double distCenter = result.distance;

            double errarray[2];
            double distarray[2];
            errarray[1] = distCenter - arcRadius;
            if(fabs(errarray[1]) >= dTol)
            {       
                distarray[1] = distbase;

                int k = 0;
                int maxCount = 15;

                double newDistbase = 1.001 * distbase;

                while(k < maxCount && !isnan(newDistbase) && fabs(errarray[1]) > dTol)
                {
                    perpPt = DestVincenty(locus.geoStart, gcrs, newDistbase);
                    locPt = PointOnLocusP(locus, perpPt, dTol, dEps);
                    DistVincenty(locPt, arcCenter, result);
                    distCenter = result.distance;
                    double dErr = distCenter - arcRadius;

                    distarray[0] = distarray[1];
                    distarray[1] = newDistbase;
                    errarray[0] = errarray[1];
                    errarray[1] = dErr;

                    FindLinearRoot(distarray, errarray, newDistbase);
                    k++;
                }
            }

            LLPoint geoPt;
            if(PtIsOnLocus(locus, locPt, geoPt, 1e-6)) //dTol))
            {
                if(i == 0)
                    intPt1 = locPt;
                if(i == 1)
                    intPt2 = locPt;
                nIntersections++;
            }
        }
        intersection1 = intPt1;
        intersection2 = intPt2;
        DistVincenty(intersection1, intersection2, result);
        if(n1 == 2 && IsNearZero(result.distance, 0.5e-8))
        {
            nIntersections = 1;
        }

        return nIntersections;
    }
}