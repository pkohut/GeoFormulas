/**	\file TestDirect.cpp
*	\brief 
*/

/****************************************************************************/
/*	TestDirect.cpp															*/
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

bool ParseTestDirectLine(string sString)
{	
	bool bPassed = true;
	TrimWhitespace(sString);
	string sTestId, sStartLat, sStartLong, sDist, sAzimuth;
	string sComputedDestLat, sComputedDestLong;

	try
	{
		regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

		string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
		// todo: should this be
		// sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
		sRxPat += "([-+]?[0-9]*[].?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
		sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";
		regex pat(sRxPat, flags);

		int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, };
		sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
		if(it != sregex_token_iterator())
		{
			sTestId = *it++;
			sStartLat = *it++;
			sStartLong = *it++;
			sDist = *it++;
			sAzimuth = *it++;
			sComputedDestLat = *it++;
			sComputedDestLong = *it++;
		}
	}
	catch(regex_error & e)
	{
		cout << "\n" << e.what();
		return false;
	}


	LLPoint ll = DestVincenty(LLPoint(Deg2Rad(ParseLatitude(sStartLat)), Deg2Rad(ParseLongitude(sStartLong))),
						Deg2Rad(atof(sAzimuth.c_str())), NmToMeters(atof(sDist.c_str())));
	ll.latitude = Rad2Deg(ll.latitude);
	ll.longitude = Rad2Deg(ll.longitude);
	string sDestLat = ConvertLatitudeDdToDms(ll.latitude); // + (ll.latitude < 0.0 ? + "S" : + "N");
	string sDestLong = ConvertLongitudeDdToDms(ll.longitude); // + (ll.longitude < 0.0 ? + "W" : + "E");
//	double dComputedDestLat = ParseLatitude(sComputedDestLat);
//	double dComputedDestLong = ParseLongitude(sComputedDestLong);
	
	if(sDestLat.compare(sComputedDestLat) != 0)
	{
		cout << "\n" << sTestId << "failed: Expected latitude: " << sComputedDestLat << "  calced: " << sDestLat;
		bPassed = false;
	}
	if(sDestLong.compare(sComputedDestLong) != 0)
	{
		cout << "\n" << sTestId << "failed: Expected longitude: " << sComputedDestLong << "  calced: " << sDestLong;
		bPassed = false;
	}
	return bPassed;	
}


int TestDirect(const string & sFilePath)
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
				if(!ParseTestDirectLine(sLine))
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