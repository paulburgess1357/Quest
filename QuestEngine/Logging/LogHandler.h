#pragma once
#include <vector>
#include <string>
#include "spdlog/spdlog.h"

namespace QuestEngine {
	namespace Logging {

		class LogHandler {

		public:
			LogHandler(const std::string& logger_name);
			LogHandler(const LogHandler& source) = delete;
			LogHandler(LogHandler&& source) = delete;

			LogHandler& operator=(const LogHandler& rhs) = delete;
			LogHandler& operator=(LogHandler&& rhs) = delete;

			~LogHandler();

		private:
			void check_if_exists() const;
			void create_stdout_color_sink();
			void add_logger(const std::string& logger_name);
			static void shutdown();

			std::vector<spdlog::sink_ptr> m_sink_ptrs{};
			bool m_log_handler_exists;
		};

	} // namespace Logging
} // namespace QuestEngine