#pragma once

//qt  dll
//#include <QtCore/qglobal.h>
//
//#ifndef BUILD_STATIC
//# if defined(BLCOKSAMPLE_LIB)
//#  define BLCOKSAMPLE_EXPORT Q_DECL_EXPORT
//# else
//#  define BLCOKSAMPLE_EXPORT Q_DECL_IMPORT
//# endif
//#else
//# define BLCOKSAMPLE_EXPORT
//#endif




//win32 dll
#ifdef WIN32
#ifdef BLCOKSAMPLE_LIB
#define BLCOKSAMPLE_EXPORT __declspec(dllexport)
#else
#define BLCOKSAMPLE_EXPORT __declspec(dllimport)

#endif

//#define CALLBACK __stdcall

#else

#define BLCOKSAMPLE_EXPORT
//#define CALLBACK
#endif




