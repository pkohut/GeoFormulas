VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ThisWorkbook"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = True
Option Explicit

Private Type LLPoint
    latitude As Double
    longitude As Double
End Type

Private Type locus
        geoStart As LLPoint     ' /**< start point of geodesic */
        geoEnd As LLPoint       ' /**< end point of geodesic */
        locusStart As LLPoint   ' /**< start point of locus */
        locusEnd As LLPoint     ' /**< end point of locus */
        startDist As Double     ' /**< distance from geodesic to locus at geoStart */
        endDist As Double       ' /**< distance from geodesic to locus at geoEnd
                                ' *
                                ' * if startDist == endDist, the locus is parallel to the geodesic<br>
                                ' * if startDist != endDist, the locus is splayed.<br>
                                ' * if dist is positive then locus lies to the right of geodesic<br>
                                ' * if dist is negative then locus lies to the left of geodesic
                                ' */

        lineType As Long        ' /**< 0 = the locus exists only between geoStart and geoEnd
                                ' *
                                ' * 1 = the locus begins at geoStart but extends beyond geoEnd<br>
                                ' * 2 = the locus extends beyond both geoStart and geoEnd
                                ' */
End Type

Private Type InverseResult
    azimuth As Double           '  /**< calculated azimuth in radians */
    reverseAzimuth As Double    '  /**< calculated reverse azimuth in radians */
    distance As Double          '  /**< calculated distance in meters */
End Type

Private Type PtIsOnGeodesicResult
        geoStart As LLPoint     ' /**< Geodetic coordinate of line start point */
        geoEnd As LLPoint       ' /**< Geodetic coordinate of line end point */
        geoPt As LLPoint        ' /**< Geodetic coordinate of point to test */
        lengthCode As Long      ' /**< Integer that specifies extent of line<br>
                                ' *    0: geodesic exists only between geoStart and
                                ' *       geoEnd.<br>
                                ' *    1: geodesic extends beyound geoEnt
                                ' */
        result As Long          ' /**< Set true if point is on geodesic, false otherwise. */
End Type

Private Type VecXYZ
    x As Double
    y As Double
    z As Double
End Type

' inline double _stdcall Eps(void)
Private Declare Function eps _
Lib "GeoFormulas.dll" _
Alias "?Eps@GeoCalcs@@YGNXZ" _
() As Double

' inline double _stdcall Tol(void)
Private Declare Function Tol _
Lib "GeoFormulas.dll" _
Alias "?Tol@GeoCalcs@@YGNXZ" _
() As Double

' inline double _stdcall eSq(void)
Private Declare Function eSq _
Lib "GeoFormulas.dll" _
Alias "?eSq@GeoCalcs@@YGNXZ" _
() As Double

' inline double _stdcall TolPtIsOnGeodesic(void)
Private Declare Function TolPtIsOnGeodesic _
Lib "GeoFormulas.dll" _
Alias "?TolPtIsOnGeodesic@GeoCalcs@@YGNXZ" _
() As Double

' double _stdcall PrimeVerticalCurvature(double dAngle)
Private Declare Function PrimeVerticalCurvature _
Lib "GeoFormulas.dll" _
Alias "?PrimeVerticalCurvature@GeoCalcs@@YGNN@Z" _
(ByVal dAngle As Double) As Double

' double _stdcall GeometricMeanMeridional(double dAngle)
Private Declare Function GeometricMeanMeridional _
Lib "GeoFormulas.dll" _
Alias "?GeometricMeanMeridional@GeoCalcs@@YGNN@Z" _
(ByVal dAngle As Double) As Double

' VMath::Vector3 _stdcall ECEF( const LLPoint & llPt, double dAltitude)
Private Declare Function ECEF _
Lib "GeoFormulas.dll" _
Alias "?ECEF@GeoCalcs@@YG?AVVector3@VMath@@ABULLPOINT@1@N@Z" _
(ByRef llPt As LLPoint, ByVal dAltitude As Double) As VecXYZ

' bool _stdcall DistVincenty(const LLPoint & pt1, const LLPoint & pt2, InverseResult & result)
Private Declare Function DistVincenty _
Lib "GeoFormulas.dll" _
Alias "?DistVincenty@GeoCalcs@@YG_NABULLPOINT@1@0AAUINVERSE_RESULT@1@@Z" _
(ByRef llPt1 As LLPoint, ByRef llPt2 As LLPoint, ByRef result As InverseResult) As Boolean

