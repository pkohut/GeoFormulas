/** \file GeoFormulas.h
*   \brief
*/

/****************************************************************************/
/*  GeoFormulas.h                                                           */
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

#pragma once

#include "Geolib.h"
#include "VectorMath.h"

namespace GeoCalcs {

    /**
    *   \remark Order 8260.54A, Appendix 2, 2.1.1
    */
    GEOAPI
    typedef struct LLPOINT {
        double latitude;
        double longitude;

        LLPOINT()
                : latitude(0.0), longitude(0.0)
        { }

        LLPOINT(double dLat, double dLon)
                : latitude(dLat), longitude(dLon)
        { }

        void Set(double dLat, double dLon)
        {
            latitude = dLat;
            longitude = dLon;
        }


    } LLPoint;

    // @formatter:off
    /**
    *   \brief Locus of Points Relative to a Geodesic
    *   \remark Order 8260.54A, Appendix 2, 2.1.4
    */
    GEOAPI
    typedef struct LOCUS {
        LOCUS() : startDist(0.0), endDist(0.), lineType(0) {}
        LLPoint geoStart;   /**< start point of geodesic */
        LLPoint geoEnd;     /**< end point of geodesic */
        LLPoint locusStart; /**< start point of locus */
        LLPoint locusEnd;   /**< end point of locus */
        double startDist;   /**< distance from geodesic to locus at geoStart */
        double endDist;     /**< distance from geodesic to locus at geoEnd
                            *
                            * if startDist == endDist, the locus is parallel to the geodesic<br>
                            * if startDist != endDist, the locus is splayed.<br>
                            * if dist is positive then locus lies to the right of geodesic<br>
                            * if dist is negative then locus lies to the left of geodesic
                            */

        int lineType;       /**< 0 = the locus exists only between geoStart and geoEnd
                            *
                            * 1 = the locus begins at geoStart but extends beyond geoEnd<br>
                            * 2 = the locus extends beyond both geoStart and geoEnd
                            */
    } Locus ;

    /**
    *   \brief Parameter used by DistVincenty function
    *
    *   When DistVincenty returns true, INVERSE_RESULT referenced
    *   parameter to DistVincenty will be be updated.
    */
    GEOAPI
    typedef struct INVERSE_RESULT {
        INVERSE_RESULT() : azimuth(0.0), reverseAzimuth(0.0), distance(0.0) {}
        double azimuth;         /**< calculated azimuth in radians */
        double reverseAzimuth;  /**< calculated reverse azimuth in radians */
        double distance;        /**< calculated distance in meters */
    } InverseResult;

    // returns true if value was calculated (PtIsOnGeodesicResult structure
    // will be updated with computed values), PtIsOnGeodesicResult.result == true
    // if Point is on Geodesic, false otherwise.
    // return false if there was a problem in performing calculations (main DistVincenty())


    /**
    *   \brief Structured used by the PtIsOnGeodesic function
    *
    *   When PtIsOnGeodesic returns true, then referenced instance of
    *   PTISONGEODESICV_RESULT is updated with computed values.
    */
    GEOAPI
    typedef struct PTISONGEODESIC_RESULT {
        PTISONGEODESIC_RESULT() : lengthCode(0), result(0) {}
        LLPoint geoStart;   /**< Geodetic coordinate of line start point */
        LLPoint geoEnd;     /**< Geodetic coordinate of line end point */
        LLPoint geoPt;      /**< Geodetic coordinate of point to test */
        int lengthCode;     /**< Integer that specifies extent of line<br>
                            *    0: geodesic exists only between geoStart and
                            *       geoEnd.<br>
                            *    1: geodesic extends beyound geoEnt
                            */
        int result;         /**< Set true if point is on geodesic, false otherwise. */
    } PtIsOnGeodesicResult;

    // @formatter:on

    /*
    *   \brief Ellipsoid Inverse Flattening constant
    *
    *   298.2572235636654651
    *   \remarks WGS84 Ellipsoid constant
    */
    const double kInverseFlattening = 298.2572235636654651;

    /*
    *   \brief Ellipsoid Flattening constant
    *
    *   Approximately 0.00335281
    *   \remarks WGS84 Ellipsoid constant
    */
    const double kFlattening = 1.0 / kInverseFlattening;

    /*
    *   \brief Ellipsoid Semi Major Axis
    *
    *   6378137.0
    *   \remarks WGS84 Ellipsoid constant
    */
    const double kSemiMajorAxis = 6378137.0;

