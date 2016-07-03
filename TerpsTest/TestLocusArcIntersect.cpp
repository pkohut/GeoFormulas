/** \file TestLocusArcIntersect.cpp
*   \brief
*/

/****************************************************************************/
/*  TestLocusArcIntersect.cpp                                               */
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

bool ParseLocusArcIntersect3(string sLine3, string &sIntersection1Lat, string &sIntersection1Lon,
                             string &sIntersection2Lat, string &sIntersection2Lon)
{
    bool bPassed = false;
    TrimWhitespace(sLine3);
    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "[,][A-z]+[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";

        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4,};
        sregex_token_iterator it(sLine3.begin(), sLine3.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            sIntersection1Lat = *it++;
            sIntersection1Lon = *it++;
            sIntersection2Lat = *it++;
            sIntersection2Lon = *it++;
            bPassed = true;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }
    return bPassed;

}

bool ParseLocusArcIntersect1(string sLine1, string &sTestId, string &sGeoStartLat, string &sGeoStartLon,
                             string &sGeoEndLat, string &sGeoEndLon,
                             string &sLocusStartLat, string &sLocusStartLon, string &sLocusEndLat, string &sLocusEndLon,
                             string &sLocusStartDist, string &sLocusEndDist)
{
    bool bPassed = false;
    TrimWhitespace(sLine1);
    //string sTestId, sGeodesicStartLat, sGeodesicStartLong, sGeodesicEndLat, sGeodesicEndLong;
    //string sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong;
    //string sLocusStartDist, sLocusEndDist, sTestPointLat, sTestPointLong;
    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "[A-z ]+[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)";

        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        sregex_token_iterator it(sLine1.begin(), sLine1.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            sTestId = *it++;
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
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }
    return bPassed;
}

bool ParseLocusArcIntersect2(string sLine2, string &sArcCenterLat, string &sArcCenterLon, string &sArcRadius)
{
    bool bPassed = true;
    TrimWhitespace(sLine2);

    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;

        string sRxPat = "[,][A-z ]+[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+).";

        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3,};
        sregex_token_iterator it(sLine2.begin(), sLine2.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            sArcCenterLat = *it++;
            sArcCenterLon = *it++;
            sArcRadius = *it++;
        }
    }
    catch (regex_error &e)
    {
        cout << "\n" << e.what();
        return false;
    }

    return bPassed;
}

