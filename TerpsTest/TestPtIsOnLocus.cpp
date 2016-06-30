/** \file TestPtIsOnLocus.cpp
*   \brief 
*/

/****************************************************************************/
/*  TestPtIsOnLocus.cpp                                                     */
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

bool ParseTestPtIsOnLocus(string sString)
{   
    bool bPassed = true;
    TrimWhitespace(sString);
    string soTestId, soGeodesicStartLat, soGeodesicStartLong, soGeodesicEndLat, soGeodesicEndLong, soLocStartLat, soLocStartLong;
    string soLocEndLat, soLocEndLong, soLocStartDist, soLocEndDist, soTestPtLat, soTestPtLong, soResult;    
    try
    {
        regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[].?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-1])";
        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, };
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if(it != sregex_token_iterator())
        {
            soTestId = *it++;
            soGeodesicStartLat = *it++;
            soGeodesicStartLong = *it++;
            soGeodesicEndLat = *it++;
            soGeodesicEndLong = *it++;
            soLocStartLat = *it++;
            soLocStartLong = *it++;
            soLocEndLat = *it++;
            soLocEndLong = *it++;
            soLocStartDist = *it++;
            soLocEndDist = *it++;
            soTestPtLat = *it++;
            soTestPtLong = *it++;
            soResult = *it;
        }
    }
    catch(regex_error & e)
    {
        cout << "\n" << e.what();
        return false;
    }

    Locus locus;
    locus.geoStart.Set(Deg2Rad(ParseLatitude(soGeodesicStartLat)), Deg2Rad(ParseLongitude(soGeodesicStartLong)));
    locus.geoEnd.Set(Deg2Rad(ParseLatitude(soGeodesicEndLat)), Deg2Rad(ParseLongitude(soGeodesicEndLong)));
    locus.locusStart.Set(Deg2Rad(ParseLatitude(soLocStartLat)), Deg2Rad(ParseLongitude(soLocStartLong)));
    locus.locusEnd.Set(Deg2Rad(ParseLatitude(soLocEndLat)), Deg2Rad(ParseLongitude(soLocEndLong)));
    locus.startDist = NmToMeters(atof(soLocStartDist.c_str()));
    locus.endDist = NmToMeters(atof(soLocEndDist.c_str()));
    locus.lineType = 0;

    LLPoint llTestPt(LLPoint(Deg2Rad(ParseLatitude(soTestPtLat)), Deg2Rad(ParseLongitude(soTestPtLong))));
    LLPoint llProjPt;

    // Using a low 1e-3 tolerance value (0.5 mm) to test if point is on locus
    // Tests show this to be the lowest tolerance can be set and pass the
    // 8260.54A test results page.  If values had been computed internal
    // in doubles then 1e-8 could have easily been used.
    int bResult = PtIsOnLocus(locus, llTestPt, llProjPt, 1e-3);
    if(bResult != atoi(soResult.c_str()))
    {
        cout << "\n" << soTestId << " failed: expected result of " << soResult << "  cacled: " << bResult;
        bPassed = false;
    }
    return bPassed; 
}


int TestPtIsOnLocus(const string & sFilePath)
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
                if(!ParseTestPtIsOnLocus(sLine))
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