    /*
    *   \brief Ellipsoid Semi Minor Axis
    *
    *   Approximately 6356752.314245
    *   \remarks WGS84 Ellipsoid constant
    */
    const double kSemiMinorAxis = kSemiMajorAxis * (1 - kFlattening);


    /*  \brief SphereRadius in meters
    *
    *   WGS84 Ellipsoid constant.
    *   \warning
    *   If a calculated sphere radius is used, such as sqrt(SemiMajorAxis *
    *   SemiMinorAxis) then FindLinearRoot may return a root of QNAN
    *   because x[0] == x[1].  In order for some of the Terps tests to
    *   pass, the returned value must be checked and handled appropriately
    *   by the calling function.
    */
    const double kSphereRadius = sqrt(kSemiMajorAxis * kSemiMinorAxis);


    /*
    *   \brief 2 * PI
    */
#define M_2PI M_PI * 2.0


    /*
    *   \brief Epsilon
    *   \returns double epsilon of 0.5e-15.
    *   \note Order 8260.54A Appendix 2, 3.3 Tolerances, states
    *   "Empirical studies have shown that eps = 0.5e-13 and
    *   tol = 1.0-e9 work well."
    *
    *   When implementing the TerpsTest validation application
    *   eps must be set to 0.5e-15 for all tests to pass. If
    *   set as stated in section 3.3 of 8260.54A then the
    *   Tangent Fixed Radius Arc and Locus Tan Fixed Radius Arc
    *   fails validation.
    *
    */
    const double kEps = 0.5e-15;

    /*
    *   \brief Tolerance
    *   \returns double tolerance of 1.0e-9
    *   \note Order 8260.54A Appendix 2, 3.3 Tolerances, states
    *   "Empirical studies have shown that eps = 0.5e-13 and
    *   tol = 1.0-e9 work well."
    *
    *   Functions in the GeoFormulas that use different values
    *   will be clearly marked in the comments and the value
    *   used.
    *
    *   See file "Application test Results.txt" for information
    *   about tolerances used in the "TerpsTest" application.
    *
    */
    const double kTol = 1.0e-9;

    /*
    *   \brief The square of the ellipsoid eccentricity
    */
    const double keSq = kFlattening * (2.0 - kFlattening);

    /*
    *   \brief Point Is on Geodesic Tolerance
    *   \note
    *   See T. Vincenty paper on accuracy, page 90 Survey Review Vol XXIII No. 176, April 1975
    *
    *   Note: PtIsOnGeodesic in 8260.54A uses 'tol' to determine if point is on geodesic or not.
    *   After much testing and reading I believe that tol in this case == 1e-3, which gives
    *   an accuracy of 1mm.  Further testing shows that tol can be pushed to .5e-3 and still
    *   pass the WGS84PtIsOnGeodesic Test Results presented on page A2-93 of Order 8260.54A.
    *   Change TolPtIsOnGeodesic to 1e-3 for the 1mm resolution if 0.5e-3 causes any QA issues.
    */
    const double kTolPtIsOnGeodesic = 0.5e-3;

