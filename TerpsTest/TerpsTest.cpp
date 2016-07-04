/** \file TerpsTest.cpp
*   \brief
*/

/****************************************************************************/
/*  TerpsTest.cpp                                                           */
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
#include <assert.h>
#include <bitset>
#include <cstdlib>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>

#include "LatLongConversions.h"
#include "Conversions.h"
#include "geo_formulas_configure.h"
#include "GeoFormulas.h"

using namespace std;

extern int TestDirect(const string &sFilePath);

extern int TestInverse(const string &sFilePath);

extern int TestPtIsOnGeodesic(const string &sFilePath);

extern int TestPtIsOnArc(const string &sFilePath);

extern int TestDiscretizedArcLength(const string &sFilePath);

extern int TestPerpIntercept(const string &sFilePath);

extern int TestPtIsOnLocus(const string &sFilePath);

extern int TestLocusCrsAtPoint(const string &sFilePath);

extern int TestCrsIntersect(const string &sFilePath);

extern int TestArcIntersect(const string &sFilePath);

extern int TestGeodesicArcIntersect(const string &sFilePath);

extern int TestTangentFixedRadiusArc(const string &sFilePath);

extern int TestGeoLocusIntersect(const string &sFilePath);

extern int TestLocusArcIntersect(const string &sFilePath);

extern int TestLocusIntersect(const string &sFilePath);

extern int TestLocusTanFixedRadiusArc(const string &sFilePath);

extern int TestLocusPerpIntercept(const string &sFilePath);

extern int TestPointToArcTangents(const string &sFilePath);

extern int TestPerpTangentPoints(const string &sFilePath);

// @formatter:off
bool TestLatitudeParsing()
{
    try
    {
        //      assert(IsApprox(ParseLatitude("0:0:0.5s"),          -0.000138889, 1e-8));
        assert(IsApprox(ParseLatitude("  1:2:3.4s "), -1.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLatitude(" 1s"), -1.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLatitude(" 1:2s"), -1.0333333333333333333333333333333, 1e-15));
        assert(IsApprox(ParseLatitude(" 1:2:3s"), -1.0341666666666666666666666666667, 1e-15));
        assert(IsApprox(ParseLatitude("  89:59:59.99s"), -89.9999972222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLatitude("  90:0:0.0s "), -90.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLatitude("  1:2:33.4s "), -1.0426111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLatitude("  1:22:3.4s "), -1.3676111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLatitude("  11:2:3.4s "), -11.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLatitude("  1:2:33.44s "), -1.0426222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLatitude("  1:22:3.44s "), -1.3676222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLatitude("  11:2:3.44s "), -11.0342888888888888888888888888889, 1e-15));
        assert(IsApprox(ParseLatitude("  1:22:33.44s "), -1.3759555555555555555555555555556, 1e-15));
        assert(IsApprox(ParseLatitude("  11:22:33.44s "), -11.3759555555555555555555555555556, 1e-15));
        //assert(IsApprox(ParseLatitude("  90:00:00.01s "), -90.0000027777777777777777777777778, 1e-15)); // will throw exception
        assert(IsApprox(ParseLatitude("  1:2:3.4n "), 1.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLatitude(" 1n"), 1.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLatitude(" 1:2n"), 1.0333333333333333333333333333333, 1e-15));
        assert(IsApprox(ParseLatitude(" 1:2:3n"), 1.0341666666666666666666666666667, 1e-15));
        assert(IsApprox(ParseLatitude("  89:59:59.99n"), 89.9999972222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLatitude("  90:0:0.0n "), 90.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLatitude("  1:2:33.4n "), 1.0426111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLatitude("  1:22:3.4n "), 1.3676111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLatitude("  11:2:3.4n "), 11.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLatitude("  1:2:33.44n "), 1.0426222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLatitude("  1:22:3.44n "), 1.3676222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLatitude("  11:2:3.44n "), 11.0342888888888888888888888888889, 1e-15));
        assert(IsApprox(ParseLatitude("  1:22:33.44n "), 1.3759555555555555555555555555556, 1e-15));
        assert(IsApprox(ParseLatitude("  11:22:33.44n "), 11.3759555555555555555555555555556, 1e-15));
        //assert(IsApprox(ParseLatitude("  90:00:00.01n "), 90.0000027777777777777777777777778, 1e-15)); // will throw exception
        return true;
    }
    catch (CRNavConversionException &ex)
    {
        string err = ex.m_sEx;
        return false;
    }
}


