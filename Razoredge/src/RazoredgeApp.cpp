#include <Razor.h>
//--------ENtry point-------

#include <Razor/Core/EntryPoint.h>
//--------------------

#include "EditorLayer.h"

namespace Razor{

	class Razoredge : public Application
	{
	public:
		Razoredge()
			:Application("Razor Edge")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~Razoredge() {

		}
	};

	Application* CreateApplication() {
		return new Razoredge();
	}
}