#pragma once

// Enable GEODLL for DLL builds of GeoFormulas, otherwise builds are static
#if defined(GEODLL)
#define GEOAPI __declspec(dllexport) 
#else
#define GEOAPI 
#endif