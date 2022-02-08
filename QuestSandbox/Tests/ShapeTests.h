#pragma once
#include "QuestEngine/API/EngineAPI.h"
#include <string>

namespace QuestSandbox::Tests {

	class ShapeTests {

	public:
		ShapeTests(const QuestEngine::API::QuestEngineAPI& engine_api);

		// Triangle
		void load_standard_triangle() const;
		void load_indexed_triangle() const;

		// Cube
		void load_standard_cube() const;
		void load_indexed_cube() const;

	private:
		const QuestEngine::API::QuestEngineAPI& m_engine_api;
		static const std::string m_base_shader_path;
	};

} // QuestSandbox::Tests