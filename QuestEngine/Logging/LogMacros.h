#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include "LogHandler.h"

// Loggers
namespace QuestEngine{
	namespace Logging {

		constexpr char DEFAULT_LOGGER[] = "QuestLogger";

	} // namespace Logging
} // namespace QuestEngine

#ifdef QUESTENGINE_CONFIG_DEBUG

#define QUEST_TRACE(...) if(spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER)->trace(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_DEBUG(...) if(spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER)->debug(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_INFO(...) if(spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER)->info(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_WARN(...) if(spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER)->warn(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_ERROR(...) if(spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER)->error(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_FATAL(...) if(spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestEngine::Logging::DEFAULT_LOGGER)->critical(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)

#else

#define QUEST_TRACE(...)
#define QUEST_DEBUG(...)
#define QUEST_INFO(...)
#define QUEST_WARN(...)
#define QUEST_ERROR(...)
#define QUEST_FATAL(...)

#endif