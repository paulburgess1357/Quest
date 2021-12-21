#pragma once
#include "QuestGLCore/Handle/Traits/Buffer.h" // Specialized move constructor
#include "QuestUtility/Include/Logger.h"

namespace QuestGLCore::Handle {

	template <typename TraitType, typename HandleTypedef>
	class HandleTemplate {

	public:
		template<typename... Args>
		explicit HandleTemplate(Args&&... args)
			:m_handle_is_initialized{ false },
			m_handle{ },
			m_trait{ std::forward<Args>(args)... }{
			create();
		}

		~HandleTemplate() {
			destroy();
		}

		HandleTemplate(const HandleTemplate& source) = delete;
		HandleTemplate& operator=(const HandleTemplate& rhs) = delete;

		HandleTemplate(HandleTemplate&& source) noexcept
			:m_handle_is_initialized{ source.m_handle_is_initialized },
			m_handle{ source.m_handle },
			m_trait{ source.m_trait }{
			reset(source);
		}

		HandleTemplate& operator=(HandleTemplate&& rhs) noexcept {
			if (this != &rhs) {
				this->destroy();
				this->m_handle_is_initialized = rhs.m_handle_is_initialized;
				this->m_handle = rhs.m_handle;
				this->m_trait = rhs.m_trait;
				reset(rhs);
			}
			return *this;
		}

		[[nodiscard]] HandleTypedef get_handle() const {
			return m_handle;
		}

		void bind() const {
			m_trait.bind(m_handle);
		}

		void unbind() const {
			m_trait.unbind();
		}

	private:
		void create() {
			m_handle = m_trait.create();
			m_handle_is_initialized = true;
			QUEST_TRACE("Creating Handle: {}", m_handle);
		}

		void destroy() {
			if (m_handle_is_initialized) {
				m_trait.destroy(m_handle);
				QUEST_TRACE("Destroying Handle: {}", m_handle);
				reset(*this);
			}
		}

		static void reset(HandleTemplate& handle) {
			handle.m_handle_is_initialized = false;
			handle.m_handle = HandleTypedef{};
			handle.m_trait = TraitType{ };
		}

		bool m_handle_is_initialized;
		HandleTypedef m_handle;
		TraitType m_trait;
	};

} // namespace QuestGLCore::Handle