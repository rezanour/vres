#pragma once

#include <stdint.h>

#if defined(VRES_EXPORTS)
#define VRES_API __declspec(dllexport)
#else
#define VRES_API __declspec(dllimport)
#endif
