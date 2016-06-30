/** \file TestLocusPerpIntersect.cpp
*   \brief
*/

/****************************************************************************/
/*  TestLocusPerpIntersect.cpp                                              */
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

//
//bool ParseLocusTanFixedRadiusArc3(string sLine3, string & sArcDirection, string & sArcCenterLat, string & sArcCenterLon,
//                                string & sTanPt1Lat, string & sTanPt1Lon, string & sTanPt2Lat, string & sTanPt2Lon)
//{
//  bool bPassed = false;
//  TrimWhitespace(sLine3);
//  try
//  {
//      regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;
//
//      string sRxPat = "[,][A-z]+[,]";
//      sRxPat += "([-+]?[1])[,]";
//      sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
//      sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
//      sRxPat += "([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([N/A]+|[0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";
//
//
//      regex pat(sRxPat, flags);
//      int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, };
//      sregex_token_iterator it(sLine3.begin(), sLine3.end(), pat, sub_matches);
//      if(it != sregex_token_iterator())
//      {
//          sArcDirection = *it++;
//          sArcCenterLat = *it++;
//          sArcCenterLon = *it++;
//          sTanPt1Lat = *it++;
//          sTanPt1Lon = *it++;
//          sTanPt2Lat = *it++;
//          sTanPt2Lon = *it++;
//          bPassed = true;
//      }
//  }
//  catch(regex_error & e)
//  {
//      cout << "\n" << e.what();
//      return false;
//  }
//  return bPassed;
//
//}

bool ParseLocusPerpIntercept1(string sLine1, string &sTestId, string &sGeoStartLat, string &sGeoStartLon,
                              string &sGeoEndLat, string &sGeoEndLon,
                              string &sLocusStartLat, string &sLocusStartLon, string &sLocusEndLat,
                              string &sLocusEndLon,
                              string &sLocusStartDist, string &sLocusEndDist, string &sTestPtLat, string &sTestPtLon)
{
    bool bPassed = false;
    TrimWhitespace(sLine1);
    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::perl;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "[0-9A-z ]+[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";

        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,};
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
            sTestPtLat = *it++;
            sTestPtLon = *it++;
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

