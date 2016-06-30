/** \file PtIsOnGeodesic.cpp
*   \brief
*/

/****************************************************************************/
/*  PtIsOnGeodesic.cpp                                                      */
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

    // returns true if value was calculated (PtIsOnGeodesicResult structure
    // will be updated with computed values), PtIsOnGeodesicResult.result == true
    // if Point is on Geodesic, false otherwise.
    // return false if there was a problem in performing calculations (main DistVincenty())

    /**
    *
    */
    bool PtIsOnGeodesic(const LLPoint &pt1, const LLPoint &pt2, const LLPoint &pt3, int lengthCode,
                        PtIsOnGeodesicResult &result)
    {
        InverseResult invResult;
        if (!DistVincenty(pt1, pt3, invResult))
            return false;
        double dist13 = invResult.distance;
        //        double crs13 = invResult.azimuth;

        if (!DistVincenty(pt1, pt2, invResult))
            return false;

        double dist12 = invResult.distance;
        double crs12 = invResult.azimuth;

        LLPoint testPt2 = DestVincenty(pt1, crs12, dist13);

        if (!DistVincenty(pt3, testPt2, invResult))
            return false;

        double distError = invResult.distance;

        if (distError <= kTolPtIsOnGeodesic)
        {
            if (lengthCode > 0 || dist13 - dist12 <= kTolPtIsOnGeodesic)
                result.result = true;
            else
                result.result = false;
        }
        else if (lengthCode == 2)
        {
            testPt2 = DestVincenty(pt1, crs12 + M_PI, dist13);

            if (!DistVincenty(pt3, testPt2, invResult))
                return false;
            distError = invResult.distance;
            if (distError <= kTolPtIsOnGeodesic)
                result.result = true;
            else
                result.result = false;
        }
        else
        {
            result.result = false;
        }
        result.geoStart = pt1;
        result.geoEnd = pt2;
        result.geoPt = testPt2;
        result.lengthCode = lengthCode;
        return true;
    }
}