' LLPoint _stdcall DestVincenty(const LLPoint & pt, double brng, double dist)
Private Declare Function DestVincenty _
Lib "GeoFormulas.dll" _
Alias "?DestVincenty@GeoCalcs@@YG?AULLPOINT@1@ABU21@NN@Z" _
(ByRef llPt As LLPoint, ByVal brng As Double, ByVal dist As Double) As LLPoint

' bool _stdcall PtIsOnGeodesic(const LLPoint & pt1, const LLPoint & pt2,
'                              const LLPoint & pt3, int lengthCode, PtIsOnGeodesicResult & result );
Private Declare Function PtIsOnGeodesic _
Lib "GeoFormulas.dll" _
Alias "?PtIsOnGeodesic@GeoCalcs@@YG_NABULLPOINT@1@00HAAUPTISONGEODESIC_RESULT@1@@Z" _
(ByRef llPt1 As LLPoint, ByRef llPt2 As LLPoint, ByRef llPt3 As LLPoint, _
ByVal lengthCode As Long, ByRef result As PtIsOnGeodesicResult) As Boolean

' void _stdcall FindLinearRoot(double *x, double *errArray, double & root)
Private Declare Sub FindLinearRoot _
Lib "GeoFormulas.dll" _
Alias "?FindLinearRoot@GeoCalcs@@YGXPAN0AAN@Z" _
(ByRef x As Double, ByRef errArray As Double, ByRef root As Double)

' bool _stdcall PtIsOnArc( const LLPoint & llArcCenter, double dArcRadius,
'                          double dArcStartAzimuth, double dArcEndAzimuth, int nArcDirection,
'                          const LLPoint & llTestPt, int & bOnArc )
Private Declare Function PtIsOnArc _
Lib "GeoFormulas.dll" _
Alias "?PtIsOnArc@GeoCalcs@@YG_NABULLPOINT@1@NNNH0AAH@Z" _
(ByRef llArcCenter As LLPoint, ByVal dArcRadius As Double, ByVal dArcStartAzimuth As Double, _
ByVal dArcEndAzimuth As Double, ByVal nArcDirection As Long, ByRef llTestPt As LLPoint, ByRef bOnArc As Long) As Boolean

' double _stdcall GetArcExtent(double dStartCrs, double dEndCrs, const int nOrientation, double dTol)
Private Declare Function GetArcExtent _
Lib "GeoFormulas.dll" _
Alias "?GetArcExtent@GeoCalcs@@YGNNNHN@Z" _
(ByVal dStartCrs As Double, ByVal dEndCrs As Double, ByVal nOrientation As Long, ByVal dTol As Double) As Double

' double _stdcall DiscretizedArcLength(const LLPoint & center, double dRadius,
'                                      double dStartCrs, double dEndCrs,
'                                      int nOrient, int nSegments, double dTol)
Private Declare Function DiscretizedArcLength _
Lib "GeoFormulas.dll" _
Alias "?DiscretizedArcLength@GeoCalcs@@YGNABULLPOINT@1@NNNHHN@Z" _
(ByRef llCenter As LLPoint, ByVal dRadius As Double, ByVal dStartCrs As Double, ByVal dEndCrs As Double, _
ByVal nOrient As Long, ByVal nSegments As Long, ByVal dTol As Double) As Double

' double _stdcall DirectArcLength(const LLPoint & center, double dRadius, double dStartCrs,
'                                 double dEndCrs, int nOrient, double dTol);
Private Declare Function DirectArcLength _
Lib "GeoFormulas.dll" _
Alias "?DirectArcLength@GeoCalcs@@YGNABULLPOINT@1@NNNHN@Z" _
(ByRef llCenter As LLPoint, ByVal dRadius As Double, ByVal dStartCrs As Double, ByVal dEndCrs As Double, _
ByVal nOrient As Long, ByVal dTol As Double) As Double

' double _stdcall DistToLocusD(const Locus & loc, double dDistance, double dEps)
Private Declare Function DistToLocusD _
Lib "GeoFormulas.dll" _
Alias "?DistToLocusD@GeoCalcs@@YGNABULOCUS@1@NN@Z" _
(ByRef loc As locus, ByVal dDistance As Double, ByVal dEps As Double) As Double

