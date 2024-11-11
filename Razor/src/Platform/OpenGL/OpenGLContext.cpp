#include "rzpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>


namespace Razor {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RZ_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		RZ_PROFILE_FUNCTION();


		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		RZ_CORE_INFO("OpenGL Info:");
		RZ_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		RZ_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		RZ_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		//RZ_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}
	void OpenGLContext::SwapBuffer()
	{
		RZ_PROFILE_FUNCTION();


		glfwSwapBuffers(m_WindowHandle);

	}

}
