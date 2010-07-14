/**	\file TestPerpTangentPoints.cpp
*	\brief 
*/

/****************************************************************************/
/*	TestPerpTangentPoints.cpp												*/
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

//#include "stdafx.h"
#include <string>
#include <fstream>
#include "LatLongConversions.h"
#include "..\GeoFormulas\Conversions.h"
#include "..\GeoFormulas\GeoFormulas.h"
#include <boost/regex.hpp>

using namespace boost;
using namespace GeoCalcs;
using namespace std;

bool ParseTestPerpTangentPoints(string sString)
{
	bool bPassed = false;
	TrimWhitespace(sString);
	string sTestId, sGeoStartLat, sGeoStartLon, sGeoAzimuth;
	string sArcCenterLat, sArcCenterLon, sArcRadius;
	string sIntPt1Lat, sIntPt1Lon, sIntPt2Lat, sIntPt2Lon;
	string sTanPt1Lat, sTanPt1Lon, sTanPt2Lat, sTanPt2Lon;
	try
	{
		regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

		string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
		sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";

		regex pat(sRxPat, flags);

		int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, };
		sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
		if(it != sregex_token_iterator())
		{
			sTestId = *it++;
			sGeoStartLat = *it++;
			sGeoStartLon = *it++;
			sGeoAzimuth = *it++;
			sArcCenterLat = *it++;
			sArcCenterLon = *it++;
			sArcRadius = *it++;
			sIntPt1Lat = *it++;
			sIntPt1Lon = *it++;
			sIntPt2Lat = *it++;
			sIntPt2Lon = *it++;
			sTanPt1Lat = *it++;
			sTanPt1Lon = *it++;
			sTanPt2Lat = *it++;
			sTanPt2Lon = *it++;
			bPassed = true;
		}
	}
	catch(regex_error & e)
	{
		cout << "\n" << e.what();
		return false;
	}

	LLPoint geoPt(Deg2Rad(ParseLatitude(sGeoStartLat)), Deg2Rad(ParseLongitude(sGeoStartLon)));
	double geoAzimuth = Deg2Rad(atof(sGeoAzimuth.c_str()));

	LLPoint arc(Deg2Rad(ParseLatitude(sArcCenterLat)), Deg2Rad(ParseLongitude(sArcCenterLon)));
	double radius = NmToMeters(atof(sArcRadius.c_str()));

	LLPoint llIntPt1(Deg2Rad(ParseLatitude(sIntPt1Lat)), Deg2Rad(ParseLongitude(sIntPt1Lon)));
	LLPoint llIntPt2(Deg2Rad(ParseLatitude(sIntPt2Lat)), Deg2Rad(ParseLongitude(sIntPt2Lon)));

	LLPoint tangentPt1(Deg2Rad(ParseLatitude(sTanPt1Lat)), Deg2Rad(ParseLongitude(sTanPt1Lon)));
	LLPoint tangentPt2(Deg2Rad(ParseLatitude(sTanPt2Lat)), Deg2Rad(ParseLongitude(sTanPt2Lon)));

	
	LLPoint linePts[2];
	LLPoint tanPts[2];
	PerpTangentPoints(geoPt, geoAzimuth, arc, radius, linePts, tanPts, 1e-9);


		string sInt1Lat = ConvertLatitudeDdToDms(Rad2Deg(linePts[0].latitude));
		string sInt1Lon = ConvertLongitudeDdToDms(Rad2Deg(linePts[0].longitude));
		string sInt2Lat = ConvertLatitudeDdToDms(Rad2Deg(linePts[1].latitude));
		string sInt2Lon = ConvertLongitudeDdToDms(Rad2Deg(linePts[1].longitude));
		string sTan1Lat = ConvertLatitudeDdToDms(Rad2Deg(tanPts[0].latitude));
		string sTan1Lon = ConvertLongitudeDdToDms(Rad2Deg(tanPts[0].longitude));
		string sTan2Lat = ConvertLatitudeDdToDms(Rad2Deg(tanPts[1].latitude));
		string sTan2Lon = ConvertLongitudeDdToDms(Rad2Deg(tanPts[1].longitude));

		double dTol = 1e-10;

		if(sInt1Lat.compare(sIntPt1Lat) != 0)
		{
			double dLat = Deg2Rad(ParseLatitude(sIntPt1Lat));
			if(IsApprox(dLat, linePts[0].latitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Intercept pt 1 latitude: " << sIntPt1Lat << "  calced: " << sInt1Lat;
			} else {
				cout << "\n" << sTestId << " failed: Expected Intercept pt 1 latitude: " << sIntPt1Lat << "  calced: " << sInt1Lat;
				bPassed = false;
			}
		}

		if(sInt1Lon.compare(sIntPt1Lon) != 0)
		{
			double dLon = Deg2Rad(ParseLongitude(sIntPt1Lon));
			if(IsApprox(dLon, linePts[0].longitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Intercept pt 1 longitude: " << sIntPt1Lon << "  calced: " << sInt1Lon;
			} else {
				cout << "\n" << sTestId << " failed: Expected Intercept pt 1 longitude: " << sIntPt1Lon << "  calced: " << sInt1Lon;
				bPassed = false;
			}
		}

		if(sInt2Lat.compare(sIntPt2Lat) != 0)
		{
			double dLat = Deg2Rad(ParseLatitude(sIntPt2Lat));
			if(IsApprox(dLat, linePts[1].latitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Intercept pt 2 latitude: " << sIntPt2Lat << "  calced: " << sInt2Lat;
			} else {
				cout << "\n" << sTestId << " failed: Expected Intercept pt 2 latitude: " << sIntPt2Lat << "  calced: " << sInt2Lat;
				bPassed = false;
			}
		}

		if(sInt2Lon.compare(sIntPt2Lon) != 0)
		{
			double dLon = Deg2Rad(ParseLongitude(sIntPt2Lon));
			if(IsApprox(dLon, linePts[1].longitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Intercept pt 2 longitude: " << sIntPt2Lon << "  calced: " << sInt2Lon;
			} else {
				cout << "\n" << sTestId << " failed: Expected Intercept pt 2 longitude: " << sIntPt2Lon << "  calced: " << sInt2Lon;
				bPassed = false;
			}
		}




		if(sTan1Lat.compare(sTanPt1Lat) != 0)
		{
			double dLat = Deg2Rad(ParseLatitude(sTanPt1Lat));
			if(IsApprox(dLat, tanPts[0].latitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Tangent pt 1 latitude: " << sTanPt1Lat << "  calced: " << sTan1Lat;
			} else {
				cout << "\n" << sTestId << " failed: Expected Tangent pt 1 latitude: " << sTanPt1Lat << "  calced: " << sTan1Lat;
				bPassed = false;
			}
		}

		if(sTan1Lon.compare(sTanPt1Lon) != 0)
		{
			double dLon = Deg2Rad(ParseLongitude(sTanPt1Lon));
			if(IsApprox(dLon, tanPts[0].longitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Tangent pt 1 longitude: " << sTanPt1Lon << "  calced: " << sTan1Lon;
			} else {
				cout << "\n" << sTestId << " failed: Expected Tangent pt 1 longitude: " << sTanPt1Lon << "  calced: " << sTan1Lon;
				bPassed = false;
			}
		}

		if(sTan2Lat.compare(sTanPt2Lat) != 0)
		{
			double dLat = Deg2Rad(ParseLatitude(sTanPt2Lat));
			if(IsApprox(dLat, tanPts[1].latitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Tangent pt 2 latitude: " << sTanPt2Lat << "  calced: " << sTan2Lat;
			} else {
				cout << "\n" << sTestId << " failed: Expected Tangent pt 2 latitude: " << sTanPt2Lat << "  calced: " << sTan2Lat;
				bPassed = false;
			}
		}

		if(sTan2Lon.compare(sTanPt2Lon) != 0)
		{
			double dLon = Deg2Rad(ParseLongitude(sTanPt2Lon));
			if(IsApprox(dLon, tanPts[1].longitude, dTol))
			{
				cout << "\n" << sTestId << " within rounding tolerance of " << dTol << ": Input Tangent pt 2 longitude: " << sTanPt2Lon << "  calced: " << sTan2Lon;
			} else {
				cout << "\n" << sTestId << " failed: Expected Tangent pt 2 longitude: " << sTanPt2Lon << "  calced: " << sTan2Lon;
				bPassed = false;
			}
		}






	return bPassed;	
}

int TestPerpTangentPoints(const string & sFilePath)
{
	ifstream infile;
	infile.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	int nCount = 0;
	int nCommentCount = 0;
	bool bPassed = true;
	try
	{
		string sLine;
		infile.open(sFilePath.c_str(), ifstream::in);

		while(!infile.eof())
		{
			getline(infile, sLine);			
			if(sLine.at(0) == '#')
			{
				nCommentCount++;
			}
			else
			{
				if(!ParseTestPerpTangentPoints(sLine))
					bPassed = false;
				nCount++;
			}
		}
		infile.close();
		return bPassed;
	}

	catch(ifstream::failure e)
	{
		int nError = -99;
		// Per C++ standards for ifstream::failbit with global function getline
		// No characters were extracted because the end was prematurely found.Notice
		// that some eofbit cases will also set failbit.
		// In this case the end of the file is read and causes both flags to be raised,
		// so this presumably means all the data has been read correctly.
		if((infile.rdstate() & ifstream::failbit) && (infile.rdstate() & ifstream::eofbit) != 0)
			nError = bPassed;
		else if((infile.rdstate() & ifstream::failbit) != 0)
			nError = -1;
		else if((infile.rdstate() & ifstream::badbit) != 0)
			nError = -2;
		else if((infile.rdstate() & ifstream::eofbit) != 0)
			nError = -3;
		if(infile.is_open())
			infile.close();
		return nError;
	}
}