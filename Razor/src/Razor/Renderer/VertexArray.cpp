#include "rzpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "VertexArray.h"

namespace Razor
{
	Ref<VertexArray>VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
		RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}