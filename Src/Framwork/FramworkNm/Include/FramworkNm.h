#ifndef _FRAMWORK_NM_CONFIG_H
#define _FRAMWORK_NM_CONFIG_H
#include "Config.h"

#ifdef _WIN32
#ifdef FRAMWORKNM_EXPORT
#define FRAMWORKNM_API			__declspec(dllexport)
#define FRAMWORKNM_CLASS		__declspec(dllexport)
#else
#define FRAMWORKNM_API			__declspec(dllimport)
#define FRAMWORKNM_CLASS		__declspec(dllimport)
#endif
#else
#define FRAMWORKNM_API
#define FRAMWORKNM_CLASS
#endif

#endif
