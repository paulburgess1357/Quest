// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include "QuestEngine/API/Neutral/EngineAPI.h"

// Tests
#include "QuestSandbox/Tests/ShapeTests.h"

int main() {
    QuestEngine::API::EngineAPI engine_api;
	const QuestSandbox::Tests::ShapeTests shape_test { engine_api };

	//shape_test.load_standard_shape();
	// shape_test.load_indexed_shape();
	// shape_test.load_normals_texture_indexed_shape_blinn_phong();
	// shape_test.g_buffer_lighting_test();
	shape_test.g_buffer_lighting_test_pointlight_mesh_volume();

	engine_api.run();
}