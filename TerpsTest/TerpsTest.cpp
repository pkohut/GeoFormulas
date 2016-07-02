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
#include "LatLongConversions.h"
#include "Conversions.h"
#include "GeoFormulas.h"
#include <boost/typeof/std/bitset.hpp>

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


bool TestLatitudeParsing()
{
    try
    {
        //      assert(IsApprox(ParseLatitude("0:0:0.5s"),          -0.000138889, 1e-8) == true);
        assert(IsApprox(ParseLatitude("  1:2:3.4s "), -1.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLatitude(" 1s"), -1.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLatitude(" 1:2s"), -1.0333333333333333333333333333333, 1e-15) == true);
        assert(IsApprox(ParseLatitude(" 1:2:3s"), -1.0341666666666666666666666666667, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  89:59:59.99s"), -89.9999972222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  90:0:0.0s "), -90.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:2:33.4s "), -1.0426111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:22:3.4s "), -1.3676111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  11:2:3.4s "), -11.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:2:33.44s "), -1.0426222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:22:3.44s "), -1.3676222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  11:2:3.44s "), -11.0342888888888888888888888888889, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:22:33.44s "), -1.3759555555555555555555555555556, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  11:22:33.44s "), -11.3759555555555555555555555555556, 1e-15) == true);
        //assert(IsApprox(ParseLatitude("  90:00:00.01s "), -90.0000027777777777777777777777778, 1e-15) == true); // will throw exception
        assert(IsApprox(ParseLatitude("  1:2:3.4n "), 1.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLatitude(" 1n"), 1.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLatitude(" 1:2n"), 1.0333333333333333333333333333333, 1e-15) == true);
        assert(IsApprox(ParseLatitude(" 1:2:3n"), 1.0341666666666666666666666666667, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  89:59:59.99n"), 89.9999972222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  90:0:0.0n "), 90.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:2:33.4n "), 1.0426111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:22:3.4n "), 1.3676111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  11:2:3.4n "), 11.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:2:33.44n "), 1.0426222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:22:3.44n "), 1.3676222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  11:2:3.44n "), 11.0342888888888888888888888888889, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  1:22:33.44n "), 1.3759555555555555555555555555556, 1e-15) == true);
        assert(IsApprox(ParseLatitude("  11:22:33.44n "), 11.3759555555555555555555555555556, 1e-15) == true);
        //assert(IsApprox(ParseLatitude("  90:00:00.01n "), 90.0000027777777777777777777777778, 1e-15) == true); // will throw exception
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
        assert(IsApprox(ParseLongitude("  1:2:3.4w "), -1.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLongitude(" 1w"), -1.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude(" 1:2w"), -1.0333333333333333333333333333333, 1e-15) == true);
        assert(IsApprox(ParseLongitude(" 1:2:3w"), -1.0341666666666666666666666666667, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  89:59:59.99w"), -89.9999972222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  90:0:0.0w "), -90.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:2:33.4w "), -1.0426111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:22:3.4w "), -1.3676111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  11:2:3.4w "), -11.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:2:33.44w "), -1.0426222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:22:3.44w "), -1.3676222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  11:2:3.44w "), -11.0342888888888888888888888888889, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:22:33.44w "), -1.3759555555555555555555555555556, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  11:22:33.44w "), -11.3759555555555555555555555555556, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  90:00:00.01w "), -90.0000027777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:2:3.4e "), 1.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLongitude(" 1e"), 1.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude(" 1:2e"), 1.0333333333333333333333333333333, 1e-15) == true);
        assert(IsApprox(ParseLongitude(" 1:2:3e"), 1.0341666666666666666666666666667, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  89:59:59.99e"), 89.9999972222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  90:0:0.0e "), 90.0000000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:2:33.4e "), 1.0426111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:22:3.4e "), 1.3676111111111111111111111111111, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  11:2:3.4e "), 11.0342777777777777777777777777778, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:2:33.44e "), 1.0426222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:22:3.44e "), 1.3676222222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  11:2:3.44e "), 11.0342888888888888888888888888889, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  1:22:33.44e "), 1.3759555555555555555555555555556, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  11:22:33.44e "), 11.3759555555555555555555555555556, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  90:00:00.01e "), 90.0000027777777777777777777777778, 1e-15) == true);
        //assert(IsApprox(ParseLongitude("  180:00:00.01e "),   180.00000277777777777777777777778, 1e-15) == true); // will throw an exception
        assert(IsApprox(ParseLongitude("  180:00:00.00e "), 180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180:00:00e "), 180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180:00e "), 180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180e "), 180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179:59:59.99e "), 179.99999722222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179:59:59e "), 179.99972222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179:59e "), 179.98333333333333333333333333333, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179e "), 179.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180:00:00.00w "), -180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180:00:00w "), -180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180:00w "), -180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  180w "), -180.00000000000000000000000000000, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179:59:59.99w "), -179.99999722222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179:59:59w "), -179.99972222222222222222222222222, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179:59w "), -179.98333333333333333333333333333, 1e-15) == true);
        assert(IsApprox(ParseLongitude("  179w "), -179.00000000000000000000000000000, 1e-15) == true);


        return true;
    }
    catch (CRNavConversionException &ex)
    {
        string err = ex.m_sEx;
        return false;
    }
}

