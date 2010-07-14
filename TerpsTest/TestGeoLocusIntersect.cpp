/**	\file TestGeoLocusIntersect.cpp
*	\brief 
*/

/****************************************************************************/
/*	TestGeoLocusIntersect.cpp												*/
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

bool ParseGeoLocusIntersect3(string sLine3, string & sIntersectionLat, string & sIntersectionLon)
{
    bool bPassed = false;
    TrimWhitespace(sLine3);
    try
    {
        regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

        string sRxPat = "[,][A-z]+[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";

        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, };
        sregex_token_iterator it(sLine3.begin(), sLine3.end(), pat, sub_matches);
        if(it != sregex_token_iterator())
        {
            sIntersectionLat = *it++;
            sIntersectionLon = *it++;
            bPassed = true;
        }
    }
    catch(regex_error & e)
    {
        cout << "\n" << e.what();
        return false;
    }
    return bPassed;

}

bool ParseGeoLocusIntersect2(string sLine2, string & sGeoStartLat, string & sGeoStartLon,
                             string & sGeoEndLat, string & sGeoEndLon,
                             string & sLocusStartLat, string & sLocusStartLon, string & sLocusEndLat, string & sLocusEndLon,
                             string & sLocusStartDist, string & sLocusEndDist)
{
	bool bPassed = false;
	TrimWhitespace(sLine2);
	//string sTestId, sGeodesicStartLat, sGeodesicStartLong, sGeodesicEndLat, sGeodesicEndLong;
	//string sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong;
	//string sLocusStartDist, sLocusEndDist, sTestPointLat, sTestPointLong;
	try
	{
		regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

		string sRxPat = "[,][A-z ]+[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)";

		regex pat(sRxPat, flags);
		int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, };
		sregex_token_iterator it(sLine2.begin(), sLine2.end(), pat, sub_matches);
		if(it != sregex_token_iterator())
        {
			sGeoStartLat = *it++;
			sGeoStartLon = *it++;
			sGeoEndLat = *it++;
			sGeoEndLon = *it++;
            sLocusStartLat = *it++;
            sLocusStartLon = *it++;
            sLocusEndLat = *it++;
            sLocusEndLon = *it++;
            sLocusStartDist = *it++;
            sLocusEndDist = *it++;
			bPassed = true;
		}
	}
	catch(regex_error & e)
	{
		cout << "\n" << e.what();
		return false;
	}
	return bPassed;
}

bool ParseGeoLocusIntersect(string sLine1, string sLine2, string sLine3)
{	
	bool bPassed = true;
	TrimWhitespace(sLine1);
	string sTestId, sGeodesicStartLat, sGeodesicStartLong, sGeodesicEndLat, sGeodesicEndLong;
	try
	{
		regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

		string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
		sRxPat += "[A-z ]+[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		regex pat(sRxPat, flags);
		int const sub_matches[] = {1, 2, 3, 4, 5, };
		sregex_token_iterator it(sLine1.begin(), sLine1.end(), pat, sub_matches);
		if(it != sregex_token_iterator())
		{
			sTestId = *it++;
			sGeodesicStartLat = *it++;
			sGeodesicStartLong = *it++;
			sGeodesicEndLat = *it++;
			sGeodesicEndLong = *it++;
		}
	}
	catch(regex_error & e)
	{
		cout << "\n" << e.what();
		return false;
	}
    string sLocusGeoStartLat, sLocusGeoStartLong, sLocusGeoEndLat, sLocusGeoEndLong;
    string sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong;
    string sLocusStartDist, sLocusEndDist, sIntersectionLat, sIntersectionLong;

    if(!ParseGeoLocusIntersect2(sLine2, sLocusGeoStartLat, sLocusGeoStartLong, sLocusGeoEndLat, sLocusGeoEndLong,
        sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong, sLocusStartDist, sLocusEndDist))
        bPassed = false;
    else {
        if(!ParseGeoLocusIntersect3(sLine3, sIntersectionLat, sIntersectionLong))
            bPassed = false;
        else {
            Locus locus;
            locus.geoStart.Set(Deg2Rad(ParseLatitude(sLocusGeoStartLat)), Deg2Rad(ParseLongitude(sLocusGeoStartLong)));
            locus.geoEnd.Set(Deg2Rad(ParseLatitude(sLocusGeoEndLat)), Deg2Rad(ParseLongitude(sLocusGeoEndLong)));
            locus.locusStart.Set(Deg2Rad(ParseLatitude(sLocusStartLat)), Deg2Rad(ParseLongitude(sLocusStartLong)));
            locus.locusEnd.Set(Deg2Rad(ParseLatitude(sLocusEndLat)), Deg2Rad(ParseLongitude(sLocusEndLong)));
            locus.startDist = NmToMeters(atof(sLocusStartDist.c_str()));
            locus.endDist = NmToMeters(atof(sLocusEndDist.c_str()));

            LLPoint geoStart(Deg2Rad(ParseLatitude(sGeodesicStartLat)), Deg2Rad(ParseLongitude(sGeodesicStartLong)));
            LLPoint geoEnd(Deg2Rad(ParseLatitude(sGeodesicEndLat)), Deg2Rad(ParseLongitude(sGeodesicEndLong)));
            
            LLPoint intersection;
            int nVal = GeoLocusIntersect(geoStart, geoEnd, locus, intersection, Tol(), Eps());
            if(nVal == 0)
			{
				if(sIntersectionLat.compare("N/A") != 0)
				{
					string sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intersection.latitude));
					string sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intersection.longitude));
					cout << "\n" << sTestId << "failed: Expected no solution. Calced a solution of Latitude" << sPtIntLat << " and Longitude " << sPtIntLon;
					bPassed = false;
				}
			}
            else
            {
				string sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intersection.latitude));
				string sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intersection.longitude));
				if(sPtIntLat.compare(sIntersectionLat) != 0)
				{
					double dLat = Deg2Rad(ParseLatitude(sIntersectionLat));
					if(IsApprox(dLat, intersection.latitude, 1e-10))
						cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect Latitude: " << sIntersectionLat << " calced: " << sPtIntLat;
					else {
						cout << "\n" << sTestId << " failed: Expected Intersect latitude: " << sIntersectionLat << "  calced: " << sPtIntLat;
						bPassed = false;
					}
				}
				if(sPtIntLon.compare(sIntersectionLong) != 0)
				{
					double dLon = Deg2Rad(ParseLongitude(sIntersectionLong));
					if(IsApprox(dLon, intersection.longitude, 1e-10))
						cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect Longitude: " << sIntersectionLong << " calced: " << sPtIntLon;
					else {
						cout << "\n" << sTestId << " failed: Expected Intersect longitude: " << sIntersectionLong << "  calced: " << sPtIntLon;
						bPassed = false;
					}
				}

            }
        }
    }
	return bPassed;	
}


int TestGeoLocusIntersect(const string & sFilePath)
{
	ifstream infile;
	infile.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	int nCount = 0;
	int nCommentCount = 0;
	bool bPassed = true;
	try
	{
		string sLine1, sLine2, sLine3;
		infile.open(sFilePath.c_str(), ifstream::in);

		while(!infile.eof())
		{
			getline(infile, sLine1);			
			if(sLine1.at(0) == '#')
			{
				nCommentCount++;
			}
			else
			{
				getline(infile, sLine2);
				getline(infile, sLine3);
				if(!ParseGeoLocusIntersect(sLine1, sLine2, sLine3))
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