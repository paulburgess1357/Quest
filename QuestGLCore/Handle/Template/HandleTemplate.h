#pragma once
#include "QuestUtility/Include/Logger.h"

namespace QuestGLCore::Handle {

	template <typename TraitType, typename HandleTypedef>
	class HandleTemplate {

	public:
		explicit HandleTemplate(const bool init = true)
			:m_handle_is_initialized{ false },
			m_handle{ HandleTypedef{} }{
			if(init) {
				create();
			}
		}

		~HandleTemplate() {
			destroy();
		}

		HandleTemplate(const HandleTemplate& source) = delete;
		HandleTemplate& operator=(const HandleTemplate& rhs) = delete;

		HandleTemplate(HandleTemplate&& source) noexcept
			:m_handle_is_initialized{ source.m_handle_is_initialized },
			m_handle{ source.m_handle }{
			reset(source);
		}

		HandleTemplate& operator=(HandleTemplate&& rhs) noexcept {
			if (this != &rhs) {
				this->destroy();
				this->m_handle_is_initialized = rhs.m_handle_is_initialized;
				this->m_handle = rhs.m_handle;
				reset(rhs);
			}
			return *this;
		}

		[[nodiscard]] HandleTypedef get_handle() const {
			return m_handle;
		}

		void bind() const {
			TraitType::bind(m_handle);
		}

		void unbind() const {
			TraitType::unbind();
		}

	private:
		void create() {
			m_handle = TraitType::create();
			m_handle_is_initialized = true;
			QUEST_TRACE("Creating Handle: {}", m_handle);
		}

		void destroy() {
			if (m_handle_is_initialized) {
				TraitType::destroy(m_handle);
				QUEST_TRACE("Destroying Handle: {}", m_handle);
				reset(*this);
			}
		}

		static void reset(HandleTemplate& handle) {
			handle.m_handle_is_initialized = false;
			handle.m_handle = HandleTypedef{};
		}

		bool m_handle_is_initialized;
		HandleTypedef m_handle;

	};




} // namespace QuestGLCore::Handle