#pragma once
#include <exception>

namespace QuestEngine {
	namespace Logging {

		class LogHandlerExistsException final : public std::exception {
			[[nodiscard]] const char* what() const override {
				return "Log handler already exists.  Only a single log handler can exist (due to spd::shutdown() function)";
			}
		};

	} // namespace Interface
} // namespace QuestWindow