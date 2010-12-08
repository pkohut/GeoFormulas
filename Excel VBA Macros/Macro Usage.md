Using GeoFormulas with Microsoft Excel VBA
=========================

Attached are new source files, an Excel Macro enabled workbook, an export Excel class file of all the macros in the workbook. Towards the bottom of the macro file (and in the Excel workbook) are some samples to illustrate using the macros to call into the new code. (ps, I had to rename the GeoFormulasDll.zip to GeoFormulasDll.piz, because it contains a DLL, and Google's security won't allow the zip to contain an exe).

The GeoFormulas code now creates a DLL which is used for both the TerpsTest code and the Excel workbook. A compiled release version of the DLL and the TerpsTest.exe is in the ReleaseDll directory. To use the DLL with an Excel workbook, the DLL must be in a searchable path on the computer, or if you prefer to hardcode the paths you can in the Excel workbook. Mostly the function declarations were cleaned up and updated to support creating the DLL. The DLL is standard Win32 and does not implement COM or ActiveX, so the code stays pretty clean and easy to follow.

For testing purposes I use Excel 2007, GeoFormulas.dll (32 bit), Window 7 (64 bit). First order is to enable the developer section on the Excel ribbon. This is done through the "Excel Options->Show Developer tab in Ribbon" check box.  After enabling, click "the developer tab -> Visual Basic" button. This will bring up the Visual Basic IDE within Excel. If you loaded the attached workbook, then clicking on the "This Workbook" in the project side window should so all the macro code.

Most of the macro code in the workbook is telling VBA how to communicate with the C++ DLL.  For instance, the DestVincenty function has a C++ definition of
    LLPoint _stdcall DestVincenty(const LLPoint & pt, double brng, double dist)

VBA needs to be told how to find and talk with the DLL function, this is done with a declaration

    Private Declare Function DestVincenty _
    Lib "GeoFormulas.dll" _
    Alias "?DestVincenty@GeoCalcs@@YG?AULLPOINT@1@ABU21@NN@Z" _
    (ByRef llPt As LLPoint, ByVal brng As Double, ByVal dist As Double) As LLPoint

Here we are telling VBA the macro function name to use is DestVincenty, and it reside in the GeoFormulas.dll. Since the path to GeoFormulas.dll is not hardcoded it must be in one of the search paths of the OS.  Next, the alias is the C++ name managing signature, which is needed to tell VBA exactly what the function name is the DLL is. Then comes the parameter declarations for the DestVincenty function, and finally its return type.

I've gone ahead and mapped all the functions in GeoFormuals.h and Conversions.h using the above method. Also, each of the C++ stuctures are mapped in the macro file as well. For instance, LLPoint structure in C++ is declared in VBA like so...

    Private Type LLPoint
       latitude As Double
       longitude As Double
    End Type

This will allow natural OO usage with all the functions. Here's an example call to DistVincenty from VBA,

    bVal = DistVincenty(llStart, llCenter, result)

where llStart and llCenter are dim'ed as LLPoint, result is dim'ed as InverseResult, and bVal is Boolean.

The definitions for CrsIntersect had to be named CrsIntersect1 and CrsIntersect2 (macro code only) to distinguish between the to function in C++. Also, the Mod function from the GeoFormula library is named Mod1 in VBA because of a name conflict with a built in VBA function call Mod.

There are 2 functions in GeoFormula's that pass arrays. These are PerpTangentPoints and FindLinearRoot. Those parameter that require an array need special handling in VBA, see the macros TestFindLinerarRoot and TestPerpTangentPoints for working examples.

