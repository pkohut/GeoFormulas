/** \file TestPerpIntercept.cpp
*   \brief
*/

/****************************************************************************/
/*  TestPerpIntercept.cpp                                                   */
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

//#include "stdafx.h"
#include <string>
#include <fstream>
#include "LatLongConversions.h"
#include "Conversions.h"
#include "GeoFormulas.h"
#include <regex>


using namespace GeoCalcs;
using namespace std;

bool ParseTestPerpIntercept(string sString)
{
    bool bPassed = true;
    trim(sString);
    string soTestId, soStartLat, soStartLong, soAz, soTestPtLat, soTestPtLong, soAzFromPt, soDistFromPt;
    string soInterceptLat, soInterceptLong;
    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";
        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,};
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            soTestId = *it++;
            soStartLat = *it++;
            soStartLong = *it++;
            soAz = *it++;
            soTestPtLat = *it++;
            soTestPtLong = *it++;
            soAzFromPt = *it++;
            soDistFromPt = *it++;
            soInterceptLat = *it++;
            soInterceptLong = *it++;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }

    double dCalcedCrsFromPt, dCalcedDistFromPt;
    LLPoint pt3;


    pt3 = PerpIntercept(LLPoint(Deg2Rad(ParseLatitude(soStartLat)), Deg2Rad(ParseLongitude(soStartLong))),
                        Deg2Rad(atof(soAz.c_str())),
                        LLPoint(Deg2Rad(ParseLatitude(soTestPtLat)), Deg2Rad(ParseLongitude(soTestPtLong))),
                        dCalcedCrsFromPt, dCalcedDistFromPt, kTol);

    string sLat = ConvertLatitudeDdToDms(Rad2Deg(pt3.latitude));
    string sLon = ConvertLongitudeDdToDms(Rad2Deg(pt3.longitude));

    if (sLat.compare(soInterceptLat) != 0)
    {
        cout << "\n" << soTestId << " failed: Input intercept latitude: " << soInterceptLat << "  calced: " << sLat;
        bPassed = false;
    }

    if (sLon.compare(soInterceptLong) != 0)
    {
        cout << "\n" << soTestId << " failed: Input intercept longitude: " << soInterceptLong << "  calced: " << sLon;
        bPassed = false;
    }
    return bPassed;
}


int TestPerpIntercept(const string &sFilePath)
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

        while (!infile.eof())
        {
            getline(infile, sLine);
            if (sLine.at(0) == '#')
            {
                nCommentCount++;
            }
            else
            {
                if (!ParseTestPerpIntercept(sLine))
                    bPassed = false;
                nCount++;
            }
        }
        infile.close();
        return bPassed;
    }

    catch (ifstream::failure e)
    {
        int nError = -99;
        // Per C++ standards for ifstream::failbit with global function getline
        // No characters were extracted because the end was prematurely found.Notice
        // that some eofbit cases will also set failbit.
        // In this case the end of the file is read and causes both flags to be raised,
        // so this presumably means all the data has been read correctly.
        if ((infile.rdstate() & ifstream::failbit) && (infile.rdstate() & ifstream::eofbit) != 0)
            nError = bPassed;
        else if ((infile.rdstate() & ifstream::failbit) != 0)
            nError = -1;
        else if ((infile.rdstate() & ifstream::badbit) != 0)
            nError = -2;
        else if ((infile.rdstate() & ifstream::eofbit) != 0)
            nError = -3;
        if (infile.is_open())
            infile.close();
        return nError;
    }
}
