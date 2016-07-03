/** \file TestCrsIntersect.cpp
*   \brief
*/

/****************************************************************************/
/*  TestCrsIntersect.cpp                                                    */
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

bool ParseTestCrsIntersect(string sString)
{
    bool bPassed = true;
    TrimWhitespace(sString);
    string soTestId, soPt1Lat, soPt1Lon, soPt2Lat, soPt2Lon, soAzAtPt1;
    string soAzFromIntersectionToPt1, soDistToPt1FromIntersection;
    string soAzAtPt2, soAzFromIntersectionToPt2, soDistToPt2FromIntersection;
    string soIntersectionLat, soIntersectionLon;

    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";

        regex pat(sRxPat, flags);

        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,};
        sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            soTestId = *it++;
            soPt1Lat = *it++;
            soPt1Lon = *it++;
            soPt2Lat = *it++;
            soPt2Lon = *it++;
            soAzAtPt1 = *it++;
            soAzFromIntersectionToPt1 = *it++;
            soDistToPt1FromIntersection = *it++;
            soAzAtPt2 = *it++;
            soAzFromIntersectionToPt2 = *it++;
            soDistToPt2FromIntersection = *it++;
            soIntersectionLat = *it++;
            soIntersectionLon = *it++;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }

    LLPoint pt1(Deg2Rad(ParseLatitude(soPt1Lat)), Deg2Rad(ParseLongitude(soPt1Lon)));
    LLPoint pt2(Deg2Rad(ParseLatitude(soPt2Lat)), Deg2Rad(ParseLongitude(soPt2Lon)));
    LLPoint Intsect(Deg2Rad(ParseLatitude(soIntersectionLat)), Deg2Rad(ParseLongitude(soIntersectionLon)));

    double dAzAtPt1 = Deg2Rad(atof(soAzAtPt1.c_str()));
    //  double dAzFromIntersectionToPt1 = Deg2Rad(atof(soAzFromIntersectionToPt1.c_str()));
    //  double dDistToPt1FromIntersection = NmToMeters(atof(soDistToPt1FromIntersection.c_str()));
    double dAzAtPt2 = Deg2Rad(atof(soAzAtPt2.c_str()));
    //  double dAzFromIntersectionToPt2 = Deg2Rad(atof(soAzFromIntersectionToPt2.c_str()));
    //  double dDistToPt2FromIntersection = NmToMeters(atof(soDistToPt2FromIntersection.c_str()));

    LLPoint llIntersect;
    bool bVal = CrsIntersect(pt1, dAzAtPt1, pt2, dAzAtPt2, kTol, llIntersect);

    string sllInterLat = ConvertLatitudeDdToDms(Rad2Deg(llIntersect.latitude));
    string sllInterlon = ConvertLongitudeDdToDms(Rad2Deg(llIntersect.longitude));
    if (sllInterLat.compare(soIntersectionLat) != 0)
    {
        double dLat = Deg2Rad(ParseLatitude(soIntersectionLat));
        if (IsApprox(dLat, llIntersect.latitude, 1e-10))
        {
            cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Test Point Latitude: " <<
            soIntersectionLat << "  calced: " << sllInterLat;
        }
        else
        {
            cout << "\n" << soTestId << " failed: Expected Test Point Latitude: " << soIntersectionLat <<
            "  calced: " << sllInterLat;
            bPassed = false;
        }
    }
    if (sllInterlon.compare(soIntersectionLon) != 0)
    {
        double dLon = Deg2Rad(ParseLongitude(soIntersectionLon));
        if (IsApprox(dLon, llIntersect.longitude, 1e-10))
        {
            cout << "\n" << soTestId << " within rounding tolerance of 1e-10: Input Test Point Longitude: " <<
            soIntersectionLon << "  calced: " << sllInterlon;
        }
        else
        {
            cout << "\n" << soTestId << " failed: Expected Test Point Longitude: " << soIntersectionLon <<
            "  calced: " << sllInterlon;
            bPassed = false;
        }
    }

    return bPassed;
}

int TestCrsIntersect(const string &sFilePath)
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
                if (!ParseTestCrsIntersect(sLine))
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
