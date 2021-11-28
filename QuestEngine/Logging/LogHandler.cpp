#include "pch.h"
#include "LogHandler.h"
#include "LogHandlerException.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

// Based on: https://www.youtube.com/watch?v=DQCkMnMNFBI
//           https://github.com/gabime/spdlog/wiki/1.-QuickStart

namespace QuestEngine {
	namespace Logging {
		
		LogHandler::LogHandler(const std::string& logger_name)
			:m_log_handler_exists{ false } {
			check_if_exists();
			create_stdout_color_sink();
			add_logger(logger_name);
			m_log_handler_exists = true;
		}

		LogHandler::~LogHandler() {
			shutdown();
		}

		void LogHandler::check_if_exists() const {
			if(m_log_handler_exists) {
				throw LogHandlerExistsException();
			}
		}

		void LogHandler::create_stdout_color_sink() {
			const auto stdout_logger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			stdout_logger->set_pattern("%^[%Y-%m-%d %H:%M:%S] %v%$");
			m_sink_ptrs.push_back(stdout_logger);
		}

		void LogHandler::add_logger(const std::string& logger_name) {

			// Create logger (can output to various sinks)
			const auto logger = std::make_shared<spdlog::logger>(logger_name, m_sink_ptrs.begin(), m_sink_ptrs.end());

			// Set logger levels (trace, debug, error, fatal, etc.; in this case everything)
			// Trace would be lowest level
			logger->set_level(spdlog::level::trace);
			logger->flush_on(spdlog::level::trace);

			// Register
			spdlog::register_logger(logger);
		}

		void LogHandler::shutdown() {
			spdlog::shutdown();
		}

	} // namespace Logging
} // namespace QuestEngine