' double _stdcall DistToLocusP(const Locus & loc, const LLPoint & geoPt, double dTol, double eps)
Private Declare Function DistToLocusP _
Lib "GeoFormulas.dll" _
Alias "?DistToLocusP@GeoCalcs@@YGNABULOCUS@1@ABULLPOINT@1@NN@Z" _
(ByRef loc As locus, ByRef geoPt As LLPoint, ByVal dTol As Double, ByVal eps As Double) As Double

' LLPoint _stdcall PointOnLocusP(const Locus & loc, const LLPoint & geoPt, double dTol, double eps)
Private Declare Function PointOnLocusP _
Lib "GeoFormulas.dll" _
Alias "?PointOnLocusP@GeoCalcs@@YG?AULLPOINT@1@ABULOCUS@1@ABU21@NN@Z" _
(ByRef loc As locus, ByRef geoPt As LLPoint, ByVal dTol As Double, ByVal eps As Double) As LLPoint

' bool _stdcall PtIsOnLocus(const Locus & loc, const LLPoint & testPt, LLPoint & projPt, double dTol)
Private Declare Function PtIsOnLocus _
Lib "GeoFormulas.dll" _
Alias "?PtIsOnLocus@GeoCalcs@@YG_NABULOCUS@1@ABULLPOINT@1@AAU31@N@Z" _
(ByRef loc As locus, ByRef testPt As LLPoint, ByRef projPt, ByVal dTol As Double) As Boolean

' LLPoint _stdcall PerpIntercept(const LLPoint & llPt1, double dCrs13, const LLPoint & llPt2,
'                                double & dCrsFromPt, double & dDistFromPt, double dTol)
Private Declare Function PerpIntercept _
Lib "GeoFormulas.dll" _
Alias "?PerpIntercept@GeoCalcs@@YG?AULLPOINT@1@ABU21@N0AAN1N@Z" _
(ByRef llPt1 As LLPoint, ByVal dCrs13 As Double, ByRef llPt2 As LLPoint, _
ByRef dCrsFromPt As Double, ByRef dDistFromPt As Double, ByVal dTol As Double) As LLPoint

' double _stdcall SignAzimuthDifference(double az1, double az2)
Private Declare Function SignAzimuthDifference _
Lib "GeoFormulas.dll" _
Alias "?SignAzimuthDifference@GeoCalcs@@YGNNN@Z" _
(ByVal az1 As Double, ByVal az2 As Double) As Double

' double _stdcall LocusCrsAtPoint(const Locus & locus, const LLPoint & testPt, LLPoint & geoPt, double & dPerpCrs, const double dTol)
Private Declare Function LocusCrsAtPoint _
Lib "GeoFormulas.dll" _
Alias "?LocusCrsAtPoint@GeoCalcs@@YGNABULOCUS@1@ABULLPOINT@1@AAU31@AANN@Z" _
(ByRef locus As locus, ByRef testPt As LLPoint, ByRef geoPt As LLPoint, ByRef dPerpCrs As Double, ByVal dTol As Double) As Double

' bool  _stdcall CrsIntersect(const LLPoint & llPt1, double az13,
'                             const LLPoint & llPt2, double az23, double dTol, LLPoint & llIntersect)
Private Declare Function CrsIntersect1 _
Lib "GeoFormulas.dll" _
Alias "?CrsIntersect@GeoCalcs@@YG_NABULLPOINT@1@N0NNAAU21@@Z" _
(ByRef llPt1 As LLPoint, ByVal az13 As Double, ByRef llPt2 As LLPoint, ByVal az23 As Double, _
ByVal dTol As Double, ByRef llIntersect As LLPoint) As Boolean

'bool _stdcall CrsIntersect(const LLPoint & llPt1, double az13,
'                           double & az31, double & dist13, const LLPoint & llPt2, double az23,
'                           double & az32, double & dist23, double dTol, LLPoint & llIntersect)
Private Declare Function CrsIntersect2 _
Lib "GeoFormulas.dll" _
Alias "?CrsIntersect@GeoCalcs@@YG_NABULLPOINT@1@NAAN10N11NAAU21@@Z" _
(ByRef llPt1 As LLPoint, ByVal az13 As Double, _
ByRef az31 As Double, ByRef dist13 As Double, ByRef llPt2 As LLPoint, ByVal az23 As Double, _
ByRef az32 As Double, ByRef dist23 As Double, ByVal dTol As Double, ByRef llIntersect As LLPoint) As Boolean

