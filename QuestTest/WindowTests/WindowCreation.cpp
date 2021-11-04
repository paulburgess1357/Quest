#include "pch.h"
#include "QuestWindow/Include/Window.h"

namespace WindowCreationTest {

	// ========== Fixtures ==========

	class OglWindowTestFixture : public testing::Test {

	protected:
		static void SetUpTestCase();
		static void TearDownTestCase();

		static QuestWindow::OpenGL::OGLWindow* m_window;
	};

	QuestWindow::OpenGL::OGLWindow* OglWindowTestFixture::m_window = nullptr;

	void OglWindowTestFixture::SetUpTestCase() {
		m_window = new QuestWindow::OpenGL::OGLWindow{ 1920, 1080, 3, 3 };
	}

	void OglWindowTestFixture::TearDownTestCase() {
		delete m_window;
	}


	// ========== Tests ==========

	TEST_F(OglWindowTestFixture, OglWindowConstruction_StandardArgs_SuccessfulObjCreation) {
		EXPECT_TRUE(m_window->get_window() != nullptr);
	}

} // namespace WindowCreationTest