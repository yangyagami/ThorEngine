#ifndef THOR_PCH_H
#define THOR_PCH_H

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#define SPDLOG_NO_SOURCE_LOC
#include "spdlog/spdlog.h"

#endif
