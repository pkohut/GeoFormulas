/** \file TestLocusCrsAtPoint.cpp
*   \brief 
*/

/****************************************************************************/
/*  TestLocusCrsAtPoint.cpp                                                 */
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

bool ParseLocusCrsAtPointLine2(string sLine2, string & sGeoPtLat, string & sGeoPtLon,
                               string & sLocusAzToTestPt, string & sTestPtAzToGeoPt)
{
    bool bPassed = true;
    TrimWhitespace(sLine2);
    string sTestId, sGeodesicStartLat, sGeodesicStartLong;
    string sGeodesicEndLat, sGeodesicEndLong;
    string sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong;
    string sLocusStartDist, sLocusEndDist, sTestPointLat, sTestPointLong;

    try
    {
        regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

        string sRxPat = "[,][A-z]+[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)";

        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4, };
        sregex_token_iterator it(sLine2.begin(), sLine2.end(), pat, sub_matches);
        if(it == sregex_token_iterator())
            bPassed = false;
        else {
            sGeoPtLat = *it++;
            sGeoPtLon = *it++;
            sLocusAzToTestPt = *it++;
            sTestPtAzToGeoPt = *it++;
            bPassed = true;
        }
    }
    catch(regex_error & e)
    {
        cout << "\n" << e.what();
        return false;
    }
    return bPassed;
}