' int _stdcall ArcIntercept(const LLPoint & center1, double radius1,
'                           const LLPoint & center2, double radius2,
'                           LLPoint & intPtC1, LLPoint & intPtC2, double dTol)
Private Declare Function ArcIntercept _
Lib "GeoFormulas.dll" _
Alias "?ArcIntercept@GeoCalcs@@YGHABULLPOINT@1@N0NAAU21@1N@Z" _
(ByRef llCenter1 As LLPoint, ByVal radius1 As Double, ByRef llCenter2 As LLPoint, ByVal radius2 As Double, _
ByRef llIntPtC1 As LLPoint, ByRef llIntPtC2 As LLPoint, ByVal dTol As Double) As Long

'    int _stdcall DistanceIntersection(const LLPoint & pt1, double dist13, const LLPoint & pt2, double dist23,
'                                      LLPoint & intPtC1, LLPoint & intPtC2, double dTol)
Private Declare Function DistanceIntersection _
Lib "GeoFormulas.dll" _
Alias "?DistanceIntersection@GeoCalcs@@YGHABULLPOINT@1@N0NAAU21@1N@Z" _
(ByRef llPt1 As LLPoint, ByVal dist13 As Double, ByRef llPt2 As LLPoint, ByVal dist23 As Double, _
ByRef llIntPtC1 As LLPoint, ByRef llIntPtC2 As LLPoint, ByVal dTol As Double) As Long

' int _stdcall GeodesicArcIntercept(const LLPoint & pt1, double crs1,
'                                   const LLPoint & center, double radius,
'                                   LLPoint & intPtC1, LLPoint & intPtC2, double dTol)
Private Declare Function GeodesicArcIntercept _
Lib "GeoFormulas.dll" _
Alias "?GeodesicArcIntercept@GeoCalcs@@YGHABULLPOINT@1@N0NAAU21@1N@Z" _
(ByRef llPt1 As LLPoint, ByVal crs1 As Double, ByRef llCenter As LLPoint, ByVal radius As Double, _
ByRef llIntPtC1 As LLPoint, ByRef llIntPtC2 As LLPoint, ByVal dTol As Double) As Long

' int _stdcall TangentFixedRadiusArc(const LLPoint & pt1, double crs12, const LLPoint & pt3,
'                                    double crs3, double radius, int & dir,
'                                    LLPoint & centerPt, LLPoint & tanPt1, LLPoint & tanPt2, double dTol)
Private Declare Function TangentFixedRadiusArc _
Lib "GeoFormulas.dll" _
Alias "?TangentFixedRadiusArc@GeoCalcs@@YGHABULLPOINT@1@N0NNAAHAAU21@22N@Z" _
(ByRef llPt1 As LLPoint, ByVal crs12 As Double, ByRef llPt3 As LLPoint, ByVal crs3 As Double, _
ByVal radius As Double, ByRef dir As Long, ByRef llCenterPt As LLPoint, _
ByRef llTanPt1 As LLPoint, ByRef llTanPt2 As LLPoint, ByVal dTol As Double) As Long

' int _stdcall GeoLocusIntersect(const LLPoint & gStart, const LLPoint & gEnd, const Locus & loc, LLPoint & intersect,
'        double dTol, double dEps)
Private Declare Function GeoLocusIntersect _
Lib "GeoFormulas.dll" _
Alias "?GeoLocusIntersect@GeoCalcs@@YGHABULLPOINT@1@0ABULOCUS@1@AAU21@NN@Z" _
(ByRef llGStart As LLPoint, ByRef llGEnd As LLPoint, ByRef loc As locus, ByRef llIntersect As LLPoint, _
ByVal dTol As Double, ByVal dEps As Double) As Long

'     int _stdcall LocusArcIntersect(const Locus & locus, const LLPoint & arcCenter, double arcRadius,
'        LLPoint & intersection1, LLPoint & intersection2, double dTol,
'        double dEps)
Private Declare Function LocusArcIntersect _
Lib "GeoFormulas.dll" _
Alias "?LocusArcIntersect@GeoCalcs@@YGHABULOCUS@1@ABULLPOINT@1@NAAU31@2NN@Z" _
(ByRef locus As locus, ByRef llArcCenter As LLPoint, ByVal dArcRadius As Double, _
ByRef llIntersection1 As LLPoint, ByRef llIntersection2 As LLPoint, ByVal dTol As Double, ByVal dEps As Double) As Long

