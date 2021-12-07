#pragma once
#include <vector>
#include <string>
#include <atomic>
#include "spdlog/spdlog.h"

namespace QuestUtility {
	namespace Logging {

		class LogHandler {

		public:
			explicit LogHandler(const std::string& logger_name);
			LogHandler(const LogHandler& source) = delete;
			LogHandler(LogHandler&& source) = delete;

			LogHandler& operator=(const LogHandler& rhs) = delete;
			LogHandler& operator=(LogHandler&& rhs) = delete;

			~LogHandler();

		private:
			void create_stdout_color_sink();
			void add_logger(const std::string& logger_name);
			void startup_message() const;
			void shutdown_message() const;

			std::vector<spdlog::sink_ptr> m_sink_ptrs{};
			std::string m_logger_name;

			static void shutdown();
			static std::atomic_int m_log_handler_count;

		};

	} // namespace Logging
} // namespace QuestUtility