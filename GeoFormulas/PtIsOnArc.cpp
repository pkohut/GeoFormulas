/** \file PtIsOnArc.cpp
*   \brief
*/

/****************************************************************************/
/*  PtIsOnArc.cpp                                                           */
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
    bool PtIsOnArc(const LLPoint &llArcCenter, double dArcRadius,
                   double dArcStartAzimuth, double dArcEndAzimuth, int nArcDirection,
                   const LLPoint &llTestPt, int &bOnArc)
    {
        InverseResult invResult;
        if (!DistVincenty(llArcCenter, llTestPt, invResult))
            return false;

        bOnArc = false;

        if (fabs(invResult.distance - dArcRadius) <= 0.5e-3)
        {
            const double dSubtendedAng1 = GetArcExtent(dArcStartAzimuth, dArcEndAzimuth, nArcDirection, kTol);

            if (dSubtendedAng1 == M_2PI)
                bOnArc = true;
            else
            {
                const double dSubtendedAng2 = GetArcExtent(dArcStartAzimuth, invResult.azimuth,
                                                     nArcDirection, kTol);

                if (nArcDirection > 0)
                {
                    if (dSubtendedAng2 <= dSubtendedAng1)
                        bOnArc = true;
                }
                else
                {
                    if (dSubtendedAng2 >= dSubtendedAng1)
                        bOnArc = true;
                }
            }
        }
        return true;
    }
}