' int _stdcall LocusIntersect(const Locus & loc1, const Locus & loc2, LLPoint & intersect,
'                             double dTol, double dEps)
Private Declare Function LocusIntersect _
Lib "GeoFormulas.dll" _
Alias "?LocusIntersect@GeoCalcs@@YGHABULOCUS@1@0AAULLPOINT@1@NN@Z" _
(ByRef loc1 As locus, ByRef loc2 As locus, ByRef llIntersect As LLPoint, ByVal dTol As Double, ByVal dEps As Double) As Long


' int _stdcall LocusTanFixedRadiusArc(const Locus & loc1, const Locus & loc2, double radius,
'        int & dir, LLPoint & center, LLPoint & intersection1, LLPoint & intersection2,
'        double dTol, double dEps)
Private Declare Function LocusTanFixedRadiusArc _
Lib "GeoFormulas.dll" _
Alias "?LocusTanFixedRadiusArc@GeoCalcs@@YGHABULOCUS@1@0NAAHAAULLPOINT@1@22NN@Z" _
(ByRef loc1 As locus, ByRef loc2 As locus, ByVal dRadius As Double, _
ByRef dir As Long, ByRef llCenter As LLPoint, ByRef llIntersection1 As LLPoint, ByRef llIntersectino2 As LLPoint, _
ByVal dTol As Double, ByVal dEps As Double) As Long

' int _stdcall LocusPerpIntercept(const Locus & loc, const LLPoint & pt2, double & crsFromPt,
'                                 double & distFromPt, LLPoint & intPt, double dTol)
Private Declare Function LocusPerpIntercept _
Lib "GeoFormulas.dll" _
Alias "?LocusPerpIntercept@GeoCalcs@@YGHABULOCUS@1@ABULLPOINT@1@AAN2AAU31@N@Z" _
(ByRef loc As locus, ByRef llPt2 As LLPoint, ByRef dCrsFromPt As Double, _
ByRef dDistFromPt As Double, ByRef llIntPt As LLPoint, ByVal dTol As Double) As Long

' int _stdcall PointToArcTangents(const LLPoint & point, const LLPoint & center, double radius,
'                                 LLPoint & tanPt1, LLPoint & tanPt2, double dTol)
Private Declare Function PointToArcTangents _
Lib "GeoFormulas.dll" _
Alias "?PointToArcTangents@GeoCalcs@@YGHABULLPOINT@1@0NAAU21@1N@Z" _
(ByRef llPt As LLPoint, ByRef llCenter As LLPoint, ByVal dRadius As Double, _
ByRef llTanPt1 As LLPoint, ByRef llTanPt2 As LLPoint, ByVal dTol As Double) As Long

' void _stdcall PerpTangentPoints(const LLPoint & lineStart, double crs,
'                                 const LLPoint & center, double radius,
'                                 LLPoint linePts[2], LLPoint tanPts[2], double dTol)
Private Declare Sub PerpTangentPoints _
Lib "GeoFormulas.dll" _
Alias "?PerpTangentPoints@GeoCalcs@@YGXABULLPOINT@1@N0NPAU21@1N@Z" _
(ByRef llLineStart As LLPoint, ByVal dCrs As Double, ByRef llCenter As LLPoint, ByVal dRadius As Double, _
ByRef llLinePts As LLPoint, ByRef llTanPts As LLPoint, ByVal dTol As Double)

' double _stdcall Mod(double a, double b)
Private Declare Function Mod1 _
Lib "GeoFormulas.dll" _
Alias "?Mod@GeoCalcs@@YGNNN@Z" _
(ByVal a As Double, ByVal b As Double) As Double



'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

' const inline double _stdcall InverseFlattening(void)
Private Declare Function InverseFlattening _
Lib "GeoFormulas.dll" _
Alias "?InverseFlattening@GeoCalcs@@YG?BNXZ" _
() As Double


' const inline double _stdcall Flattening(void)
Private Declare Function Flattening _
Lib "GeoFormulas.dll" _
Alias "?Flattening@GeoCalcs@@YG?BNXZ" _
() As Double

' const inline double _stdcall SemiMajorAxis(void)
Private Declare Function SemiMajorAxis _
Lib "GeoFormulas.dll" _
Alias "?SemiMajorAxis@GeoCalcs@@YG?BNXZ" _
() As Double

' const inline double _stdcall SemiMinorAxis(void)
Private Declare Function SemiMinorAxis _
Lib "GeoFormulas.dll" _
Alias "?SemiMinorAxis@GeoCalcs@@YG?BNXZ" _
() As Double