bool TestLongitudeParsing()
{
    try
    {
        assert(IsApprox(ParseLongitude("  1:2:3.4w "), -1.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLongitude(" 1w"), -1.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude(" 1:2w"), -1.0333333333333333333333333333333, 1e-15));
        assert(IsApprox(ParseLongitude(" 1:2:3w"), -1.0341666666666666666666666666667, 1e-15));
        assert(IsApprox(ParseLongitude("  89:59:59.99w"), -89.9999972222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  90:0:0.0w "), -90.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  1:2:33.4w "), -1.0426111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLongitude("  1:22:3.4w "), -1.3676111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLongitude("  11:2:3.4w "), -11.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLongitude("  1:2:33.44w "), -1.0426222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  1:22:3.44w "), -1.3676222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  11:2:3.44w "), -11.0342888888888888888888888888889, 1e-15));
        assert(IsApprox(ParseLongitude("  1:22:33.44w "), -1.3759555555555555555555555555556, 1e-15));
        assert(IsApprox(ParseLongitude("  11:22:33.44w "), -11.3759555555555555555555555555556, 1e-15));
        assert(IsApprox(ParseLongitude("  90:00:00.01w "), -90.0000027777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLongitude("  1:2:3.4e "), 1.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLongitude(" 1e"), 1.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude(" 1:2e"), 1.0333333333333333333333333333333, 1e-15));
        assert(IsApprox(ParseLongitude(" 1:2:3e"), 1.0341666666666666666666666666667, 1e-15));
        assert(IsApprox(ParseLongitude("  89:59:59.99e"), 89.9999972222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  90:0:0.0e "), 90.0000000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  1:2:33.4e "), 1.0426111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLongitude("  1:22:3.4e "), 1.3676111111111111111111111111111, 1e-15));
        assert(IsApprox(ParseLongitude("  11:2:3.4e "), 11.0342777777777777777777777777778, 1e-15));
        assert(IsApprox(ParseLongitude("  1:2:33.44e "), 1.0426222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  1:22:3.44e "), 1.3676222222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  11:2:3.44e "), 11.0342888888888888888888888888889, 1e-15));
        assert(IsApprox(ParseLongitude("  1:22:33.44e "), 1.3759555555555555555555555555556, 1e-15));
        assert(IsApprox(ParseLongitude("  11:22:33.44e "), 11.3759555555555555555555555555556, 1e-15));
        assert(IsApprox(ParseLongitude("  90:00:00.01e "), 90.0000027777777777777777777777778, 1e-15));
        //assert(IsApprox(ParseLongitude("  180:00:00.01e "),   180.00000277777777777777777777778, 1e-15)); // will throw an exception
        assert(IsApprox(ParseLongitude("  180:00:00.00e "), 180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180:00:00e "), 180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180:00e "), 180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180e "), 180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  179:59:59.99e "), 179.99999722222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  179:59:59e "), 179.99972222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  179:59e "), 179.98333333333333333333333333333, 1e-15));
        assert(IsApprox(ParseLongitude("  179e "), 179.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180:00:00.00w "), -180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180:00:00w "), -180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180:00w "), -180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  180w "), -180.00000000000000000000000000000, 1e-15));
        assert(IsApprox(ParseLongitude("  179:59:59.99w "), -179.99999722222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  179:59:59w "), -179.99972222222222222222222222222, 1e-15));
        assert(IsApprox(ParseLongitude("  179:59w "), -179.98333333333333333333333333333, 1e-15));
        assert(IsApprox(ParseLongitude("  179w "), -179.00000000000000000000000000000, 1e-15));


        return true;
    }
    catch (CRNavConversionException &ex)
    {
        string err = ex.m_sEx;
        return false;
    }
}