bool ParseLocusArcIntersect(string sLine1, string sLine2, string sLine3)
{
    bool bPassed = true;

    string sLocusGeoStartLat, sLocusGeoStartLong, sLocusGeoEndLat, sLocusGeoEndLong;
    string sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong;
    string sLocusStartDist, sLocusEndDist;
    string sIntersection1Lat, sIntersection1Long, sIntersection2Lat, sIntersection2Long;
    string sArcCenterLat, sArcCenterLon, sArcRadius;
    string sTestId;

    if (!ParseLocusArcIntersect1(sLine1, sTestId, sLocusGeoStartLat, sLocusGeoStartLong, sLocusGeoEndLat,
                                 sLocusGeoEndLong,
                                 sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong, sLocusStartDist,
                                 sLocusEndDist))
        return false;

    if (!ParseLocusArcIntersect2(sLine2, sArcCenterLat, sArcCenterLon, sArcRadius))
        return false;

    if (!ParseLocusArcIntersect3(sLine3, sIntersection1Lat, sIntersection1Long, sIntersection2Lat, sIntersection2Long))
        return false;

    Locus locus;
    locus.geoStart.Set(Deg2Rad(ParseLatitude(sLocusGeoStartLat)), Deg2Rad(ParseLongitude(sLocusGeoStartLong)));
    locus.geoEnd.Set(Deg2Rad(ParseLatitude(sLocusGeoEndLat)), Deg2Rad(ParseLongitude(sLocusGeoEndLong)));
    locus.locusStart.Set(Deg2Rad(ParseLatitude(sLocusStartLat)), Deg2Rad(ParseLongitude(sLocusStartLong)));
    locus.locusEnd.Set(Deg2Rad(ParseLatitude(sLocusEndLat)), Deg2Rad(ParseLongitude(sLocusEndLong)));
    locus.startDist = NmToMeters(atof(sLocusStartDist.c_str()));
    locus.endDist = NmToMeters(atof(sLocusEndDist.c_str()));

    LLPoint arcCenter(Deg2Rad(ParseLatitude(sArcCenterLat)), Deg2Rad(ParseLongitude(sArcCenterLon)));
    double arcRadius = NmToMeters(atof(sArcRadius.c_str()));

    LLPoint intersection1, intersection2;
    if (sTestId.compare("test61") == 0)
    {
        int x = 0;
        x++;
    }
    int nVal = LocusArcIntersect(locus, arcCenter, arcRadius, intersection1, intersection2, kTol, kEps);
    if (nVal == 0)
    {
        if (sIntersection1Lat.compare("N/A") != 0 || sIntersection2Lat.compare("N/A") != 0)
        {
            //          string sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intersection1.latitude));
            //          string sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intersection1.longitude));
            cout << "\n" << sTestId << "failed: Expected at least one solution, none found";
            bPassed = false;
        }
    }
    else if (nVal == 1)
    {
        if (sIntersection1Lat.compare("N/A") == 0 && sIntersection2Lat.compare("N/A") == 0)
        {
            cout << "\n" << sTestId << "failed: Expected no solutions. Found only 1 solution";
            bPassed = false;
        }
        else if (sIntersection1Lat.compare("N/A") != 0 && sIntersection2Lat.compare("N/A") != 0)
        {
            cout << "\n" << sTestId << "failed: Expected 2 solutions. Found only 1 solution";
            bPassed = false;
        }
        else
        {
            string sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intersection1.latitude));
            string sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intersection1.longitude));
            if (sPtIntLat.compare(sIntersection1Lat) != 0)
            {
                double dLat = Deg2Rad(ParseLatitude(sIntersection1Lat));
                if (IsApprox(dLat, intersection1.latitude, 1e-10))
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect 1 Latitude: " <<
                    sIntersection1Lat << " calced: " << sPtIntLat;
                else
                {
                    cout << "\n" << sTestId << " failed: Expected Intersect 1 latitude: " << sIntersection1Lat <<
                    "  calced: " << sPtIntLat;
                    bPassed = false;
                }
            }
            if (sPtIntLon.compare(sIntersection1Long) != 0)
            {
                double dLon = Deg2Rad(ParseLongitude(sIntersection1Long));
                if (IsApprox(dLon, intersection1.longitude, 1e-10))
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect 1 Longitude: " <<
                    sIntersection1Long << " calced: " << sPtIntLon;
                else
                {
                    cout << "\n" << sTestId << " failed: Expected Intersect 1 longitude: " << sIntersection1Long <<
                    "  calced: " << sPtIntLon;
                    bPassed = false;
                }
            }
        }
    }
    else
    {
        string sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intersection1.latitude));
        string sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intersection1.longitude));
        if (sPtIntLat.compare(sIntersection1Lat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(sIntersection1Lat));
            if (IsApprox(dLat, intersection1.latitude, 1e-10))
                cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect 1 Latitude: " <<
                sIntersection1Lat << " calced: " << sPtIntLat;
            else
            {
                cout << "\n" << sTestId << " failed: Expected Intersect 1 latitude: " << sIntersection1Lat <<
                "  calced: " << sPtIntLat;
                bPassed = false;
            }
        }
        if (sPtIntLon.compare(sIntersection1Long) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(sIntersection1Long));
            if (IsApprox(dLon, intersection1.longitude, 1e-10))
                cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect 1 Longitude: " <<
                sIntersection1Long << " calced: " << sPtIntLon;
            else
            {
                cout << "\n" << sTestId << " failed: Expected Intersect 1 longitude: " << sIntersection1Long <<
                "  calced: " << sPtIntLon;
                bPassed = false;
            }
        }

        sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intersection2.latitude));
        sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intersection2.longitude));
        if (sPtIntLat.compare(sIntersection2Lat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(sIntersection2Lat));
            if (IsApprox(dLat, intersection2.latitude, 1e-10))
                cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect 2 Latitude: " <<
                sIntersection2Lat << " calced: " << sPtIntLat;
            else
            {
                cout << "\n" << sTestId << " failed: Expected Intersect 2 latitude: " << sIntersection2Lat <<
                "  calced: " << sPtIntLat;
                bPassed = false;
            }
        }
        if (sPtIntLon.compare(sIntersection2Long) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(sIntersection2Long));
            if (IsApprox(dLon, intersection2.longitude, 1e-10))
                cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intersect 2 Longitude: " <<
                sIntersection2Long << " calced: " << sPtIntLon;
            else
            {
                cout << "\n" << sTestId << " failed: Expected Intersect 2 longitude: " << sIntersection2Long <<
                "  calced: " << sPtIntLon;
                bPassed = false;
            }
        }


    }
    return bPassed;
}


int TestLocusArcIntersect(const string &sFilePath)
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

        while (!infile.eof())
        {
            getline(infile, sLine1);
            if (sLine1.at(0) == '#')
            {
                nCommentCount++;
            }
            else
            {
                getline(infile, sLine2);
                getline(infile, sLine3);
                if (!ParseLocusArcIntersect(sLine1, sLine2, sLine3))
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
