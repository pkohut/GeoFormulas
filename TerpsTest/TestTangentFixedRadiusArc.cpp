/** \file TestTangentFixedRadiusArc.cpp
*   \brief
*/

/****************************************************************************/
/*  TestTangentFixedRadiusArc.cpp                                           */
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

bool ParseTestTangentFixedRadiusArc(string sString)
{
    bool bPassed = true;
    trim(sString);
    string soTestId, soGeodesic1StartLat, soGeodesic1StartLon, soGeodesic1Azimuth, soGeodesic2StartLat, soGeodesic2StartLon;
    string soGeodesic2Azimuth, soArcRadius, soArcDirection, soArcCenterLat, soArcCenterLon;
    string soTangentPt1Lat, soTangentPt1Lon, soTangentPt2Lat, soTangentPt2Lon;
    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([N/A]+|[-+]?[1])[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";

        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,};
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            soTestId = *it++;
            soGeodesic1StartLat = *it++;
            soGeodesic1StartLon = *it++;
            soGeodesic1Azimuth = *it++;
            soGeodesic2StartLat = *it++;
            soGeodesic2StartLon = *it++;
            soGeodesic2Azimuth = *it++;
            soArcRadius = *it++;
            soArcDirection = *it++;
            soArcCenterLat = *it++;
            soArcCenterLon = *it++;
            soTangentPt1Lat = *it++;
            soTangentPt1Lon = *it++;
            soTangentPt2Lat = *it++;
            soTangentPt2Lon = *it++;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }

    LLPoint geodesic1Start(Deg2Rad(ParseLatitude(soGeodesic1StartLat)), Deg2Rad(ParseLongitude(soGeodesic1StartLon)));
    double geodesic1Azimuth = Deg2Rad(atof(soGeodesic1Azimuth.c_str()));
    LLPoint geodesic2Start(Deg2Rad(ParseLatitude(soGeodesic2StartLat)), Deg2Rad(ParseLongitude(soGeodesic2StartLon)));
    double geodesic2Azimuth = Deg2Rad(atof(soGeodesic2Azimuth.c_str()));
    double arcRadius = NmToMeters(atof(soArcRadius.c_str()));

    int arcDirection = 0;
    if (soArcDirection != "N/A")
    {
        arcDirection = atoi(soArcDirection.c_str());
    }

    LLPoint tangentPt1;
    LLPoint tangentPt2;
    LLPoint arcCenter;
    if (arcDirection != 0)
    {
        tangentPt1.Set(Deg2Rad(ParseLatitude(soTangentPt1Lat)), Deg2Rad(ParseLongitude(soTangentPt1Lon)));
        tangentPt2.Set(Deg2Rad(ParseLatitude(soTangentPt2Lat)), Deg2Rad(ParseLongitude(soTangentPt2Lon)));
        arcCenter.Set(Deg2Rad(ParseLatitude(soArcCenterLat)), Deg2Rad(ParseLongitude(soArcCenterLon)));
    }

    //  CGeoCalcs geo1;
    LLPoint tanPt1, tanPt2, centerPt;

    int nIndex = TangentFixedRadiusArc(geodesic1Start, geodesic1Azimuth, geodesic2Start, geodesic2Azimuth,
                                       arcRadius, arcDirection, centerPt, tanPt1, tanPt2, 1e-9);

    if (nIndex == 0)
    {
        if (soArcDirection != "N/A")
        {
            bPassed = false;
            cout << "\n" << soTestId << " Failed: Returned with no solution.";
        }

    }
    else
    {

        string sArcCenterLat = ConvertLatitudeDdToDms(Rad2Deg(centerPt.latitude));
        string sArcCenterLon = ConvertLongitudeDdToDms(Rad2Deg(centerPt.longitude));
        string sTan1Lat = ConvertLatitudeDdToDms(Rad2Deg(tanPt1.latitude));
        string sTan1Lon = ConvertLongitudeDdToDms(Rad2Deg(tanPt1.longitude));
        string sTan2Lat = ConvertLatitudeDdToDms(Rad2Deg(tanPt2.latitude));
        string sTan2Lon = ConvertLongitudeDdToDms(Rad2Deg(tanPt2.longitude));

        if (atoi(soArcDirection.c_str()) != arcDirection)
        {
            cout << "\n" << soTestId << " failed: Expected Arc direction: " << soArcDirection << "  calced: " <<
            arcDirection;
            bPassed = false;
        }

        if (sArcCenterLat.compare(soArcCenterLat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(soArcCenterLat));
            if (IsApprox(dLat, centerPt.latitude, 1e-10))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Arc center latitude: " <<
                soArcCenterLat << "  calced: " << sArcCenterLat;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Expected Arc center latitude: " << soArcCenterLat <<
                "  calced: " << sArcCenterLat;
                bPassed = false;
            }
        }

        if (sArcCenterLon.compare(soArcCenterLon) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(soArcCenterLon));
            if (IsApprox(dLon, centerPt.longitude, 1e-10))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Arc center longitude: " <<
                soArcCenterLon << "  calced: " << sArcCenterLon;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Expected Arc center longitude: " << soArcCenterLon <<
                "  calced: " << sArcCenterLon;
                bPassed = false;
            }
        }

        if (sTan1Lat.compare(soTangentPt1Lat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(soTangentPt1Lat));
            if (IsApprox(dLat, tanPt1.latitude, 1e-10))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Tangent pt 1 latitude: " <<
                soTangentPt1Lat << "  calced: " << sTan1Lat;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Expected Tangent pt 1 latitude: " << soTangentPt1Lat <<
                "  calced: " << sTan1Lat;
                bPassed = false;
            }
        }

        if (sTan1Lon.compare(soTangentPt1Lon) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(soTangentPt1Lon));
            if (IsApprox(dLon, tanPt1.longitude, 1e-10))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Tangent pt 1 longitude: " <<
                soTangentPt1Lon << "  calced: " << sTan1Lon;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Expected Tangent pt 1 longitude: " << soTangentPt1Lon <<
                "  calced: " << sTan1Lon;
                bPassed = false;
            }
        }

        if (sTan2Lat.compare(soTangentPt2Lat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(soTangentPt2Lat));
            if (IsApprox(dLat, tanPt2.latitude, 1e-10))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Tangent pt 2 latitude: " <<
                soTangentPt2Lat << "  calced: " << sTan2Lat;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Expected Tangent pt 2 latitude: " << soTangentPt2Lat <<
                "  calced: " << sTan2Lat;
                bPassed = false;
            }
        }

        if (sTan2Lon.compare(soTangentPt2Lon) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(soTangentPt2Lon));
            if (IsApprox(dLon, tanPt2.longitude, 1e-10))
            {
                cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Tangent pt 2 longitude: " <<
                soTangentPt2Lon << "  calced: " << sTan2Lon;
            }
            else
            {
                cout << "\n" << soTestId << " failed: Expected Tangent pt 2 longitude: " << soTangentPt2Lon <<
                "  calced: " << sTan2Lon;
                bPassed = false;
            }
        }


    }


    return bPassed;
}

int TestTangentFixedRadiusArc(const string &sFilePath)
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
                if (!ParseTestTangentFixedRadiusArc(sLine))
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