// @formatter:on

void OutputError(int nError, const string &sDirectory, const string &sFile)
{
    if (nError == -1)
        cerr << "\nProblem opening file " << sDirectory << sFile;
    else if (nError == -2)
        cerr << "\nUnexpected problem reading file " << sDirectory << sFile;
    else if (nError == -3)
        cerr << "\nUnexpected end of file found " << sDirectory << sFile;
    else if (nError == -99)
        cerr << "\nUnknown file IO error occurred with file " << sDirectory << sFile;
    else
        cerr << "\nFailed: 8260.54A Direct measurement test.";
}

bool PathExists(string path)
{
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        cerr << "Cannot access " << path << endl;
        return false;
    }
    if (!info.st_mode & S_IFDIR)
    {
        cerr << path << " is not a directory" << endl;
        return false;
    }
    return true;
}

#if defined(WIN32)
const char kPathSep = '\\';
#else
const char kPathSep = '/';
#endif

string PathAppend(const string &path1, const string &path2)
{
    if (path1[path1.length()] != kPathSep)
    {
        return path1 + kPathSep + path2;
    }

    return path1 + path2;
}

string GetAppName(const string &fullPath)
{
    size_t pos = fullPath.find_last_of(kPathSep);
    if (pos != string::npos)
        return fullPath.substr(pos + 1);
    return fullPath;
}

void ShowUsage(string name)
{
    cout << "Usage: " << name << " -d TEST_DIR [TEST_NUMBERS]" << endl
    << "  -h  Show this help message" << endl
    << "  -d  Path to test data" << endl
    << "  -v  Show version number and copyright" << endl
    << "TEST_NUMBERS are tests to run from 1 to 22, all tests are run "
    << "if not specified."
    << endl;
}

void ShowVersion(const string &name)
{
    cout << name << " " << to_string(geo_formulas_VERSION_MAJOR)
                           + "." + to_string(geo_formulas_VERSION_MINOR)
                           + "." + to_string(geo_formulas_VERSION_PATCH);
    cout << endl << geo_formulas_COPYRIGHT << endl;
}

