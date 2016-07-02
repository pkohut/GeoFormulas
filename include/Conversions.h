/** \file Conversions.h
*   \brief
*/

/****************************************************************************/
/*  Conversions.h                                                           */
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

#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

#if defined(WIN32)
  #define _USE_MATH_DEFINES 1
  //#include <math.h>
#endif

#include "Geolib.h"
#include "RNavConversionException.h"


GEOAPI
inline bool IsApprox(double a, double b,
                     const double precision = 1e-11)
{
    return (fabs(a - b) <= precision * std::min(fabs(a), fabs(b)));
}

GEOAPI
inline bool IsNearZero(double a, double epsilon = 2e-6)
{
    return (fabs(a) < epsilon);
}

const double kMetersPerFoot = 0.3048;
const double kFeetPerMeter = 1.0 / 0.3048;
const double kMetersPerNm = 1852.0;
const double kFeetPerNm = kMetersPerNm / kMetersPerFoot;
const double kNmPerFoot = kMetersPerFoot / kMetersPerNm;
const double kNmPerMeter = 1.0 / kMetersPerNm;


//////////////////////////////////////////////////////////////////////////
// Distance conversion functions
// returns the conversion from feet to meters ( feet * 0.3048 )
GEOAPI inline double FeetToMeters(const double dFeet)
{ return dFeet * kMetersPerFoot; }

// return the conversion from meters to feet { meters / 0.3048 )
GEOAPI inline double MetersToFeet(const double dMeters)
{ return dMeters * kFeetPerMeter; }

// returns the conversion from feet to nautical miles (  feet * (0.3048 / 1852.0) )
GEOAPI inline double FeetToNm(const double dFeet)
{ return dFeet * kNmPerFoot; }

// returns the conversion from nautical miles to feet ( nm * (1852.0 / 0.3048) )
GEOAPI inline double NmToFeet(const double dNm)
{ return dNm * kFeetPerNm; }

// returns the conversion from meters to nautical miles ( meters / 1852.0 )
GEOAPI inline double MetersToNm(const double dMeters)
{ return dMeters * kNmPerMeter; }

// returns the conversion from nautical miles to meters ( nm * 1852.0; )
GEOAPI inline double NmToMeters(const double dNm)
{ return dNm * kMetersPerNm; }


//////////////////////////////////////////////////////////////////////////
// Angular conversion functions
GEOAPI inline double Deg2Rad(const double dVal)
{ return dVal * (M_PI / 180.0); }

GEOAPI inline double Rad2Deg(const double dVal)
{ return dVal * (180.0 / M_PI); }


//////////////////////////////////////////////////////////////////////////
// Temperature conversion functions
// returns the conversion from Celsius to Fahrenheit
GEOAPI inline double CelsiusToFahrenheit(const double dCelsius)
{ return 1.8 * dCelsius + 32.0; }

// returns the conversion from Fahrenheit to Celsius
GEOAPI inline double FahrenheitToCelsius(const double dFahrenheit)
{ return (dFahrenheit - 32) / 1.8; }
