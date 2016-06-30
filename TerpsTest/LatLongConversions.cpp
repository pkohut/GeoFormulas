/** \file LatLongConversions.cpp
*   \brief
*/

/****************************************************************************/
/*  LatLongConversions.cpp                                                  */
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
#include <boost/regex.hpp>
#include "LatLongConversions.h"
#include "Conversions.h"

using namespace boost;
using namespace std;

void TrimWhitespace(string &szString)
{
    regex pat("^[ \t]+|[ \t]+$");
    szString = regex_replace(szString, pat, "");
}

double ParseLatitude(string szDeg)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::perl;
    TrimWhitespace(szDeg);
    string sPattern = "[+-]|[sn]";
    smatch what;
    regex pat(sPattern, flags);
    if (!regex_search(szDeg, what, pat))
    {
        // did not find pattern so assume value is positive and North
        // and stuff 'N' at the beginning of the string
        szDeg = "N" + szDeg;
        regex_search(szDeg, what, pat);
    }

    // Replace all '+' 'n' and 'N' with 'N'
    pat.assign("[+N]", flags);
    szDeg = regex_replace(szDeg, pat, "N");

    // Replace all '-' 's' and 'S' with 'S'
    pat.assign("[-S]", flags);
    szDeg = regex_replace(szDeg, pat, "S");

    // determine if pattern above was found at the beginning or
    // end of the string.  If found at the end the swap it to the
    // beginning.
    size_t pos = what.position();
    if (pos == szDeg.length() - 1)
    {
        szDeg = szDeg[pos] + szDeg.substr(0, pos);
    }

    // String has been normalized continue on with the parsing
    return ParseLatitudeBegin(szDeg);
}


double ParseLatitudeBegin(string &sString)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::perl;
    string sPattern = "[:. ]";

    regex pat(sPattern, flags);
    smatch matchResults;
    sString = regex_replace(sString, pat, " ");
    pat.assign(" ", flags);

    //  if(!regex_match(sString, matchResults, pat))
    //      throw CRNavConversionException("regex match not found");

    // Split the string into it's sub string tokens based on sPattern below.
    // Define the sub string match patterns that will be valid for the iterator
    // Note: If sPattern is changed then make sure the sub_matches are changed
    // accordingly too.

    int const sub_matches[] = {1, 2, 3, 4, 5, 6};
    sPattern = "([NS])(\\d+)[ ](\\d+)[ ](\\d+)[ ](\\d+)";
    pat.assign(sPattern, flags);
    sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
    if (it == sregex_token_iterator())
    {
        sPattern = "([NS])(\\d+)[ ](\\d+)[ ](\\d+)()";
        pat.assign(sPattern, flags);
        it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
        if (it == sregex_token_iterator())
        {
            sPattern = "([NS])(\\d+)[ ](\\d+)()()";
            pat.assign(sPattern, flags);
            it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
            if (it == sregex_token_iterator())
            {
                sPattern = "([NS])(\\d+)()()()";
                pat.assign(sPattern, flags);
                it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
                if (it == sregex_token_iterator())
                    throw CRNavConversionException(
                            "Value out of range, are you passing an angle greater than 90 degrees?");
            }
        }
    }

    // Get each piece of the substring to build the final string that
    // can be converted to decimal
    string sneg, sdeg, smin, ssec;
    // Make sure we convert 'S' and '-' to '-'
    // Don't need to do this if 'N' or '+'
    if ((*it).str().compare("S") == 0 || (*it).str().compare("s") == 0 || (*it).str().compare("-") == 0)
        sneg += "-";

    it++;

    sdeg = *it++;
    smin = *it++;
    ssec = *it++;
    //  ssec += "." + *it++;
    double dDeg = atof(sdeg.c_str());
    double dMin = atof(smin.c_str());
    double dSec = atof(ssec.c_str());
    //  if(dDeg > 90.0 || dMin > 59.0 || dSec > 59.0)
    //      throw(CRNavConversionException("Degrees > 90 or Minutes > 59 or Seconds > 59"));

    ssec += "." + *it++;
    dSec = atof(ssec.c_str());

    double dVal;
    if (sneg[0] == '-')
        dVal = ConvertDmsToDd(-dDeg, dMin, dSec);
    else
        dVal = ConvertDmsToDd(dDeg, dMin, dSec);
    if (dVal > 90.0 || dVal < -90.0)
        throw (CRNavConversionException("Latitude > 90.0 or < -90.0"));
    return dVal;
}


double ParseLongitude(string szDeg)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::perl;
    TrimWhitespace(szDeg);
    string sPattern = "[+-]|[ew]";
    smatch what;
    regex pat(sPattern, flags);
    if (!regex_search(szDeg, what, pat))
    {
        // did not find pattern so assume value is positive and North
        // and stuff 'N' at the beginning of the string
        szDeg = "E" + szDeg;
        regex_search(szDeg, what, pat);
    }

    // Replace all '+' 'n' and 'N' with 'N'
    pat.assign("[+E]", flags);
    szDeg = regex_replace(szDeg, pat, "E");

    // Replace all '-' 's' and 'S' with 'S'
    pat.assign("[-W]", flags);
    szDeg = regex_replace(szDeg, pat, "W");

    // determine if pattern above was found at the beginning or
    // end of the string.  If found at the end the swap it to the
    // beginning.
    size_t pos = what.position();
    if (pos == szDeg.length() - 1)
    {
        szDeg = szDeg[pos] + szDeg.substr(0, pos);
    }

    // String has been normalized continue on with the parsing
    return ParseLongitudeBegin(szDeg);
}


