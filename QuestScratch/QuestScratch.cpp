// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include "QuestEngine/API/EngineAPI.h"
#include "QuestGLCore/VertexData/VertexData.h"
#include "QuestUtility/String/FileToString.h"
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Model/Model.h

int main(){

    const QuestEngine::API::QuestEngineAPI engine_api;

 //   std::string vertex_string =   QuestUtility::String::FileToString::load("../Resources/Shaders/Triangle/TriangleVertex.glsl");
 //   std::string fragment_string = QuestUtility::String::FileToString::load("../Resources/Shaders/Triangle/TriangleFragment.glsl");

 //   engine_api.load_shader("TriangleShader", {
 //   	std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, vertex_string },
 //   	std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, fragment_string }
 //   });


 //   // Standard model (Single Array Buffer) Test ==========================================================================================
 //   std::vector<float> vertices = {
 //       // first triangle
 //       -0.5f, -0.5f, 0.0f, // left  
 //        0.5f, -0.5f, 0.0f, // right 
 //        0.0f,  0.5f, 0.0f  // top   
 //   };
 //   
 //   QuestGLCore::VertexData::VertexData vertex_data{ GL_ARRAY_BUFFER };
 //   vertex_data.load_data<float>(vertices, { 3 });

 //   // Move vertex data into mesh
 //  QuestGLCore::Model::Mesh standard_mesh { std::move(vertex_data) };

	//// Move mesh into vector
 //  std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::VertexData>> meshes;
 //  meshes.push_back(std::move(standard_mesh));

 //  // Move vector of mesh's into model
 //  const auto& shader_program = engine_api.get_shader("TriangleShader");
 //  engine_api.load_model("Test Model", shader_program, meshes);


 //  // QuestGLCore::Model::Model<QuestGLCore::VertexData::VertexData> model_test{ shader_program, std::move(meshes) };


 //  //  Indexed model (VBO + EBO) Test =====================================================================================================
 //  vertices = {
 //   0.5f,  0.5f, 0.0f,  // top right
 //   0.5f, -0.5f, 0.0f,  // bottom right
 //  -0.5f, -0.5f, 0.0f,  // bottom left
 //  -0.5f,  0.5f, 0.0f   // top left 
 //  };
 //  std::vector<unsigned int> indices = {  // note that we start from 0!
 //      0, 1, 3,   // first triangle
 //      1, 2, 3    // second triangle
 //  };
 //  QuestGLCore::VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER };
 //  vertex_data_element.load_data(vertices, indices, { 3 });

 //  // Move vertex data into mesh
 //  QuestGLCore::Model::Mesh indexed_mesh{ std::move(vertex_data_element) };

 //  // Move mesh into vector
 //  std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::IndexedVertexData>> indexed_meshes;
 //  indexed_meshes.push_back(std::move(indexed_mesh));

 //  // Move vector of mesh's into model
 //  QuestGLCore::Model::Model<QuestGLCore::VertexData::IndexedVertexData> indexed_model_test { shader_program, std::move(indexed_meshes) };


}
