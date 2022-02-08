// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include "QuestEngine/API/EngineAPI.h"

// Tests
#include "QuestSandbox/Tests/ShapeTests.h"

int main() {
    const QuestEngine::API::QuestEngineAPI engine_api;
	const QuestSandbox::Tests::ShapeTests shape_test { engine_api };

	shape_test.load_standard_cube();
	shape_test.load_indexed_cube();
	engine_api.run();
}