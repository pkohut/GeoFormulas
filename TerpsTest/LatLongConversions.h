#pragma once
#include <string>

//////////////////////////////////////////////////////////////////////////
// Latitude and longitude string and double conversions
double ParseLatitude(std::string szDeg);
double ParseLatitudeBegin(std::string & sString);
double ParseLongitude(std::string szDeg);
double ParseLongitudeBegin(std::string & sString);

std::string Pad0(std::string szOrg, size_t nMinDigits);
double ConvertDmsToDd(std::string const & sDeg, std::string const & sMin, std::string const & sSec);
double ConvertDmsToDd(double const & dDeg, double const & dMin, double const & dSec);
std::string ConvertDdToDms(double const & dDeg);
void TrimWhitespace(std::string & szString);
std::string ConvertLatitudeDdToDms(double const & dDeg);
std::string ConvertLongitudeDdToDms(double const & dDeg);