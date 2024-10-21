#include <Razor.h>

class Sandbox : public Razor::Application
{
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Razor::Application* Razor::CreateApplication() {
	return new Sandbox();
}