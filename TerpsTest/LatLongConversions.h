#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////
// Latitude and longitude string and double conversions
double ParseLatLongBegin(bool bIsLatitude, std::string &sString);

double ParseLatitude(std::string sDeg);

double ParseLongitude(std::string sDeg);

std::string PadString(std::string szOrg, char c, size_t nMinDigits);

double ConvertDmsToDd(double const &dDeg, double const &dMin, double const &dSec);

std::string ConvertDdToDms(double const &dDeg);

std::string ConvertLatitudeDdToDms(double const &dDeg);

std::string ConvertLongitudeDdToDms(double const &dDeg);


inline std::string &ltrim(std::string &s, const char *t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline std::string &rtrim(std::string &s, const char *t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline std::string &trim(std::string &s, const char *t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}
