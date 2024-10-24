#pragma once

#ifdef RZ_PLATFORM_WINDOWS



extern Razor::Application* Razor::CreateApplication();

int main(int argc, char** argv) {

	Razor::Log::Init();

	RZ_CORE_WARN("Initialzed log");

	auto app = Razor::CreateApplication();
	app->Run();
	delete app;
}

#endif