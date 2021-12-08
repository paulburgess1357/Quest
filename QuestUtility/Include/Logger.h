#pragma once
#include "QuestUtility/Logging/LogHandler.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "QuestUtility/Logging/LogMacros.h"

namespace QuestUtility::Logging {
	inline extern constexpr char DEFAULT_LOGGER[] = "Default Logger";
	inline extern const LogHandler logHandler { DEFAULT_LOGGER };  // NOLINT(clang-diagnostic-exit-time-destructors)
} // namespace QuestUtility::Logging
