#include "pch.h"
#include "QuestWindow/Include/Window.h"

namespace WindowCreationTest {

	// ========== Fixtures ==========

	class OglWindowTestFixture : public testing::Test {

	protected:
		void SetUp() override {
			m_window = new QuestWindow::OpenGL::OGLWindow{ 1920, 1080, 3, 3 };
		}

		void TearDown() override {
			delete m_window;
		}

		static QuestWindow::OpenGL::OGLWindow* m_window;
	};

	QuestWindow::OpenGL::OGLWindow* OglWindowTestFixture::m_window = nullptr;



	// =============== Tests ===============

	TEST_F(OglWindowTestFixture, OglWindowConstruction_StandardArgs_SuccessfulObjCreation) {
		EXPECT_TRUE(m_window->get_window() != nullptr);
	}

	// ---- Move Constructor tests ---- 
	TEST_F(OglWindowTestFixture, OglWindowMove_STDMove_OrigObjInvalid) {
		QuestWindow::OpenGL::OGLWindow new_window{ std::move(*m_window) };
		EXPECT_TRUE(m_window->get_window() == nullptr);
	}

	TEST_F(OglWindowTestFixture, OglWindowMove_STDMove_NewObjValid) {
		const QuestWindow::OpenGL::OGLWindow new_window{ std::move(*m_window) };
		EXPECT_TRUE(new_window.get_window() != nullptr);
	}

} // namespace WindowCreationTest