#ifndef CORE_H
#define CORE_H

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "Config.h"
#include "Consts.h"
#include "Logger.h"
#include "Utils.h"

#define DLLEXPORT extern "C" _declspec(dllexport)
// #define ENABLE_VERY_VERBOSE_LOGGING

#define TB_LOADER_MAJOR 1
#define TB_LOADER_MINOR 0
#define TB_LOADER_PATCH 1
#define TB_LOADER_METADATA ""

[[nodiscard]] const char* get_version_string();

#endif // CORE_H