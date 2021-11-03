#pragma once

namespace QuestGraphicsCore {
	namespace Template {

		template <typename HandleType, typename TraitType, typename HandleTypedef>
		class Bind {

		public:
			explicit Bind(const HandleType& handle_template_type) {
				bind(handle_template_type.get_handle());
			}
			~Bind() {
				unbind();
			}

			Bind(Bind&& source) = delete;
			Bind& operator=(Bind&& source) = delete;

			Bind(const Bind& source) = delete;
			Bind& operator=(const Bind& source) = delete;

			void bind(const HandleTypedef& handle) const {
				TraitType::bind(handle);
			}

			void unbind() const {
				TraitType::unbind();
			}

		};

	} // namespaceTemplate
} // namespace QuestGraphicsCore