bool ParseLocusCrsAtPoint(string sLine1, string sLine2)
{   
    bool bPassed = true;
    TrimWhitespace(sLine1);
    string sTestId, sGeodesicStartLat, sGeodesicStartLong, sGeodesicEndLat, sGeodesicEndLong;
    string sLocusStartLat, sLocusStartLong, sLocusEndLat, sLocusEndLong;
    string sLocusStartDist, sLocusEndDist, sTestPointLat, sTestPointLong;
    try
    {
        regex_constants::syntax_option_type flags =  regex_constants::icase | regex_constants::perl;

        string sRxPat = "([a-z]+|[A-Z]+\\d+)[,]";
        sRxPat += "[A-z]+[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])[,]";
        sRxPat += "([-+]?[0-9]*[.]?[0-9]+)[,]([-+]?[0-9]*[.]?[0-9]+)[,]";
        sRxPat += "([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[NS])[,]([0-9]*[:][0-9]*[:][0-9]*[.][0-9]*[WE])";
        regex pat(sRxPat, flags);
        int const sub_matches[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, };
        sregex_token_iterator it(sLine1.begin(), sLine1.end(), pat, sub_matches);
        if(it != sregex_token_iterator())
        {
            sTestId = *it++;
            sGeodesicStartLat = *it++;
            sGeodesicStartLong = *it++;
            sGeodesicEndLat = *it++;
            sGeodesicEndLong = *it++;
            sLocusStartLat = *it++;
            sLocusStartLong = *it++;
            sLocusEndLat = *it++;
            sLocusEndLong = *it++;
            sLocusStartDist = *it++;
            sLocusEndDist = *it++;
            sTestPointLat = *it++;
            sTestPointLong = *it++;
        }
    }
    catch(regex_error & e)
    {
        cout << "\n" << e.what();
        return false;
    }

    Locus locus;
    locus.geoStart.Set(Deg2Rad(ParseLatitude(sGeodesicStartLat)), Deg2Rad(ParseLongitude(sGeodesicStartLong)));
    locus.geoEnd.Set(Deg2Rad(ParseLatitude(sGeodesicEndLat)), Deg2Rad(ParseLongitude(sGeodesicEndLong)));
    locus.locusStart.Set(Deg2Rad(ParseLatitude(sLocusStartLat)), Deg2Rad(ParseLongitude(sLocusStartLong)));
    locus.locusEnd.Set(Deg2Rad(ParseLatitude(sLocusEndLat)), Deg2Rad(ParseLongitude(sLocusEndLong)));
    locus.startDist = NmToMeters(atof(sLocusStartDist.c_str()));
    locus.endDist = NmToMeters(atof(sLocusEndDist.c_str()));

    LLPoint testPt(Deg2Rad(ParseLatitude(sTestPointLat)), Deg2Rad(ParseLongitude(sTestPointLong)));
    
    LLPoint  geoPt;
    double dPerpCrs;
    double dLocusCrs = LocusCrsAtPoint(locus, testPt, geoPt, dPerpCrs, 1e-3);
    if(dLocusCrs < 0.0)
        bPassed = false;
    else
    {
        string soGeoPtLat, soGeoPtLon, soLocusAzToTestPt, soTestPtAzToGeoPt;
        if(!ParseLocusCrsAtPointLine2(sLine2, soGeoPtLat, soGeoPtLon, soLocusAzToTestPt, soTestPtAzToGeoPt))
            bPassed = false;
        else {
            string sGeoPtLat = ConvertLatitudeDdToDms(Rad2Deg(geoPt.latitude));
            if(soGeoPtLat.compare(sGeoPtLat) != 0)
            {
                double dLat = Deg2Rad(ParseLatitude(soGeoPtLat));
                if(IsApprox(dLat, geoPt.latitude, 1e-10))
                {
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Input Geodesic Point Latitude: " << soGeoPtLat << "  calced: " << sGeoPtLat;
                } else {
                    cout << "\n" << sTestId << " failed: Expected Computed Geodesic Point Latitude: " << soGeoPtLat << "  calced: " << sGeoPtLat;
                    bPassed = false;
                }
            }

            string sGeoPtLon = ConvertLongitudeDdToDms(Rad2Deg(geoPt.longitude));
            if(soGeoPtLon.compare(sGeoPtLon) != 0)
            {
                double dLon = Deg2Rad(ParseLongitude(soGeoPtLon));
                if(IsApprox(dLon, geoPt.longitude, 1e-10))
                {
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-10: Input Geodesic Point Longitude: " << soGeoPtLon << "  calced: " << sGeoPtLon;
                } else {
                    cout << "\n" << sTestId << " failed: Expected Computed Geodesic Point Longitude: " << soGeoPtLon << "  calced: " << sGeoPtLon;
                    bPassed = false;
                }
            }

            char szBuffer[20];
            sprintf(szBuffer, "%07.5f", Rad2Deg(dPerpCrs));
            if(soLocusAzToTestPt.compare(szBuffer) != 0)
            {
                if(IsApprox(dPerpCrs, Deg2Rad(atof(soLocusAzToTestPt.c_str())), 1e-8))
                {
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-8: Input Locus Azimuth at TestPt: " << soLocusAzToTestPt << "  calced: " << szBuffer;
                }
                else
                {
                    cout << "\n" << sTestId << " failed: Input Locus Azimuth at TestPt: " << soLocusAzToTestPt << "  calced: " << szBuffer;
                    bPassed = false;
                }
            }

            sprintf(szBuffer, "%07.5f", Rad2Deg(dLocusCrs));
            if(soTestPtAzToGeoPt.compare(szBuffer) != 0)
            {
                if(IsApprox(dLocusCrs, Deg2Rad(atof(soTestPtAzToGeoPt.c_str())), 1e-8))
                {
                    cout << "\n" << sTestId << " within rounding tolerance of 1e-8: Input TestPt Azimuth to GeoPt: " << soTestPtAzToGeoPt << "  calced: " << szBuffer;
                }
                else
                {
                    cout << "\n" << sTestId << " failed: Input TestPt Azimuth to GeoPt: " << soTestPtAzToGeoPt << "  calced: " << szBuffer;
                    bPassed = false;
                }
            }
        }
    }

    
    
    
    //LLPoint  geoPt;
    //double dPerpCrs;

    //CGeoCalcs geo1;
    //double dLocusCrs = geo1.LocusCrsAtPoint(locus, testPt, geoPt, dPerpCrs, 1e-3);

    //dPerpCrs = Rad2Deg(dPerpCrs);
    //dLocusCrs = Rad2Deg(dLocusCrs);



    //char szBuffer[20];
    //sprintf(szBuffer, "%07.6f", dDist1);
    //if(sComputedArcLength.compare(szBuffer) != 0)
    //{
    //  if(szBuffer[strlen(szBuffer) - 1] == '0')
    //  {
    //      szBuffer[strlen(szBuffer) - 1] = '\0';
    //  }
    //  if(sComputedArcLength.compare(szBuffer) != 0)
    //  {
    //      if(IsApprox(dDist1, atof(sComputedArcLength.c_str()), 0.5e-8))
    //      {
    //          cout << "\n" << sTestId << " within rounding tolerance of 0.5e-8: Input Computed Arc Length: " << sComputedArcLength << "  calced: " << szBuffer;
    //      }
    //      else
    //      {
    //          cout << "\n" << sTestId << "failed: Expected Computed Arc Length: " << sComputedArcLength << "  calced: " << szBuffer;
    //          bPassed = false;
    //      }
    //  }

    //}

    //sprintf(szBuffer, "%07.6f", dDist2);
    //if(sDirectComputedArcLength.compare(szBuffer) != 0)
    //{
    //  if(szBuffer[strlen(szBuffer) - 1] == '0')
    //  {
    //      szBuffer[strlen(szBuffer) - 1] = '\0';
    //  }
    //  if(sDirectComputedArcLength.compare(szBuffer) != 0)
    //  {
    //      if(IsApprox(dDist1, atof(sComputedArcLength.c_str()), 0.5e-8))
    //      {
    //          cout << "\n" << sTestId << " within rounding tolerance of 0.5e-8: Input Direct Computed Arc Length: " << sDirectComputedArcLength << "  calced: " << szBuffer;
    //      }
    //      else
    //      {
    //          cout << "\n" << sTestId << "failed: Expected Direct Computed Arc Length: " << sDirectComputedArcLength << "  calced: " << szBuffer;
    //          bPassed = false;
    //      }
    //  }       
    //}

    return bPassed; 
}


int TestLocusCrsAtPoint(const string & sFilePath)
{
    ifstream infile;
    infile.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
    int nCount = 0;
    int nCommentCount = 0;
    bool bPassed = true;
    try
    {
        string sLine1, sLine2;
        infile.open(sFilePath.c_str(), ifstream::in);

        while(!infile.eof())
        {
            getline(infile, sLine1);            
            if(sLine1.at(0) == '#')
            {
                nCommentCount++;
            }
            else
            {
                getline(infile, sLine2);
                if(!ParseLocusCrsAtPoint(sLine1, sLine2))
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