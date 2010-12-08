/**	\file VectorMath.h
*	\brief 
*/

/****************************************************************************/
/*	VectorMath.h															*/
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
#include <math.h>

namespace VMath {
	
    class GEOAPI Vector3
	{
	public:
		Vector3()
		{
			x = y = z = 0.0;
		}
		Vector3(double _x, double _y, double _z)
		{
			x = _x; y = _y; z = _z;
		}

		friend Vector3 operator-(const Vector3 & v1, const Vector3 & v2)
		{
			return Vector3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
		}

		static double Length(const Vector3 & v)
		{
			return sqrt(Dot(v, v));
		}

		static double Dot(const Vector3 & u, const Vector3 & v)
		{
			return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
		}

		double x, y, z;
	};
}