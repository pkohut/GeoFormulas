/** \file TestPointToArcTangents.cpp
*   \brief
*/

/****************************************************************************/
/*  TestPointToArcTangents.cpp                                              */
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

bool ParseTestPointToArcTangents(string sString)
{
    bool bPassed = false;
    trim(sString);
    string sTestId, sPointLat, sPointLon, sArcCenterLat, sArcCenterLon, sArcRadius;
    string sTanPt1Lat, sTanPt1Lon, sTanPt2Lat, sTanPt2Lon;
    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";

        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,};
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            sTestId = *it++;
            sPointLat = *it++;
            sPointLon = *it++;
            sArcCenterLat = *it++;
            sArcCenterLon = *it++;
            sArcRadius = *it++;
            sTanPt1Lat = *it++;
            sTanPt1Lon = *it++;
            sTanPt2Lat = *it++;
            sTanPt2Lon = *it++;
            bPassed = true;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }

    LLPoint pt(Deg2Rad(ParseLatitude(sPointLat)), Deg2Rad(ParseLongitude(sPointLon)));
    LLPoint arc(Deg2Rad(ParseLatitude(sArcCenterLat)), Deg2Rad(ParseLongitude(sArcCenterLon)));
    double radius = NmToMeters(atof(sArcRadius.c_str()));

    LLPoint tangentPt1;
    LLPoint tangentPt2;

    if (sTanPt1Lat.compare("N/A") != 0)
    {
        tangentPt1.Set(Deg2Rad(ParseLatitude(sTanPt1Lat)), Deg2Rad(ParseLongitude(sTanPt1Lon)));
        tangentPt2.Set(Deg2Rad(ParseLatitude(sTanPt2Lat)), Deg2Rad(ParseLongitude(sTanPt2Lon)));
    }

    LLPoint tanPt1, tanPt2;

    int nIndex = PointToArcTangents(pt, arc, radius, tanPt1, tanPt2, 1e-8);

    if (nIndex == 0)
    {
        if (sTanPt1Lat.compare("N/A") != 0)
        {
            bPassed = false;
            cout << "\n" << sTestId << " Failed: Returned with no solution.";
        }

    }
    else
    {

        string sTan1Lat = ConvertLatitudeDdToDms(Rad2Deg(tanPt1.latitude));
        string sTan1Lon = ConvertLongitudeDdToDms(Rad2Deg(tanPt1.longitude));
        string sTan2Lat = ConvertLatitudeDdToDms(Rad2Deg(tanPt2.latitude));
        string sTan2Lon = ConvertLongitudeDdToDms(Rad2Deg(tanPt2.longitude));

        double dTol = 1e-10;
        if (sTan1Lat.compare(sTanPt1Lat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(sTanPt1Lat));
            if (IsApprox(dLat, tanPt1.latitude, dTol))
            {
                cout << "\n" << sTestId << " within rounding tolerance of " << dTol <<
                ": Input Tangent pt 1 latitude: " << sTanPt1Lat << "  calced: " << sTan1Lat;
            }
            else
            {
                cout << "\n" << sTestId << " failed: Expected Tangent pt 1 latitude: " << sTanPt1Lat << "  calced: " <<
                sTan1Lat;
                bPassed = false;
            }
        }

        if (sTan1Lon.compare(sTanPt1Lon) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(sTanPt1Lon));
            if (IsApprox(dLon, tanPt1.longitude, dTol))
            {
                cout << "\n" << sTestId << " within rounding tolerance of " << dTol <<
                ": Input Tangent pt 1 longitude: " << sTanPt1Lon << "  calced: " << sTan1Lon;
            }
            else
            {
                cout << "\n" << sTestId << " failed: Expected Tangent pt 1 longitude: " << sTanPt1Lon << "  calced: " <<
                sTan1Lon;
                bPassed = false;
            }
        }

        if (sTan2Lat.compare(sTanPt2Lat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(sTanPt2Lat));
            if (IsApprox(dLat, tanPt2.latitude, dTol))
            {
                cout << "\n" << sTestId << " within rounding tolerance of " << dTol <<
                ": Input Tangent pt 2 latitude: " << sTanPt2Lat << "  calced: " << sTan2Lat;
            }
            else
            {
                cout << "\n" << sTestId << " failed: Expected Tangent pt 2 latitude: " << sTanPt2Lat << "  calced: " <<
                sTan2Lat;
                bPassed = false;
            }
        }

        if (sTan2Lon.compare(sTanPt2Lon) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(sTanPt2Lon));
            if (IsApprox(dLon, tanPt2.longitude, dTol))
            {
                cout << "\n" << sTestId << " within rounding tolerance of " << dTol <<
                ": Input Tangent pt 2 longitude: " << sTanPt2Lon << "  calced: " << sTan2Lon;
            }
            else
            {
                cout << "\n" << sTestId << " failed: Expected Tangent pt 2 longitude: " << sTanPt2Lon << "  calced: " <<
                sTan2Lon;
                bPassed = false;
            }
        }


    }


    return bPassed;
}

int TestPointToArcTangents(const string &sFilePath)
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
                if (!ParseTestPointToArcTangents(sLine))
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
