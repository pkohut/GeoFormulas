/** \file GetArcExtent.cpp
*   \brief
*/

/****************************************************************************/
/*  GetArcExtent.cpp                                                        */
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
    double GetArcExtent(double dStartCrs, double dEndCrs, const int nOrientation, double dTol)
    {
        double dstartCrs = dStartCrs;
        double dendCrs = dEndCrs;
        if (fabs(dstartCrs - dendCrs) < dTol)
            return M_2PI;
        if (nOrientation < 0)
        {
            double dTemp = dstartCrs;
            dstartCrs = dendCrs;
            dendCrs = dTemp;
        }
        double dAngle;
        if (dstartCrs > dendCrs)
            dAngle = dstartCrs - dendCrs;
        else
            dAngle = M_2PI + dstartCrs - dendCrs;
        if (nOrientation < 0)
            dAngle = -dAngle;
        return dAngle;

    }
}
