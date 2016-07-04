/** \file LatLongConversions.cpp
*   \brief
*/

/****************************************************************************/
/*  LatLongConversions.cpp                                                  */
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
#include <iomanip>
#include <regex>
#include <sstream>
#include "LatLongConversions.h"
#include "Conversions.h"


using namespace std;

double ParseLatLongBegin(bool bIsLatitude, string & sString)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;
    smatch matchResults;

    string rxLatLong = "([NS])";
    int nAngle = 180;
    if(!bIsLatitude)
    {
        rxLatLong = "([EW])";
        nAngle = 360;
    }


    string sPattern = "[:. ]";
    regex pat(sPattern, flags);
    sString = regex_replace(sString, pat, " ");

    // Split the string into it's sub string tokens based on sPattern below.
    // Define the sub string match patterns that will be valid for the iterator
    // Note: If sPattern is changed then make sure the sub_matches are changed
    // accordingly too.

    int const sub_matches[] = {1, 2, 3, 4, 5, 6};
    sPattern = rxLatLong + "(\\d+)[ ](\\d+)[ ](\\d+)[ ](\\d+)";
    pat.assign(sPattern, flags);
    sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
    if (it == sregex_token_iterator())
    {
        sPattern = rxLatLong + "(\\d+)[ ](\\d+)[ ](\\d+)()";
        pat.assign(sPattern, flags);
        it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
        if (it == sregex_token_iterator())
        {
            sPattern = rxLatLong + "(\\d+)[ ](\\d+)()()";
            pat.assign(sPattern, flags);
            it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
            if (it == sregex_token_iterator())
            {
                sPattern = rxLatLong + "(\\d+)()()()";
                pat.assign(sPattern, flags);
                it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
                if (it == sregex_token_iterator())
                    throw CRNavConversionException(
                            string("Value out of range, are you passing an angle greater than ")
                            + to_string(nAngle / 2) + " degrees?");
            }
        }
    }

    // Get each piece of the substring to build the final string that
    // can be converted to decimal

    // Make sure we convert 'S' and 'W' and '-' to '-'
    // Don't need to do this if 'N' or 'E' or '+'
    int dInverse = 1;
    if(bIsLatitude)
    {
        if ((*it).str() == "S" || (*it).str() == "s" || (*it).str() == "-")
            dInverse = -1;
    }
    else if((*it).str() == "W" || (*it).str() == "w" || (*it).str() == "-")
    {
        dInverse = -1;
    }

    it++;

    double dDeg = dInverse * atof(string(*it++).c_str());
    double dMin = atof(string(*it++).c_str());
    double dSec = atof(string(*it++).c_str());
    dSec += atof((string(".") + string(*it++)).c_str());

    double dVal = ConvertDmsToDd(dDeg, dMin, dSec);
    if (dVal > double(nAngle) || dVal < (double)-nAngle)
    {
        if (bIsLatitude)
            throw (CRNavConversionException("Latitude > 90.0 or < -90.0"));
        throw (CRNavConversionException("Longitude > 180.0 or < -180.0"));
    }
    return dVal;
}


double ParseLatitude(string sDeg)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;
    trim(sDeg);
    string sPattern = "[+-]+|[sn]+";
    smatch what;
    regex pat(sPattern, flags);
    if (!regex_search(sDeg, what, pat))
    {
        // did not find pattern so assume value is positive and North
        // and stuff 'N' at the beginning of the string
        sDeg = "N" + sDeg;
    }

    // Replace all '+' 'n' and 'N' with 'N'
    pat.assign("[+N]", flags);
    sDeg = regex_replace(sDeg, pat, "N");

    // Replace all '-' 's' and 'S' with 'S'
    pat.assign("[-S]", flags);
    sDeg = regex_replace(sDeg, pat, "S");

    // determine if pattern above was found at the beginning or
    // end of the string.  If found at the end the swap it to the
    // beginning.
    size_t pos = (size_t) what.position();
    if (pos == sDeg.length() - 1)
    {
        sDeg = sDeg[pos] + sDeg.substr(0, pos);
    }

    // String has been normalized continue on with the parsing
    return ParseLatLongBegin(true, sDeg);
}


double ParseLongitude(string sDeg)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::ECMAScript;
    trim(sDeg);
    string sPattern = "[+-]+|[ew]+";
    smatch what;
    regex pat(sPattern, flags);
    if (!regex_search(sDeg, what, pat))
    {
        // did not find pattern so assume value is positive and East
        // and stuff 'E' at the beginning of the string
        sDeg = "E" + sDeg;
    }

    // Replace all '+' 'n' and 'E' with 'E'
    pat.assign("[+E]", flags);
    sDeg = regex_replace(sDeg, pat, "E");

    // Replace all '-' 'w' and 'W' with 'W'
    pat.assign("[-W]", flags);
    sDeg = regex_replace(sDeg, pat, "W");

    // determine if pattern above was found at the beginning or
    // end of the string.  If found at the end the swap it to the
    // beginning.
    size_t pos = (size_t) what.position();
    if (pos == sDeg.length() - 1)
    {
        sDeg = sDeg[pos] + sDeg.substr(0, pos);
    }

    // String has been normalized continue on with the parsing
    //return ParseLongitudeBegin(sDeg);
    return ParseLatLongBegin(false, sDeg);
}


// PadString will fill the beginning of the string with
// value of c as needed until the length of szOrg is = nMinDigits
string PadString(string szOrg, char c, size_t nMinDigits)
{
    if (nMinDigits - szOrg.length() > 0)
        return string(nMinDigits - szOrg.length(), c).append(szOrg);
    return szOrg;
}

double ConvertDmsToDd(double const &dDeg, double const &dMin, double const &dSec)
{
    if (dDeg < 0.0)
        return (-(fabs(dDeg) + (dMin / 60.0) + (dSec / 3600.0)));
    return (dDeg + (dMin / 60.0) + (dSec / 3600.0));
}

string ConvertDdToDms(double const &dDeg)
{
    int nDegrees = (int) fabs(dDeg);
    double dMinutes = fabs((dDeg - nDegrees) * 60);
    double nSeconds = fabs((dMinutes - (int) dMinutes) * 60);

    stringstream ss;
    ss.setf(ios::fixed, ios::floatfield);
    ss.precision(5);
    ss << nDegrees << ":" <<
            setfill('0') << setw(2) << (int) dMinutes << ":" <<
            setfill('0') << setw(8) << nSeconds;

    return ss.str();
}


string ConvertLatitudeDdToDms(double const &dDeg)
{
    bool bIsNeg = dDeg < 0.0;
    double dVal = fabs(dDeg);
    if (dVal > 90.0)
    {
        dVal = 180.0 - dVal;
        bIsNeg = !bIsNeg;
    }
    return (ConvertDdToDms(dVal) + (bIsNeg ? "S" : "N"));
}

string ConvertLongitudeDdToDms(double const &dDeg)
{
    bool bIsNeg = dDeg < 0.0;
    double dVal = fabs(dDeg);
    if (dVal > 180.0)
    {
        dVal = 360.0 - dVal;
        bIsNeg = !bIsNeg;
    }
    return (ConvertDdToDms(dVal) + (bIsNeg ? "W" : "E"));
}
