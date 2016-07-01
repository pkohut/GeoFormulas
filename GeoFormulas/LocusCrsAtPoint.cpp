/** \file LocusCrsAtPoint.cpp
*   \brief
*/

/****************************************************************************/
/*  LocusCrsAtPoint.cpp                                                     */
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

    double LocusCrsAtPoint(const Locus &locus, const LLPoint &testPt, LLPoint &geoPt, const double dTol)
    {
        double dPerpCrs;
        return LocusCrsAtPoint(locus, testPt, geoPt, dPerpCrs, dTol);
    }

    double LocusCrsAtPoint(const Locus &locus, const LLPoint &testPt, LLPoint &geoPt,
                           double &dPerpCrs, const double dTol)
    {
        if (!PtIsOnLocus(locus, testPt, geoPt, dTol))
            return -1.0;

        InverseResult result;
        DistVincenty(testPt, geoPt, result);
        dPerpCrs = result.azimuth;

        DistVincenty(locus.geoStart, locus.geoEnd, result);
        dPerpCrs += atan((locus.endDist - locus.startDist) / result.distance);

        double dLocusCrs = 0.0;
        if (DistToLocusP(locus, geoPt, dTol, kEps) < 0)
            dLocusCrs = dPerpCrs - M_PI_2;
        else
            dLocusCrs = dPerpCrs + M_PI_2;

        if (dLocusCrs > M_2PI)
            dLocusCrs = dLocusCrs - M_2PI;

        return dLocusCrs;
    }
}
