## Change log for GeoFormulas

==========================
###0.2.1
####Date: (2016-07-03)

Features:
  - Remove C++ Boost dependency.
    - Limit GCC version to 4.9 and Clang version to 3.3, where C++11 Regex
      is supported.
    - Use std::bitset
    - Switch to regex_constants::EMAScript
    - Add support for versioning
    - CMake generator for Visual Studio works.
    - Example of creating VS2015 project with CMake:</br>
        ``cmake -G "Visual Studio 14 2015" ..\GeoFormulas``
    - Add changelog

Bug Fixes:
  - Fix regex pattern []. with [.]
  - Windows CMake and VS project tweaks


###0.2.0
####Date: (2016-07-01)

Features:
  - Update readme.md usage instructions with embedded images scrapped from
    old website.
  - Bump to VS2015 compiler.
  - Add CMake support for OS X and Linux.
  - Remove _stdcall calling convention.
  - Define variables in Conversion.h and GeoFormulas.h as const with k.
    prefixed to variable name (removes the function calls which returned
    the values).
  - Cleanup all library code, removes much code thrash, make variables const
    if possible, remove unnecessary variables.
  - All tests passing on Windows, OS X LLVM 7.30, Debian gcc 4.8.3.

Bug Fixes:
  - Switch to portable isnan function.
  - Fix ConvertDmsToDd stability issue exposed on Clang compiler.
    - now allows kSphereRadius to be calculated from sqrt formula.
  - Switch std::fmin to std::min for earlier versions of gcc.
  - Check and handle QNAN returned from FindLinearRoot.

Misc:
  - Move GeoFormula headers to include directory
  - Define kInverseFlattening to 20 significant digits. Previously calculated
    value was from a large precision calculator
  - kSphereRadius is now calculated as sqrt(kSemiMajorAxis * kSemiMinorAxis)
    Previous value was calculated with large precision calculator
  - Switch tabs to spaces in library and terps test code
  - Format code to Allman style
  - Update file comment and copyright blocks

### 0.1.1
#### Date: (2010-12-07)

Features:
  - Add Microsoft Excel VBA support
  - Add support for DLL builds

### 0.1.0
##### Date: (2010-07-14)

Initial commit of GeoFormulas

Features:
  - Implements WGS84 ellipsoid calculations from FAA document Order 8260.54A.
  - Implements TerpsTest to check WGS84 Ellipsoid calculations. Test data and
    expected results are publish in FAA Order 8260.54A Appendix 2,
    Attachment C.





