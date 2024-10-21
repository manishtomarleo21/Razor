#pragma once

#ifdef RZ_PLATFORM_WINDOWS



extern Razor::Application* Razor::CreateApplication();

int main(int argc, char** argv) {
	auto app = Razor::CreateApplication();
	app->Run();
	delete app;
}

#endif