#pragma once
#include <unordered_map>

namespace QuestEngine::Resource {

	template<typename Key, typename Value>
	class TResource {

	public:
		template<typename... Args>
		void load(const Key& key, Args&&... args) {
			m_resource_map.try_emplace(key, std::forward<Args>(args)...);
		}

		void unload(const Key& key) {
				m_resource_map.erase(key);
		}

		void unload_all() {
			m_resource_map.clear();
		}

		Value& operator[](const Key& key) {
			return m_resource_map.find(key)->second;
		}

		Value* get_pointer(const Key& key) {
			return &m_resource_map.find(key)->second;
		}

	private:
		std::unordered_map<Key, Value> m_resource_map{};
	};


} // namespace QuestEngine::Resource