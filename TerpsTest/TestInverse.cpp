/** \file TestInverse.cpp
*   \brief
*/

/****************************************************************************/
/*  TestInverse.cpp                                                         */
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

/*
bool ParseTestInverseLine(string sString)
{
    bool bPassed = true;
    TrimWhitespace(sString);
    string soTestId, soStartLat, soStartLong, soDestLat, soDestLong, soComputedAz, soComputedReverseAz, soComputedDist;
    try
    {
        regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)";
        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, };
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if(it != sregex_token_iterator())
        {
            soTestId = *it++;
            soStartLat = *it++;
            soStartLong = *it++;
            soDestLat = *it++;
            soDestLong = *it++;
            soComputedAz = *it++;
            soComputedReverseAz = *it++;
            soComputedDist = *it++;
        }
    }
    catch(regex_error & e)
    {
        cout << "\n" << e.what();
        return false;
    }
    CPolarCoordinate start;
    CPolarCoordinate dest;
    start.SetUpDownAngleInDegrees(ParseLatitude(soStartLat));
    start.SetLeftRightAngleInDegrees(ParseLongitude(soStartLong));
    dest.SetUpDownAngleInDegrees(ParseLatitude(soDestLat));
    dest.SetLeftRightAngleInDegrees(ParseLatitude(soDestLong));

    double dDist, dReverseAz, dAz;
    CEarth earth;
    dDist = earth.GetSurfaceDistance(start, dest, &dAz, &dReverseAz);
    int x = 0;
    x++;

    //CGeoCalcs geo1;
    //InverseResult result;
    //if(!geo1.DistVincenty(soStartLat, soStartLong, soDestLat, soDestLong, result))
    //  bPassed = false;
    //else
    //{
    //  result.distance = MetersToNm(result.distance);
    //  result.azimuth = Rad2Deg(result.azimuth);
    //  result.reverseAzimuth = Rad2Deg(result.reverseAzimuth);
        dDist = MetersToNm(dDist);
        char szBuffer[25];
        sprintf(szBuffer, "%07.5f", dDist);
        if(soComputedDist.compare(szBuffer) != 0)
        {
            cout << "\n" << soTestId << "failed: Expected distance: " << soComputedDist << "  calced: " << szBuffer;
            bPassed = false;
        }

        sprintf(szBuffer, "%07.5f", dAz);
        if(soComputedAz.compare(szBuffer) != 0)
        {
            cout << "\n" << soTestId << "failed: Expected azimuth: " << soComputedAz << "  calced: " << szBuffer;
            bPassed = false;
        }

        sprintf(szBuffer, "%07.5f", dReverseAz);
        if(soComputedReverseAz.compare(szBuffer) != 0)
        {
            cout << "\n" << soTestId << "failed: Expected reverse azimuth: " << soComputedReverseAz << "  calced: " << szBuffer;
            bPassed = false;
        }
    // }
    return bPassed;
}
*/


bool ParseTestInverseLine(string sString)
{
    bool bPassed = true;
    trim(sString);
    string soTestId, soStartLat, soStartLong, soDestLat, soDestLong;
    string soComputedAz, soComputedReverseAz, soComputedDist;

    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)";
        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8,};
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            soTestId = *it++;
            soStartLat = *it++;
            soStartLong = *it++;
            soDestLat = *it++;
            soDestLong = *it++;
            soComputedAz = *it++;
            soComputedReverseAz = *it++;
            soComputedDist = *it++;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }

    InverseResult result;

    if (!DistVincenty(LLPoint(Deg2Rad(ParseLatitude(soStartLat)), Deg2Rad(ParseLongitude(soStartLong))),
                      LLPoint(Deg2Rad(ParseLatitude(soDestLat)), Deg2Rad(ParseLongitude(soDestLong))), result))
        bPassed = false;
    else
    {
        result.distance = MetersToNm(result.distance);
        result.azimuth = Rad2Deg(result.azimuth);
        //      double raz = result.reverseAzimuth;
        result.reverseAzimuth = Rad2Deg(result.reverseAzimuth);

        char szBuffer[25];

        sprintf(szBuffer, "%07.5f", result.distance);
        if (soComputedDist.compare(szBuffer) != 0)
        {
            cout << "\n" << soTestId << " failed: Input distance: " << soComputedDist << "  calced: " << szBuffer;
            bPassed = false;
        }

        if (result.azimuth == 360.0 || result.azimuth == 0.0)
        {
            if (atof(soComputedAz.c_str()) == 0.0)
                result.azimuth = 0.0;
            else
                result.azimuth = 360.0;
        }
        sprintf(szBuffer, "%07.5f", result.azimuth);
        if (soComputedAz.compare(szBuffer) != 0)
        {
            if (IsApprox(result.azimuth, atof(soComputedAz.c_str()), 1e-7))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-7: Input azimuth: " << soComputedAz <<
                "  calced: " << szBuffer;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Input azimuth: " << soComputedAz << "  calced: " << szBuffer;
                bPassed = false;
            }
        }

        if (result.reverseAzimuth == 360.0 || result.reverseAzimuth == 0.0)
        {
            if (atof(soComputedReverseAz.c_str()) == 0.0)
                result.reverseAzimuth = 0.0;
            else
                result.reverseAzimuth = 360.0;
        }

        sprintf(szBuffer, "%07.5f", result.reverseAzimuth);
        if (soComputedReverseAz.compare(szBuffer) != 0)
        {
            if (IsApprox(result.reverseAzimuth, atof(soComputedReverseAz.c_str()), 1e-7))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-7: Input reverse azimuth: " <<
                soComputedReverseAz << "  calced: " << szBuffer;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Input reverse azimuth: " << soComputedReverseAz << "  calced: " <<
                szBuffer;
                bPassed = false;
            }
        }
    }
    return bPassed;
}


int TestInverse(const string &sFilePath)
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
                if (!ParseTestInverseLine(sLine))
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
