#pragma once
#include "QuestEngine/API/EngineAPI.h"

namespace QuestSandbox::Tests {

	class TriangleTests {

	public:
		TriangleTests(const QuestEngine::API::QuestEngineAPI* engine_api);
		void load_standard_triangle() const;
		void load_indexed_triangle() const;

	private:
		const QuestEngine::API::QuestEngineAPI* m_engine_api;
		static const std::string m_vertex_str;
		static const std::string m_fragment_str;

	};

} // QuestSandbox::Tests