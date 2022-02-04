// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include "QuestEngine/API/EngineAPI.h"

// Tests
#include "QuestSandbox/Tests/ShapeTests.h"

int main() {
    const QuestEngine::API::QuestEngineAPI engine_api;
	const QuestSandbox::Tests::ShapeTests triangle_test { engine_api };
	triangle_test.load_standard_triangle();
	// triangle_test.load_indexed_triangle();
	engine_api.run();
}


//GLenum err;
//while ((err = glGetError()) != GL_NO_ERROR) {
//	std::cerr << "OpenGL error: " << err << std::endl;
//}