/** @file nertc_base.h
 * @brief  Defines macro output. The file only defines macro output instead of anything else.
 * @copyright (c) 2015-2019, NetEase Inc. All rights reserved.
 */

#ifndef NERTC_BASE_H
#define NERTC_BASE_H

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#define NERTC_UE_CALL __cdecl
#define NERTC_UE_API extern "C" __declspec(dllexport)
#elif defined(__APPLE__)
#define NERTC_UE_API __attribute__((visibility("default"))) extern "C"
#define NERTC_UE_CALL
#elif defined(__ANDROID__) || defined(__linux__)
#define NERTC_UE_API extern "C" __attribute__((visibility("default")))
#define NERTC_UE_CALL
#else
#define NERTC_UE_API extern "C"
#define NERTC_UE_CALL
#endif

#if defined __GNUC__
#define NERTC_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define NERTC_DEPRECATED __declspec(deprecated)
#else
#define NERTC_DEPRECATED
#endif

#endif