' const inline double _stdcall SphereRadius(void)
Private Declare Function SphereRadius _
Lib "GeoFormulas.dll" _
Alias "?SphereRadius@GeoCalcs@@YG?BNXZ" _
() As Double


' inline bool _stdcall IsApprox(double a, double b, const double precision = 1e-11)
Private Declare Function IsApprox _
Lib "GeoFormulas.dll" _
Alias "?IsApprox@@YG_NNNN@Z" _
(ByVal a As Double, ByVal b As Double, ByVal precision As Double) As Boolean

' inline bool _stdcall IsNearZero(double a, double epsilon = 2e-6)
Private Declare Function IsNearZero _
Lib "GeoFormulas.dll" _
Alias "?IsNearZero@@YG_NNN@Z" _
(ByVal a As Double, ByVal precision As Double) As Boolean


'inline double _stdcall FeetPerMeter(void)
Private Declare Function FeetPerMeter _
Lib "GeoFormulas.dll" _
Alias "?FeetPerMeter@@YGNXZ" _
() As Double

'inline double _stdcall MetersPerFoot(void)
Private Declare Function MetersPerFoot _
Lib "GeoFormulas.dll" _
Alias "?MetersPerFoot@@YGNXZ" _
() As Double

' inline double _stdcall FeetPerNm(void)
Private Declare Function FeetPerNm _
Lib "GeoFormulas.dll" _
Alias "?FeetPerNm@@YGNXZ" _
() As Double

' inline double _stdcall NmPerFoot(void)
Private Declare Function NmPerFoot _
Lib "GeoFormulas.dll" _
Alias "?NmPerFoot@@YGNXZ" _
() As Double

' inline double _stdcall MetersPerNm(void)
Private Declare Function MetersPerNm _
Lib "GeoFormulas.dll" _
Alias "?MetersPerNm@@YGNXZ" _
() As Double

' inline double _stdcall NmPerMeter(void)
Private Declare Function NmPerMeter _
Lib "GeoFormulas.dll" _
Alias "?NmPerMeter@@YGNXZ" _
() As Double

' inline double _stdcall FeetToMeters(const double dFeet)
Private Declare Function FeetToMeters _
Lib "GeoFormulas.dll" _
Alias "?FeetToMeters@@YGNN@Z" _
(ByVal dFeet As Double) As Double

' inline double _stdcall MetersToFeet(const double dMeters)
Private Declare Function MetersToFeet _
Lib "GeoFormulas.dll" _
Alias "?MetersToFeet@@YGNN@Z" _
(ByVal dMeters As Double) As Double

' inline double _stdcall FeetToNm(const double dFeet)
Private Declare Function FeetToNm _
Lib "GeoFormulas.dll" _
Alias "?FeetToNm@@YGNN@Z" _
(ByVal dFeet As Double) As Double

' inline double _stdcall NmToFeet(const double dNm)
Private Declare Function NmToFeet _
Lib "GeoFormulas.dll" _
Alias "?NmToFeet@@YGNN@Z" _
(ByVal dNm As Double) As Double

' inline double _stdcall MetersToNm(const double dMeters)
Private Declare Function MetersToNm _
Lib "GeoFormulas.dll" _
Alias "?MetersToNm@@YGNN@Z" _
(ByVal dMeters As Double) As Double

' inline double _stdcall NmToMeters(const double dNm)
Private Declare Function NmToMeters _
Lib "GeoFormulas.dll" _
Alias "?NmToMeters@@YGNN@Z" _
(ByVal dNm As Double) As Double

' inline double _stdcall Deg2Rad(const double dVal)
Private Declare Function Deg2Rad _
Lib "GeoFormulas.dll" _
Alias "?Deg2Rad@@YGNN@Z" _
(ByVal dVal As Double) As Double

' inline double _stdcall Rad2Deg(const double dVal)
Private Declare Function Rad2Deg _
Lib "GeoFormulas.dll" _
Alias "?Rad2Deg@@YGNN@Z" _
(ByVal dVal As Double) As Double

' inline double _stdcall CelsiusToFahrenheit(const double dCelsius)
Private Declare Function CelsiusToFahrenheit _
Lib "GeoFormulas.dll" _
Alias "?CelsiusToFahrenheit@@YGNN@Z" _
(ByVal dCelsius As Double) As Double

