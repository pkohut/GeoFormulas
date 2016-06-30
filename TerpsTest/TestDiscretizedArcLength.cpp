/** \file TestDiscretizedArcLength.cpp
*   \brief 
*/

/****************************************************************************/
/*  TestDiscretizedArcLength.cpp                                            */
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
#include "Conversions.h"
#include "GeoFormulas.h"
#include <boost/regex.hpp>

using namespace boost;
using namespace GeoCalcs;
using namespace std;

bool ParseDiscretizedArcLength(string sString)
{   
    bool bPassed = true;
    TrimWhitespace(sString);
    string sTestId, sArcCenterLat, sArcCenterLong, sArcRadius;
    string sStartAz, sEndAz, sDirection, sComputedArcLength;
    string sDirectComputedArcLength, sDifference;

    try
    {
        regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([-+]?[1])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "(.*)";
        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, };
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if(it != sregex_token_iterator())
        {
            sTestId = *it++;
            sArcCenterLat = *it++;
            sArcCenterLong = *it++;
            sArcRadius = *it++;
            sStartAz = *it++;
            sEndAz = *it++;
            sDirection = *it++;
            sComputedArcLength = *it++;
            sDirectComputedArcLength = *it++;
            sDifference = *it++;
        }
    }
    catch(regex_error & e)
    {
        cout << "\n" << e.what();
        return false;
    }


    int nSegments = 16;
    double dDist1 = DiscretizedArcLength(LLPoint(Deg2Rad(ParseLatitude(sArcCenterLat)), Deg2Rad(ParseLongitude(sArcCenterLong))),
                NmToMeters(atof(sArcRadius.c_str())), Deg2Rad(atof(sStartAz.c_str())), Deg2Rad(atof(sEndAz.c_str())),
                atoi(sDirection.c_str()), nSegments, kTol);
    dDist1 = MetersToNm(dDist1);


    double dDist2 = DirectArcLength(LLPoint(Deg2Rad(ParseLatitude(sArcCenterLat)), Deg2Rad(ParseLongitude(sArcCenterLong))),
                NmToMeters(atof(sArcRadius.c_str())), Deg2Rad(atof(sStartAz.c_str())), Deg2Rad(atof(sEndAz.c_str())),
                atoi(sDirection.c_str()), kTol);
    dDist2 = MetersToNm(dDist2);

//  double dError = dDist2 - dDist1;

    char szBuffer[20];
    sprintf(szBuffer, "%07.6f", dDist1);
    if(sComputedArcLength.compare(szBuffer) != 0)
    {
        if(szBuffer[strlen(szBuffer) - 1] == '0')
        {
            szBuffer[strlen(szBuffer) - 1] = '\0';
        }
        if(sComputedArcLength.compare(szBuffer) != 0)
        {
            if(IsApprox(dDist1, atof(sComputedArcLength.c_str()), 0.5e-8))
            {
                cout << "\n" << sTestId << " within rounding tolerance of 0.5e-8: Input Computed Arc Length: " << sComputedArcLength << "  calced: " << szBuffer;
            }
            else
            {
                cout << "\n" << sTestId << " failed: Expected Computed Arc Length: " << sComputedArcLength << "  calced: " << szBuffer;
                bPassed = false;
            }
        }
        
    }

    sprintf(szBuffer, "%07.6f", dDist2);
    if(sDirectComputedArcLength.compare(szBuffer) != 0)
    {
        if(szBuffer[strlen(szBuffer) - 1] == '0')
        {
            szBuffer[strlen(szBuffer) - 1] = '\0';
        }
        if(sDirectComputedArcLength.compare(szBuffer) != 0)
        {
            if(IsApprox(dDist1, atof(sComputedArcLength.c_str()), 0.5e-8))
            {
                cout << "\n" << sTestId << " within rounding tolerance of 0.5e-8: Input Direct Computed Arc Length: " << sDirectComputedArcLength << "  calced: " << szBuffer;
            }
            else
            {
                cout << "\n" << sTestId << " failed: Expected Direct Computed Arc Length: " << sDirectComputedArcLength << "  calced: " << szBuffer;
                bPassed = false;
            }
        }       
    }
    return bPassed; 
}


int TestDiscretizedArcLength(const string & sFilePath)
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
                if(!ParseDiscretizedArcLength(sLine))
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
