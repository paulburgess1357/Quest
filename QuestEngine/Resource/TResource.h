#pragma once
#include <unordered_map>
#include "QuestUtility/Include/Logger.h"
#include "QuestUtility/Logging/LogMacros.h"

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
			#ifdef DEBUG
				if(m_resource_map.count(key) == 0) {
					const std::string key_val = std::is_same_v<Key, std::string> ? key : "Key type is not string";
					QUEST_WARN("Key does not exist in map.  Unable to return reference.  Searched Key: " + key_val);
				}
			#endif
			return m_resource_map.find(key)->second;
		}

		Value* get_pointer(const Key& key) {
			Value* ptr = &m_resource_map.find(key)->second;
			#ifdef DEBUG
				const std::string key_val = std::is_same_v<Key, std::string> ? key : "Key type is not string";
				QUEST_WARN_CONDITION(ptr != nullptr, "Returning null pointer from resource.  Searched Key: " + key_val);
			#endif
			return ptr;
		}

	private:
		std::unordered_map<Key, Value> m_resource_map{};
	};

} // namespace QuestEngine::Resource