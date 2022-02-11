#pragma once
#include <unordered_map>
#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::Resource {

	template<typename Key, typename Value>
	class TResource {

	public:
		template<typename... Args>
		void load(const Key& key, Args&&... args) {
			m_resource_map.try_emplace(key, std::forward<Args>(args)...);
		}

		void load(const Key& key, Value& value) {
			// Normally you can use the [] overload below.  However, the qc
			// check below prevents new objects from being added.  This is a
			// replacement to use in lieu of the below when adding new items.
			if(contains_key(key)) {
				*get_pointer(key) = std::move(value);
			} else {
				m_resource_map.emplace(key, std::move(value));
			}
		}

		template<typename... Args>
		void safe_load(const Key& key, Args&&... args) {
			if (!contains_key(key)) {
				load(key, std::forward<Args>(args)...);
			}
		}

		void safe_load(const Key& key, Value& value) {
			if(!contains_key(key)) {
				load(key, value);
			}
		}

		void unload(const Key& key) {
			m_resource_map.erase(key);
		}

		void unload_all() {
			m_resource_map.clear();
		}

		Value& operator[](const Key& key) {
			#ifdef DEBUG
				if(!contains_key(key)) {
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

		[[nodiscard]] auto begin() const {
			return m_resource_map.begin();
		}

		[[nodiscard]] auto end() const {
			return m_resource_map.end();
		}

		[[nodiscard]] bool contains_key(const Key& key) {
			return m_resource_map.count(key) > 0;
		}

	private:
		std::unordered_map<Key, Value> m_resource_map{};
	};

} // namespace QuestEngine::Resource