int main(int argc, char *argv[])
{
    int nTest = 0;
    bitset<32> nTests;
    bool bAllPassed = true;


    char **begin = argv;
    char **end = argv + argc;

    string sDirectory;
    vector<string> args{argv, argv + argc};
    for (auto it = args.begin() + 1; it != args.end(); it++)
    {
        if (*it == "-h")
        {
            ShowUsage(GetAppName(argv[0]));
            return 0;
        }
        else if (*it == "-v")
        {
            ShowVersion(GetAppName(argv[0]));
            return 0;
        }
        else if (*it == "-d")
        {
            if (it + 1 < args.end())
            {
                sDirectory = *++it;
            }
            else
            {
                std::cerr << "-d option requires one argument." << endl;
                return 1;
            }
        }
        else
        {
            int test_number = atoi((*it).c_str());
            if (test_number == 0 || test_number > 22)
            {
                cerr << *it << " is not a valid test value" << endl;
                return 1;
            }
            nTests.set(test_number - 1);
        }
    }

    if (sDirectory.empty())
    {
        cerr << "-d path argument missing." << endl;
        return 1;
    }
    else if (!PathExists(sDirectory))
    {
        return 1;
    }

    if (nTests.count() == 0)
        nTests.set(); // Run all tests

    if (nTests.test(0))
    {
        nTest++;
        cout << "8260.54a Appendix 2 Test suite (version 0.3";
        cout << "\n\nRunning Latitude parsing test: ";
        if (TestLatitudeParsing() == false)
        {
            cerr << "Failed";
            bAllPassed = false;
        }
        else
        {
            cout << "Passed";
        }
    }

    if (nTests.test(1))
    {
        nTest++;
        cout << "\n\nRunning Longitude parsing test: ";
        if (TestLongitudeParsing() == false)
        {
            cerr << "Failed";
            bAllPassed = false;
        }
        else
        {
            cout << "Passed";
        }
    }


    string sFile;
    int nError;

    if (nTests.test(2))
    {
        nTest++;
        sFile = "Direct.csv";
        // Direct Test
        cout << "\n\nRunning 8260.54A Direct measurement test.";
        nError = TestDirect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
                OutputError(nError, sDirectory, sFile);
            else
                cout << "\nPassed: 8260.54A Direct measurement test.";

        }
        else
        {
            cerr << "\nFailed: 8260.54A Direct measurement test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(3))
    {
        nTest++;

        // Direct Test
        cout << "\n\nRunning 8260.54A Inverse measurement test.";
        sFile = "Inverse.csv";
        nError = TestInverse(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
                OutputError(nError, sDirectory, sFile);
            else
                cout << "\nPassed: 8260.54A Inverse measurement test.";

        }
        else
        {
            cerr << "\nFailed: 8260.54A Inverse measurement test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(4))
    {
        nTest++;
        // PtIsOnGeodesic Test
        cout << "\n\nRunning 8260.54A PtIsOnGeodesiic Test.";
        sFile = "PtIsOnGeodesic.csv";
        nError = TestPtIsOnGeodesic(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A PtIsOnGeodesiic Test.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A PtIsOnGeodesiic Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(5))
    {
        nTest++;
        // PointIsOnArc test
        cout << "\n\nRunning 8260.54A PtIsOnArc Test.";
        sFile = "PointIsOnArc.csv";
        nError = TestPtIsOnArc(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A PtIsOnArc Test.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A PtIsOnArc Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(6))
    {
        nTest++;
        // Discretized arc length test
        cout << "\n\nRunning 8260.54A DiscretizedArcLength Test.";
        sFile = "DiscretizedArcLength.csv";
        nError = TestDiscretizedArcLength(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A DiscretizedArcLength Test.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A DiscretizedArcLength Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(7))
    {
        nTest++;
        // Perp Intercept test
        cout << "\n\nRunning 8260.54A Perp Intercept Test.";
        sFile = "PerpIntercept.csv";
        nError = TestPerpIntercept(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Perp Intercept Test.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Perp Intercept Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(8))
    {
        nTest++;
        // PointIsOnLocus test
        cout << "\n\nRunning 8260.54A Pt is on Locus.";
        sFile = "PtIsOnLocus.csv";
        nError = TestPtIsOnLocus(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A PtIsOnLocus Test.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Perp PtIsOnLocus Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(9))
    {
        nTest++;
        // Locus Crs at Point test
        cout << "\n\nRunning 8260.54A Locus Crs at Point";
        sFile = "LocusCrsAtPoint.csv";
        nError = TestLocusCrsAtPoint(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Locus Crs at Point.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Locus Crs at Point.";
            bAllPassed = false;
        }
    }

    if (nTests.test(10))
    {
        nTest++;
        // Crs Intersect
        cout << "\n\nRunning 8260.54A Crs Intersect";
        sFile = "CrsIntersect.csv";
        nError = TestCrsIntersect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Crs Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Crs Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(11))
    {
        nTest++;
        // Arc Intersect
        cout << "\n\nRunning 8260.54A Arc Intersect";
        sFile = "ArcIntersect.csv";
        nError = TestArcIntersect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Arc Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Arc Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(12))
    {
        nTest++;
        // Geodesic Arc Intersect
        cout << "\n\nRunning 8260.54A Geodesic Arc Intersect";
        sFile = "GeodesicArcIntersect.csv";
        nError = TestGeodesicArcIntersect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Geodesic Arc Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Geodesic Arc Intersect.";
            bAllPassed = false;
        }
    }


    if (nTests.test(13))
    {
        nTest++;
        // Geodesic Tangent Fixed Radius Arc
        cout << "\n\nRunning 8260.54A Tangent Fixed Radius Arc";
        sFile = "TangentFixedRadiusArc.csv";
        nError = TestTangentFixedRadiusArc(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Tangent Fixed Radius Arc.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Tangent Fixed Radius Arc.";
            bAllPassed = false;
        }
    }

    if (nTests.test(14))
    {
        nTest++;
        // Geodesic Locus Intersect
        cout << "\n\nRunning 8260.54A GeoLocusIntersect";
        sFile = "GeoLocusIntersect.csv";
        nError = TestGeoLocusIntersect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Geo Locus Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Geo Locus Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(15))
    {
        nTest++;
        // Locus Arc Intersect
        cout << "\n\nRunning 8260.54A Locus Arc Intersect";
        sFile = "LocusArcIntersect.csv";
        nError = TestLocusArcIntersect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Locus Arc Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Locus Arc Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(16))
    {
        nTest++;
        // Locus Intersect
        cout << "\n\nRunning 8260.54A Locus Intersect";
        sFile = "LocusIntersect.csv";
        nError = TestLocusIntersect(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Locus Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Locus Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(17))
    {
        nTest++;
        // Locus Tan Fixed Radius Arc
        cout << "\n\nRunning 8260.54A Locus Tan Fixed Radius Arc";
        sFile = "LocusTanFixedRadiusArc.csv";
        nError = TestLocusTanFixedRadiusArc(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Locus Tan Fixed Radius Arc.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Locus Tan Fixed Radius Arc.";
            bAllPassed = false;
        }
    }

    if (nTests.test(18))
    {
        nTest++;
        // Locus Perp Intersect
        cout << "\n\nRunning 8260.54A Locus Perp Intercept";
        sFile = "LocusPerpIntercept.csv";
        nError = TestLocusPerpIntercept(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Locus Perp Intersect.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Locus Perp Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(19))
    {
        nTest++;
        // Point to Arc Tangents
        cout << "\n\nRunning 8260.54A Point to Arc Tangents";
        sFile = "PointToArcTangents.csv";
        nError = TestPointToArcTangents(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Point to Arc Tangents.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Point to Arc Tangents.";
            bAllPassed = false;
        }
    }

    if (nTests.test(20))
    {
        nTest++;
        // Perp Tangent Points
        cout << "\n\nRunning 8260.54A Perp Tangent Points";
        sFile = "PerpTangentPoints.csv";
        nError = TestPerpTangentPoints(PathAppend(sDirectory, sFile));
        if (nError != 0)
        {
            if (nError < 0)
            {
                OutputError(nError, sDirectory, sFile);
                bAllPassed = false;
            }
            else
                cout << "\nPassed 8260.54A Perp Tangent Points.";
        }
        else
        {
            cerr << "\nFailed: 8260.54A Perp Tangent Points.";
            bAllPassed = false;
        }
    }

    if (nTests.test(21))
    {
        GeoCalcs::LLPoint pt1, pt3;
        GeoCalcs::LLPoint pt2(Deg2Rad(-45 + 33.5 / 60), M_PI_2 * 0.5);
        double crs, crsFromPt, distFromPt;

        for (int k = 0; k < 10; k++)
        {
            for (int i = 0; i < 90; i++)
            {
                for (int j = 0; j < 60; j++)
                {
                    crs = Deg2Rad(i + j / 60.0);
                    pt1.Set(i, M_PI_2);
                    pt3 = GeoCalcs::PerpIntercept(pt1, crs, pt2, crsFromPt, distFromPt, 1e-9);
                }
            }
        }

    }

    if (!bAllPassed)
    {
        cerr << "\n\n*********** One or more tests failed quality control ***********\n";
    }
    else
    {
        cout << "\n\n*********** All tests passed quality control ***********\n";
    }

    return 0;
}

