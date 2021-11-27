#pragma once
#include "QuestLog/Include/Log.h"

namespace QuestEngine {

#ifndef QUESTENGINE_CONFIG_RELEASE
#define QUEST_TRACE(...) if(spdlog::get(QUEST_DEFAULT_LOGGER_NAME) != nullptr) {stdlog::get(QUEST_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__)}
#else
#define QUEST_TRACE(...) (void)0
#endif

} // namespace QuestEngine
