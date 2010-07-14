GeoFormulas and TerpsTest
=========================

GeoFormulas
-----------
GeoForumlas is a collection of ellipsoid formulas, written in C++, that are based on the formulas found in Appendix 2 of [FAA document Order 8260.54A](http://www.faa.gov/documentLibrary/media/Order/8260_54A.pdf).

> Algorithms and methods are described for calculating geodetic locations (latitudes and longitudes) on the World Geodetic System of 1984 (WGS-84) ellipsoid, resulting from intersections of geodesic and non-geodesic paths. These algorithms utilize existing distance and azimuth calculation methods to compute intersections and tangent points needed for area navigation procedure construction. The methods apply corrections to an initial spherical approximation until the error is less than the maximum allowable error, as specified by the user.

The [WGS84 Ellipsoid Calculator](http://www.pkautomation.com/wgs84_geodesic_calc.html) is a standalone Windows application that utilizes these formulas, and has been used by some in the GeoCaching community to generate and solve GeoCache puzzles.

GeoFormulas has some dependency on the STL. The version that comes with MSVC 7.1 and 8.0 are sufficient to build the GeoFormulas library.

TerpsTest
---------
TerpsTest is a test harness driven by GeoFormulas. The test data and expected results are published in [FAA Order 8260.54A](http://www.faa.gov/documentLibrary/media/Order/8260_54A.pdf) Appendix 2, Attachment C.

The goal of the test harness is to have a solid set of test data and expected results to run against the GeoFormulas. A great deal of effort was put into creating the test suite and to get the results within expected tolerances.

The directory __8260.54ATestData__ contains CSV test data used by TerpsTest. This data was scraped from the 8260_54A.pdf in Appendix 2, attachment C. __8260.54a Test Data Origin.txt__ contains details of history and how the data was collected. If any changes to the test data are made then update this document too.

__Application test Results.txt__ is an implementation log tracking some my thoughts. The code comments and this document will help document how and why certain things are implemented, in order to get the expected test results.

TerpsTest is heavily dependent on [Boost::RegEx](http://www.boost/org/) to parse the CSV test data, so the Boost library must be installed with the RegEx module compiled. The initial goal of TerpsTest was to speed its development and library dependency was not taken into consideration, sorry.

By downloading and/or using this software you agree to the following terms of use:

Legal Stuff
-----------
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this software except in compliance with the License.
    You may obtain a copy of the License at
    
      http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

Which basically means: whatever you do, I can't be held accountable if something breaks.
