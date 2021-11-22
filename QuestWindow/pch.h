// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include "QuestWindow/Template/TWindow.h"
#include "QuestWindow/Interface/IWindow.h"
#include "QuestWindow/Interface/IWindowException.h"

#include "QuestWindow/OpenGL/OGLWindow.h"
#include "QuestWindow/OpenGL/OGLWindowException.h"

#include "QuestWindow/Input/InputManager.h"
#include "QuestWindow/Input/MouseManager.h"
#include "QuestWindow/Input/Keyboard.h"
#include "QuestWindow/Input/Mouse.h"

#include "QuestWindow/Include/Window.h"

#endif //PCH_H