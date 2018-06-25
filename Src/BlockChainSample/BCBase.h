#pragma once



#ifdef WIN32
#ifdef BCSAMPLE_LIB
#define BCSAMPLE_EXPORT __declspec(dllexport)
#else
#define BCSAMPLE_EXPORT __declspec(dllimport)

#endif

//#define CALLBACK __stdcall

#else

#define BCSAMPLE_EXPORT
//#define CALLBACK




#endif