    /*
     *   \brief Clamps a value between a pair of boundary values
     *   \note Defining here so library will not depend on C++ Boost
     *   Returns
     *     lo if v < lo
     *     hi if hi < v
     *     otherwise, v
     */
    template<class T>
    const T &clamp(const T &v, const T &lo, const T &hi)
    {
        return std::max(lo, std::min(v, hi));
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    ///////////////////// GeoFormulas Function Definitions ///////////////////
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    GEOAPI
    double PrimeVerticalCurvature(double dAngle);

    GEOAPI
    double GeometricMeanMeridional(double dAngle);

    GEOAPI
    VMath::Vector3 ECEF(const LLPoint &llPt, double dAltitude);

    GEOAPI
    bool DistVincenty(const LLPoint &pt1, const LLPoint &pt2, InverseResult &result);

    GEOAPI
    LLPoint DestVincenty(const LLPoint &pt, double brng, double dist);

    GEOAPI
    bool PtIsOnGeodesic(const LLPoint &pt1, const LLPoint &pt2, const LLPoint &pt3, int lengthCode,
                        PtIsOnGeodesicResult &result);

    GEOAPI
    void FindLinearRoot(double *x, double *errArray, double &root);

    GEOAPI
    bool PtIsOnArc(const LLPoint &llArcCenter, double dArcRadius,
                   double dArcStartAzimuth, double dArcEndAzimuth, int nArcDirection,
                   const LLPoint &llTestPt, int &bOnArc);

    GEOAPI
    double GetArcExtent(double dStartCrs, double dEndCrs, const int nOrientation, double dTol);

    GEOAPI
    double DiscretizedArcLength(const LLPoint &center, double dRadius,
                                double dStartCrs, double dEndCrs,
                                int nOrient, int nSegments, double dTol);

    GEOAPI
    double DirectArcLength(const LLPoint &center, double dRadius, double dStartCrs,
                           double dEndCrs, int nOrient, double dTol);

    GEOAPI
    double DistToLocusD(const Locus &loc, double dDistance, double dEps);

    GEOAPI
    double DistToLocusP(const Locus &loc, const LLPoint &geoPt, double dTol, double eps);

    GEOAPI
    LLPoint PointOnLocusP(const Locus &loc, const LLPoint &geoPt, double dTol, double eps);

    GEOAPI
    bool PtIsOnLocus(const Locus &loc, const LLPoint &testPt, double dTol);

    GEOAPI
    bool PtIsOnLocus(const Locus &loc, const LLPoint &testPt, LLPoint &projPt, double dTol);


    GEOAPI
    LLPoint PerpIntercept(const LLPoint &llPt1, double dCrs13, const LLPoint &llPt2,
                          double &dCrsFromPt, double &dDistFromPt, double dTol);

    GEOAPI
    double SignAzimuthDifference(double az1, double az2);

    GEOAPI
    double LocusCrsAtPoint(const Locus &locus, const LLPoint &testPt, LLPoint &geoPt, const double dTol);

    GEOAPI
    double LocusCrsAtPoint(const Locus &locus, const LLPoint &testPt, LLPoint &geoPt, double &dPerpCrs,
                           const double dTol);

    GEOAPI
    bool CrsIntersect(const LLPoint &llPt1, double az13,
                      const LLPoint &llPt2, double az23, double dTol, LLPoint &llIntersect);

    GEOAPI
    bool CrsIntersect(const LLPoint &llPt1, double az13,
                      double &az31, double &dist13, const LLPoint &llPt2, double az23,
                      double &az32, double &dist23, double dTol, LLPoint &llIntersect);

    GEOAPI
    int ArcIntercept(const LLPoint &center1, double radius1,
                     const LLPoint &center2, double radius2,
                     LLPoint &intPtC1, LLPoint &intPtC2, double dTol);

    GEOAPI
    int DistanceIntersection(const LLPoint &pt1, double dist13, const LLPoint &pt2, double dist23,
                             LLPoint &intPtC1, LLPoint &intPtC2, double dTol);

    GEOAPI
    int GeodesicArcIntercept(const LLPoint &pt1, double crs1,
                             const LLPoint &center, double radius,
                             LLPoint &intPtC1, LLPoint &intPtC2, double dTol);

    GEOAPI
    int TangentFixedRadiusArc(const LLPoint &pt1, double crs12, const LLPoint &pt3,
                              double crs3, double radius, int &dir,
                              LLPoint &centerPt, LLPoint &tanPt1, LLPoint &tanPt2, double dTol);

    GEOAPI
    int GeoLocusIntersect(const LLPoint &gStart, const LLPoint &gEnd, const Locus &loc, LLPoint &intersect,
                          double dTol, double dEps);

    GEOAPI
    int LocusArcIntersect(const Locus &locus, const LLPoint &arcCenter, double arcRadius,
                          LLPoint &intersection1, LLPoint &intersection2, double dTol,
                          double dEps);

    GEOAPI
    int LocusIntersect(const Locus &loc1, const Locus &loc2, LLPoint &intersect,
                       double dTol, double dEps);

    GEOAPI
    int LocusTanFixedRadiusArc(const Locus &loc1, const Locus &loc2, double radius,
                               int &dir, LLPoint &center, LLPoint &intersection1, LLPoint &intersection2,
                               double dTol, double dEps);

    GEOAPI
    int LocusPerpIntercept(const Locus &loc, const LLPoint &pt2, double &crsFromPt,
                           double &distFromPt, LLPoint &intPt, double dTol);

    GEOAPI
    int PointToArcTangents(const LLPoint &point, const LLPoint &center, double radius,
                           LLPoint &tanPt1, LLPoint &tanPt2, double dTol);

    GEOAPI
    void PerpTangentPoints(const LLPoint &lineStart, double crs,
                           const LLPoint &center, double radius,
                           LLPoint *linePts, LLPoint *tanPts, double dTol);

    GEOAPI
    double Mod(double a, double b);

}
