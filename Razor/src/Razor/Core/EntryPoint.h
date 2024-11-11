#pragma once

#ifdef RZ_PLATFORM_WINDOWS



extern Razor::Application* Razor::CreateApplication();

int main(int argc, char** argv) {

	Razor::Log::Init();

	RZ_PROFILE_BEGIN_SESSION("Startup", "RazorProfile-Startup.json");
	auto app = Razor::CreateApplication();
	RZ_PROFILE_END_SESSION();



	RZ_PROFILE_BEGIN_SESSION("Runtime", "RazorProfile-Runtime.json");
	app->Run();
	RZ_PROFILE_END_SESSION();

	RZ_PROFILE_BEGIN_SESSION("Shutdown", "RazorProfile-Shutdown.json");
	delete app;
	RZ_PROFILE_END_SESSION();

}

#endif