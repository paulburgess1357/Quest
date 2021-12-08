#pragma once
#include "spdlog/spdlog.h"

// To add logger:
// Project -> Properties -> Select Debug Under C++ Select Preprocessor:
// Type: QUESTLOGGER into Preprocessor
// This is PER project.  If its not defined in a project, it won't be used.

#ifdef QUESTLOGGER

#define QUEST_BREAK __debugbreak(); // Windows Only  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_TRACE(...) if(spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER)->trace(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_DEBUG(...) if(spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER)->debug(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_INFO(...) if(spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER)->info(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_WARN(...) if(spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER)->warn(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_ERROR(...) if(spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER)->error(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_FATAL(...) if(spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER) != nullptr) {spdlog::get(QuestUtility::Logging::DEFAULT_LOGGER)->critical(__VA_ARGS__);}  // NOLINT(cppcoreguidelines-macro-usage)
#define QUEST_ASSERT(assert_check, message_if_false) if(!(assert_check)){ QUEST_FATAL("ASSERT: {}\n\t{}\n\tin file: {}\n\ton line: {}", #assert_check, message_if_false, __FILE__, __LINE__); QUEST_BREAK }  // NOLINT(cppcoreguidelines-macro-usage)

#else

#define QUEST_TRACE(...)
#define QUEST_DEBUG(...)
#define QUEST_INFO(...)
#define QUEST_WARN(...)
#define QUEST_ERROR(...)
#define QUEST_FATAL(...)
#define QUEST_ASSERT(...)

#endif