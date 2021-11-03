#pragma once

namespace QuestGraphicsCore {
	namespace Template {

		template <typename TraitType, typename HandleTypedef>
		class Handle {

		public:
			explicit Handle()
				:m_handle_is_initialized{ false },
				m_handle{ HandleTypedef{} }{
				generate();
			}

			~Handle() {
				destroy();
			}

			Handle(const Handle& source) = delete;
			Handle& operator=(const Handle& rhs) = delete;

			Handle(Handle&& source) noexcept
				:m_handle_is_initialized{ source.m_handle_is_initialized },
				m_handle{ source.m_handle }{
				reset(source);
			}

			Handle& operator=(Handle&& rhs) noexcept {
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

		private:
			void generate() {
				m_handle = TraitType::generate();
				m_handle_is_initialized = true;
			}

			void destroy() {
				if (m_handle_is_initialized) {
					TraitType::destroy(m_handle);
					reset(*this);
				}
			}

			static void reset(Handle& handle) {
				handle.m_handle_is_initialized = false;
				handle.m_handle = HandleTypedef{};
			}

			bool m_handle_is_initialized;
			HandleTypedef m_handle;

		};

	} // namespace Template
} // namespace QuestGraphicsCore