void OutputError(int nError, const string &sDirectory, const string &sFile)
{
    if (nError == -1)
        cout << "\nProblem opening file " << sDirectory << sFile;
    else if (nError == -2)
        cout << "\nUnexpected problem reading file " << sDirectory << sFile;
    else if (nError == -3)
        cout << "\nUnexpected end of file found " << sDirectory << sFile;
    else if (nError == -99)
        cout << "\nUnknown file IO error occurred with file " << sDirectory << sFile;
    else
        cout << "\nFailed: 8260.54A Direct measurement test.";
}


int main(int argc, char *argv[])
{
    int nTest = 0;
    bitset<32> nTests;
    bool bAllPassed = true;

    for (int i = 1; i < argc; i++)
    {
        nTests.set(atoi(argv[i]) - 1);
    }
    if (argc == 1)
        nTests.set(); // set all bits

    if (nTests.test(0))
    {
        nTest++;
        cout << "8260.54a Appendix 2 Test suite (version 0.3";
        cout << "\n\nRunning Latitude parsing test: ";
        if (TestLatitudeParsing() == false)
        {
            cout << "Failed";
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
            cout << "Failed";
            bAllPassed = false;
        }
        else
        {
            cout << "Passed";
        }
    }

    string sDirectory = "../8260.54ATestData/Test Cases and Expected Results in CSV Format/";
    string sFile;
    int nError;

    if (nTests.test(2))
    {
        nTest++;
        sFile = "Direct.csv";
        // Direct Test
        cout << "\n\nRunning 8260.54A Direct measurement test.";
        nError = TestDirect(sDirectory + sFile);
        if (nError != 0)
        {
            if (nError < 0)
                OutputError(nError, sDirectory, sFile);
            else
                cout << "\nPassed: 8260.54A Direct measurement test.";

        }
        else
        {
            cout << "\nFailed: 8260.54A Direct measurement test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(3))
    {
        nTest++;

        // Direct Test
        cout << "\n\nRunning 8260.54A Inverse measurement test.";
        sFile = "Inverse.csv";
        nError = TestInverse(sDirectory + sFile);
        if (nError != 0)
        {
            if (nError < 0)
                OutputError(nError, sDirectory, sFile);
            else
                cout << "\nPassed: 8260.54A Inverse measurement test.";

        }
        else
        {
            cout << "\nFailed: 8260.54A Inverse measurement test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(4))
    {
        nTest++;
        // PtIsOnGeodesic Test
        cout << "\n\nRunning 8260.54A PtIsOnGeodesiic Test.";
        sFile = "PtIsOnGeodesic.csv";
        nError = TestPtIsOnGeodesic(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A PtIsOnGeodesiic Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(5))
    {
        nTest++;
        // PointIsOnArc test
        cout << "\n\nRunning 8260.54A PtIsOnArc Test.";
        sFile = "PointIsOnArc.csv";
        nError = TestPtIsOnArc(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A PtIsOnArc Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(6))
    {
        nTest++;
        // Discretized arc length test
        cout << "\n\nRunning 8260.54A DiscretizedArcLength Test.";
        sFile = "DiscretizedArcLength.csv";
        nError = TestDiscretizedArcLength(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A DiscretizedArcLength Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(7))
    {
        nTest++;
        // Perp Intercept test
        cout << "\n\nRunning 8260.54A Perp Intercept Test.";
        sFile = "PerpIntercept.csv";
        nError = TestPerpIntercept(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Perp Intercept Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(8))
    {
        nTest++;
        // PointIsOnLocus test
        cout << "\n\nRunning 8260.54A Pt is on Locus.";
        sFile = "PtIsOnLocus.csv";
        nError = TestPtIsOnLocus(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Perp PtIsOnLocus Test.";
            bAllPassed = false;
        }
    }

    if (nTests.test(9))
    {
        nTest++;
        // Locus Crs at Point test
        cout << "\n\nRunning 8260.54A Locus Crs at Point";
        sFile = "LocusCrsAtPoint.csv";
        nError = TestLocusCrsAtPoint(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Locus Crs at Point.";
            bAllPassed = false;
        }
    }

    if (nTests.test(10))
    {
        nTest++;
        // Crs Intersect
        cout << "\n\nRunning 8260.54A Crs Intersect";
        sFile = "CrsIntersect.csv";
        nError = TestCrsIntersect(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Crs Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(11))
    {
        nTest++;
        // Arc Intersect
        cout << "\n\nRunning 8260.54A Arc Intersect";
        sFile = "ArcIntersect.csv";
        nError = TestArcIntersect(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Arc Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(12))
    {
        nTest++;
        // Geodesic Arc Intersect
        cout << "\n\nRunning 8260.54A Geodesic Arc Intersect";
        sFile = "GeodesicArcIntersect.csv";
        nError = TestGeodesicArcIntersect(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Geodesic Arc Intersect.";
            bAllPassed = false;
        }
    }


    if (nTests.test(13))
    {
        nTest++;
        // Geodesic Tangent Fixed Radius Arc
        cout << "\n\nRunning 8260.54A Tangent Fixed Radius Arc";
        sFile = "TangentFixedRadiusArc.csv";
        nError = TestTangentFixedRadiusArc(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Tangent Fixed Radius Arc.";
            bAllPassed = false;
        }
    }

    if (nTests.test(14))
    {
        nTest++;
        // Geodesic Locus Intersect
        cout << "\n\nRunning 8260.54A GeoLocusIntersect";
        sFile = "GeoLocusIntersect.csv";
        nError = TestGeoLocusIntersect(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Geo Locus Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(15))
    {
        nTest++;
        // Locus Arc Intersect
        cout << "\n\nRunning 8260.54A Locus Arc Intersect";
        sFile = "LocusArcIntersect.csv";
        nError = TestLocusArcIntersect(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Locus Arc Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(16))
    {
        nTest++;
        // Locus Intersect
        cout << "\n\nRunning 8260.54A Locus Intersect";
        sFile = "LocusIntersect.csv";
        nError = TestLocusIntersect(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Locus Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(17))
    {
        nTest++;
        // Locus Tan Fixed Radius Arc
        cout << "\n\nRunning 8260.54A Locus Tan Fixed Radius Arc";
        sFile = "LocusTanFixedRadiusArc.csv";
        nError = TestLocusTanFixedRadiusArc(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Locus Tan Fixed Radius Arc.";
            bAllPassed = false;
        }
    }

    if (nTests.test(18))
    {
        nTest++;
        // Locus Perp Intersect
        cout << "\n\nRunning 8260.54A Locus Perp Intercept";
        sFile = "LocusPerpIntercept.csv";
        nError = TestLocusPerpIntercept(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Locus Perp Intersect.";
            bAllPassed = false;
        }
    }

    if (nTests.test(19))
    {
        nTest++;
        // Point to Arc Tangents
        cout << "\n\nRunning 8260.54A Point to Arc Tangents";
        sFile = "PointToArcTangents.csv";
        nError = TestPointToArcTangents(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Point to Arc Tangents.";
            bAllPassed = false;
        }
    }

    if (nTests.test(20))
    {
        nTest++;
        // Perp Tangent Points
        cout << "\n\nRunning 8260.54A Perp Tangent Points";
        sFile = "PerpTangentPoints.csv";
        nError = TestPerpTangentPoints(sDirectory + sFile);
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
            cout << "\nFailed: 8260.54A Perp Tangent Points.";
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


    if (bAllPassed == false)
    {
        cout << "\n\n*********** One or more tests failed quality control ***********";
    }
    else
    {
        cout << "\n\n*********** All tests passed quality control ***********";
    }


    return 0;
}

