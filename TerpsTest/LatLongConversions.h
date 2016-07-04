#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////
// Latitude and longitude string and double conversions
double ParseLatitude(std::string sDeg);

double ParseLatitudeBegin(std::string &sString);

double ParseLongitude(std::string szDeg);

double ParseLongitudeBegin(std::string &sString);

std::string Pad0(std::string szOrg, size_t nMinDigits);

double ConvertDmsToDd(std::string const &sDeg, std::string const &sMin, std::string const &sSec);

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