' inline double _stdcall FahrenheitToCelsius(const double dFahrenheit)
Private Declare Function FahrenheitToCelsius _
Lib "GeoFormulas.dll" _
Alias "?FahrenheitToCelsius@@YGNN@Z" _
(ByVal dFahrenheit As Double) As Double


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

' Show how to call PerpTangentPoints as 2 of the parameters are arrays
Public Sub TestPerpTangentPoints()
    Dim llStart As LLPoint
    Dim llCenter As LLPoint
    Dim dCrs As Double
    Dim dRadius As Double
    Dim llLinePts(0 To 1) As LLPoint  ' array with 2 elements
    Dim llTanPts(0 To 1) As LLPoint   ' array with 2 elements
    Dim dTol As Double
    
    ' setup the input data (values from TestPerpTangentPoints.cpp, first entry)
    dTol = 0.000000001                      ' dTol = 1e-9
    dRadius = 92600#                        ' 92600 meters
    dCrs = 6.10865238198015                 ' course (radians)
    llStart.latitude = 0.699468816930232    '
    llStart.longitude = -1.13815199146851

    llCenter.latitude = 0.701159362236261
    llCenter.longitude = -1.22544220993861
    
    Call PerpTangentPoints(llStart, dCrs, llCenter, dRadius, llLinePts(0), llTanPts(0), dTol)
    
    ' after call llLinePts and llTanPts will contain computed results
    ' llLinePts(0).latitude = 0.72875973555377354  llLinePts(0).longitude = -1.1450477579398741
    ' llLinePts(1).latitude = 0.70003609540851230  llLinePts(1).longitude = -1.1382822630487073
    ' llTanPts(0).latitude =  0.71531792738744804  llTanPts(0).longitude =  -1.2298623926094026
    ' llTanPts(1).latitude =  0.68698311256712241  llTanPts(1).longitude =  -1.2211607205876529
    
End Sub


' Show how to call FindLinearRoot, 2 of the parameters are arrays
Public Sub TestFindLinearRoot()
    Dim inpArray(0 To 1) As Double
    Dim errArray(0 To 1) As Double
    Dim root As Double
    
    inpArray(0) = 1#
    inpArray(1) = 2#
    
    Call FindLinearRoot(inpArray(0), errArray(0), root)
    
    ' after call root should be 1
    
End Sub

'Sub
Public Sub TestDistanceVincenty()
    Dim llStart As LLPoint
    Dim llCenter As LLPoint
    Dim result As InverseResult
    Dim bVal As Boolean

    ' Test values from TestInverse.cpp, first entry
    llStart.latitude = 0.701159362236261
    llStart.longitude = -1.22544220993861
    llCenter.latitude = 0.699735323810393
    llCenter.longitude = -1.14960581930752

    bVal = DistVincenty(llStart, llCenter, result)
    
    ' after call to DistVincenty
    ' bVal = true
    ' result.azimuth = 1.5707963266606586
    ' result.reverseAzimuth = 4.7612838300894262
    ' result.distance = 370399.99992037204

End Sub

Public Sub TestLocusCrsAtPoint()
    Dim loc As locus
    Dim testPt As LLPoint
    Dim geoPt As LLPoint
    Dim dPerpCrs As Double
    Dim dLocusCrs As Double
        
    ' setup input values, from TestLocusCrsAtPoint.cpp, first entry
    loc.geoStart.latitude = 0.748915933893956
    loc.geoStart.longitude = -1.23673061168956
    loc.geoEnd.latitude = 0.748900251189481
    loc.geoEnd.longitude = -1.22881410717427
    loc.locusStart.latitude = 0.749061415910718
    loc.locusStart.longitude = -1.23673061168956
    loc.locusEnd.latitude = 0.749045731073063
    loc.locusEnd.longitude = -1.22881304034177
    loc.startDist = -926#
    loc.endDist = -926#
    loc.lineType = -858993460
    
    testPt.latitude = 0.749061386482528
    testPt.longitude = -1.23638776745313
    
    dLocusCrs = LocusCrsAtPoint(loc, testPt, geoPt, dPerpCrs, 0.001)
    
    ' after call to LocusCrsAtPoint
    ' dLocusCrs = 1.5710297488536700
    ' geoPt.latitude = 0.74891590448901657  geoPt.longitude = -1.2363878136507465
    ' dPerpCrs = 3.1418260756485665
    
    
    
End Sub
