#include "pch.h"
#include "LogHandler.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <iostream>

namespace QuestUtility {
	namespace Logging {

		int LogHandler::m_log_handler_count{ 0 };

		LogHandler::LogHandler(const std::string& logger_name)
			:m_logger_name{ logger_name } {
			std::cout << "Initializing Logger: " << m_logger_name << std::endl;
			create_stdout_color_sink();
			add_logger(logger_name);
			m_log_handler_count++;
		}

		LogHandler::~LogHandler() {
			m_log_handler_count--;
			if(m_log_handler_count == 0) {
				shutdown();
			}
		}

		void LogHandler::create_stdout_color_sink() {
			const auto stdout_logger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			stdout_logger->set_pattern("%^[%H:%M:%S.%e] %v%$");
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
} // namespace QuestUtility