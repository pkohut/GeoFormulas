/**	\file Conversions.h
*	\brief 
*/

/****************************************************************************/
/*	Conversions.h															*/
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

#pragma once
#include "Geolib.h"
#include "RNavConversionException.h"
#include <limits>

#define _USE_MATH_DEFINES 1
#include <math.h>

GEOAPI
inline bool _stdcall IsApprox(double a, double b,
					 const double precision = 1e-11)
{
	return( fabs(a - b) <= precision * std::min<const double>( fabs(a), fabs(b) ) );
}

GEOAPI
inline bool _stdcall IsNearZero(double a, double epsilon = 2e-6)
{
	return (fabs(a) < epsilon);
}

	//////////////////////////////////////////////////////////////////////////
	// functions returning common constants
//	inline double FeetPerMeter(void) { return 3.28083989501312335958005249343832020997375328083989501312335958; }
GEOAPI	inline double _stdcall FeetPerMeter(void) { return 1.0 / 0.3048; }
GEOAPI	inline double _stdcall MetersPerFoot(void) { return 0.3048; }

	// returns the number of feet per nautical mile ( 1852.0 / 0.3048 )
//	inline double FeetPerNm(void) { return 6076.115485564304461942257217847769028871391076115485564304461942; }
GEOAPI	inline double _stdcall FeetPerNm(void) { return 1852.0 / 0.3048; }

	// returns the number of nautical miles per foot ( 0.3048 / 1852.0 )
//	inline double NmPerFoot(void) { return 1.645788336933045356371490280777537796976241900647948164146868251e-4; }
GEOAPI	inline double _stdcall NmPerFoot(void) { return 0.3048 / 1852.0; }

	// returns meters per nautical mile ( 1852.0 )
GEOAPI	inline double _stdcall MetersPerNm(void) { return 1852.0; }

	// returns Nautical miles per 1 meter ( 1.0 / 1852.0 )
//	inline double NmPerMeter(void) { return 5.399568034557235421166306695464362850971922246220302375809935205e-4; }
GEOAPI	inline double _stdcall NmPerMeter(void) { return 1.0 / 1852.0; }


	// returns PI
//	inline double PI1(void) { return pi<double>(); }
//	inline double PI2(void) { return pi<double>() * 2.0; }

	// returns the constant for the base of the natural logarithm
//	inline double E(void) { return e<double>(); }


	//////////////////////////////////////////////////////////////////////////
	// Distance conversion functions
	// returns the conversion from feet to meters ( feet * 0.3048 )
GEOAPI	inline double _stdcall FeetToMeters(const double dFeet) { return dFeet * MetersPerFoot(); }

	// return the conversion from meters to feet { meters / 0.3048 )
GEOAPI	inline double _stdcall MetersToFeet(const double dMeters) { return dMeters * FeetPerMeter(); }

	// returns the conversion from feet to nautical miles (  feet * (0.3048 / 1852.0) )
GEOAPI	inline double _stdcall FeetToNm(const double dFeet) { return dFeet * NmPerFoot(); }

	// returns the conversion from nautical miles to feet ( nm * (1852.0 / 0.3048) )
GEOAPI	inline double _stdcall NmToFeet(const double dNm) { return dNm * FeetPerNm(); }

	// returns the conversion from meters to nautical miles ( meters / 1852.0 )
GEOAPI	inline double _stdcall MetersToNm(const double dMeters) { return dMeters * NmPerMeter(); }

	// returns the conversion from nautical miles to meters ( nm * 1852.0; )
GEOAPI	inline double _stdcall NmToMeters(const double dNm) { return dNm * MetersPerNm(); }


	//////////////////////////////////////////////////////////////////////////
	// Angular conversion functions
GEOAPI	inline double _stdcall Deg2Rad(const double dVal) { return dVal * (M_PI / 180.0); }
GEOAPI	inline double _stdcall Rad2Deg(const double dVal) { return dVal * (180.0 / M_PI); }
//	inline double Deg2Rad(const double dVal) { return dVal * (pi<double>() / 180.0); }
//	inline double Rad2Deg(const double dVal) { return dVal * (180.0 / pi<double>()); }
	


	//////////////////////////////////////////////////////////////////////////
	// Temperature conversion functions
	// returns the conversion from Celsius to Fahrenheit
GEOAPI	inline double _stdcall CelsiusToFahrenheit(const double dCelsius) { return 1.8 * dCelsius + 32.0; }

	// returns the conversion from Fahrenheit to Celsius
GEOAPI	inline double _stdcall FahrenheitToCelsius(const double dFahrenheit) { return (dFahrenheit - 32) / 1.8; }

	