bool ParseLocusPerpIntercept2(string sLine2, string &sAzFromTestPtToIntercept, string &sDistFromTestPtToIntercept,
                              string &sInterceptLat, string &sInterceptLon)
{
    bool bPassed = false;
    TrimWhitespace(sLine2);

    try
    {
        regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::perl;

        string sRxPat = "[,][0-9A-z ]+[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";


        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4,};
        sregex_token_iterator it(sLine2.begin(), sLine2.end(), pat, sub_matches);
        if (it != sregex_token_iterator())
        {
            sAzFromTestPtToIntercept = *it++;
            sDistFromTestPtToIntercept = *it++;
            sInterceptLat = *it++;
            sInterceptLon = *it++;
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

bool ParseLocusPerpIntercept(string sLine1, string sLine2)
{
    bool bPassed = true;

    string sLocus1GeoStartLat, sLocus1GeoStartLong, sLocus1GeoEndLat, sLocus1GeoEndLong;
    string sLocus1StartLat, sLocus1StartLong, sLocus1EndLat, sLocus1EndLong;
    string sLocus1StartDist, sLocus1EndDist;
    string sTestPtLat, sTestPtLon;

    string sAzFromTestPtToIntercept, sDistFromTestPtToIntercept, sInterceptLat, sInterceptLon;
    string sTestId;

    if (!ParseLocusPerpIntercept1(sLine1, sTestId, sLocus1GeoStartLat, sLocus1GeoStartLong, sLocus1GeoEndLat,
                                  sLocus1GeoEndLong,
                                  sLocus1StartLat, sLocus1StartLong, sLocus1EndLat, sLocus1EndLong, sLocus1StartDist,
                                  sLocus1EndDist, sTestPtLat, sTestPtLon))
        return false;

    if (!ParseLocusPerpIntercept2(sLine2, sAzFromTestPtToIntercept, sDistFromTestPtToIntercept, sInterceptLat,
                                  sInterceptLon))
        return false;


    Locus locus1, locus2;
    locus1.geoStart.Set(Deg2Rad(ParseLatitude(sLocus1GeoStartLat)), Deg2Rad(ParseLongitude(sLocus1GeoStartLong)));
    locus1.geoEnd.Set(Deg2Rad(ParseLatitude(sLocus1GeoEndLat)), Deg2Rad(ParseLongitude(sLocus1GeoEndLong)));
    locus1.locusStart.Set(Deg2Rad(ParseLatitude(sLocus1StartLat)), Deg2Rad(ParseLongitude(sLocus1StartLong)));
    locus1.locusEnd.Set(Deg2Rad(ParseLatitude(sLocus1EndLat)), Deg2Rad(ParseLongitude(sLocus1EndLong)));
    locus1.startDist = NmToMeters(atof(sLocus1StartDist.c_str()));
    locus1.endDist = NmToMeters(atof(sLocus1EndDist.c_str()));

    LLPoint testPt(Deg2Rad(ParseLatitude(sTestPtLat)), Deg2Rad(ParseLongitude(sTestPtLon)));

    LLPoint intersection1, intersection2;
    double dCrsFromPt, dDistFromPt;
    LLPoint intPt;
    int nVal = LocusPerpIntercept(locus1, testPt, dCrsFromPt, dDistFromPt, intPt, kTol);

    if (nVal == 0)
    {
        cout << "\n" << sTestId << "failed: Expected solution, found none.";
        bPassed = false;
    }
    else
    {
        string sPtIntLat = ConvertLatitudeDdToDms(Rad2Deg(intPt.latitude));
        string sPtIntLon = ConvertLongitudeDdToDms(Rad2Deg(intPt.longitude));
        //      double dAzimuth = Rad2Deg(dCrsFromPt);
        //      double dist = dDistFromPt;
        int x = 0;
        x++;

        if (sPtIntLat.compare(sInterceptLat) != 0)
        {
            double dLat = Deg2Rad(ParseLatitude(sInterceptLat));
            if (IsApprox(dLat, intPt.latitude, 1e-10))
                cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intercept Latitude: " <<
                sInterceptLat << " calced: " << sPtIntLat;
            else
            {
                cout << "\n" << sTestId << " failed: Expected Intercept Latitude: " << sInterceptLat << "  calced: " <<
                sPtIntLat;
                bPassed = false;
            }
        }
        if (sPtIntLon.compare(sInterceptLon) != 0)
        {
            double dLon = Deg2Rad(ParseLongitude(sInterceptLon));
            if (IsApprox(dLon, intPt.longitude, 1e-10))
                cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Intercept Longitude: " <<
                sInterceptLon << " calced: " << sPtIntLon;
            else
            {
                cout << "\n" << sTestId << " failed: Expected Intercept Longitude: " << sInterceptLon << "  calced: " <<
                sPtIntLon;
                bPassed = false;
            }
        }

        //      double dInputAz = atof(sAzFromTestPtToIntercept.c_str());
        //      double dInputDist = atof(sDistFromTestPtToIntercept.c_str());
        char szBuffer[20];
        sprintf(szBuffer, "%07.5f", Rad2Deg(dCrsFromPt));
        if (sAzFromTestPtToIntercept.compare(szBuffer) != 0)
        {
            sAzFromTestPtToIntercept += "0";
            if (sAzFromTestPtToIntercept.compare(szBuffer) != 0)
            {
                if (IsApprox(dCrsFromPt, Deg2Rad(atof(sAzFromTestPtToIntercept.c_str())), 1e-8))
                {
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-8: Input Azimuth to IntPt: " <<
                    sAzFromTestPtToIntercept << "  calced: " << szBuffer;
                }
                else
                {
                    cout << "\n" << sTestId << " failed: Input Azimuth to IntPt: " << sAzFromTestPtToIntercept <<
                    "  calced: " << szBuffer;
                    bPassed = false;
                }
            }
        }

        sprintf(szBuffer, "%07.5f", MetersToNm(dDistFromPt));
        if (sDistFromTestPtToIntercept.compare(szBuffer) != 0)
        {
            sDistFromTestPtToIntercept += "0";
            if (sDistFromTestPtToIntercept.compare(szBuffer) != 0)
            {
                if (IsApprox(dDistFromPt, atof(sDistFromTestPtToIntercept.c_str()), 1e-8))
                {
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-8: Input Dist to IntPt: " <<
                    sDistFromTestPtToIntercept << "  calced: " << szBuffer;
                }
                else
                {
                    cout << "\n" << sTestId << " failed: Input Dist to IntPt: " << sDistFromTestPtToIntercept <<
                    "  calced: " << szBuffer;
                    bPassed = false;
                }
            }
        }


    }
    return bPassed;
}


int TestLocusPerpIntercept(const string &sFilePath)
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
                if (!ParseLocusPerpIntercept(sLine1, sLine2))
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
