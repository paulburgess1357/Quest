# Quest
Quest is a collection of static libraries used for building the ECS Extra Life Game Engine v2 (to be known as Quest Engine). The following collection of projects/libraries focus on: Template programming, Strong exception guarantees, and RAII classes for various graphics API's. **This is a very early-stage repo**. The end goal is to have a collection of libraries across multiple graphics API's that offer compile time polymorphism.

As development of this repo continues, the above examples will be replaced by working classes/libraries to be used in other projects.  Eventually, each static library will be moved into its own repo.

### Dependencies
```
.\vcpkg install glfw3:x64-windows
.\vcpkg install assimp:x64-windows
.\vcpkg install entt:x64-windows
.\vcpkg install glm:x64-windows
.\vcpkg install stb:x64-windows
.\vcpkg install imgui[docking-experimental,opengl3-binding,glfw-binding]:x64-windows
.\vcpkg install glad:x64-windows
.\vcpkg install gtest:x64-windows
.\vcpkg install spdlog:x64-windows
```