double ParseLongitudeBegin(string &sString)
{
    regex_constants::syntax_option_type flags = regex_constants::icase | regex_constants::perl;
    string sPattern = "[:. ]";

    regex pat(sPattern, flags);
    smatch matchResults;
    sString = regex_replace(sString, pat, " ");
    pat.assign(" ", flags);

    //  if(!regex_match(sString, matchResults, pat))
    //      throw CRNavConversionException("regex match not found");

    // Split the string into it's sub string tokens based on sPattern below.
    // Define the sub string match patterns that will be valid for the iterator
    // Note: If sPattern is changed then make sure the sub_matches are changed
    // accordingly too.

    int const sub_matches[] = {1, 2, 3, 4, 5, 6};
    sPattern = "([EW])(\\d+)[ ](\\d+)[ ](\\d+)[ ](\\d+)";
    pat.assign(sPattern, flags);
    sregex_token_iterator it(sString.begin(), sString.end(), pat, sub_matches);
    if (it == sregex_token_iterator())
    {
        sPattern = "([EW])(\\d+)[ ](\\d+)[ ](\\d+)()";
        pat.assign(sPattern, flags);
        it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
        if (it == sregex_token_iterator())
        {
            sPattern = "([EW])(\\d+)[ ](\\d+)()()";
            pat.assign(sPattern, flags);
            it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
            if (it == sregex_token_iterator())
            {
                sPattern = "([EW])(\\d+)()()()";
                pat.assign(sPattern, flags);
                it = sregex_token_iterator(sString.begin(), sString.end(), pat, sub_matches);
                if (it == sregex_token_iterator())
                    throw CRNavConversionException(
                            "Value out of range, are you passing an angle greater than 180 degrees?");
            }
        }
    }

    // Get each piece of the substring to build the final string that
    // can be converted to decimal
    string sneg, sdeg, smin, ssec;
    // Make sure we convert 'W' and '-' to '-'
    // Don't need to do this if 'E' or '+'
    if ((*it).str().compare("W") == 0 || (*it).str().compare("w") == 0 || (*it).str().compare("-") == 0)
        sneg += "-";

    it++;

    sdeg = *it++;
    smin = *it++;
    ssec = *it++;
    //  ssec += "." + *it++;
    double dDeg = atof(sdeg.c_str());
    double dMin = atof(smin.c_str());
    double dSec = atof(ssec.c_str());
    //  if(dDeg > 180.0 || dMin > 59.0 || dSec > 59.0)
    //      throw(CRNavConversionException("Degrees > 180 or Minutes > 59 or Seconds > 59"));

    ssec += "." + *it++;
    dSec = atof(ssec.c_str());

    double dVal;
    if (sneg[0] == '-')
        dVal = ConvertDmsToDd(-dDeg, dMin, dSec);
    else
        dVal = ConvertDmsToDd(dDeg, dMin, dSec);
    if (dVal > 180.0 || dVal < -180.0)
        throw (CRNavConversionException("Longitude > 180.0 or < -180.0"));
    return dVal;
}


// Pad0 will pad to the beginning of the string as many
// '0' as needed until the length of szOrg is = nMinDigits
string Pad0(string szOrg, size_t nMinDigits)
{
    for (size_t pos = szOrg.length(); pos < nMinDigits; pos++)
    {
        szOrg = "0" + szOrg;
    }
    return szOrg;
}

double ConvertDmsToDd(double const &dDeg, double const &dMin, double const &dSec)
{
    if (dDeg < 0.0)
        return (-(fabs(dDeg) + (dMin / 60.0) + (dSec / 3600.0)));
    return (dDeg + (dMin / 60.0) + (dSec / 3600.0));
}

double ConvertDmsToDd(string const &sDeg, string const &sMin, string const &sSec)
{
    double dNeg = atof(sDeg.c_str());
    double dDeg = fabs(dNeg);
    double dMin = atof(sMin.c_str());
    double dSec = atof(sSec.c_str());
    if (dNeg < 0.0)
        return ConvertDmsToDd(-dDeg, dMin, dSec);
    return ConvertDmsToDd(dDeg, dMin, dSec);
}

string ConvertDdToDms(double const &dDeg)
{
    char szBuffer[25];
    int nDegrees = (int) dDeg;
    double dMinutes = (dDeg - nDegrees) * 60;
    double nSeconds = (dMinutes - (int) dMinutes) * 60;
    sprintf(szBuffer, "%d:%02d:%08.5f", nDegrees, (int) fabs(dMinutes), fabs(nSeconds));
    return string(szBuffer);
}

string ConvertLatitudeDdToDms(double const &dDeg)
{
    bool bIsNeg = dDeg < 0.0;
    double dVal = fabs(dDeg);
    if (dVal > 90.0)
        dVal = 180.0 - dVal;
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
