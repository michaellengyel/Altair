#pragma once

#ifdef ALTAIR_PLATFORM_WINDOWS

extern Altair::Application* Altair::CreateApplication();

int main(int argc, char** argv)
{
	Altair::Log::Init();
	ALTAIR_CORE_WARN("Initializind log!");
	ALTAIR_CORE_ERROR("Initializind log!");

	// Created on the heap
	auto app = Altair::CreateApplication();
	app->Run();
	delete app;
}

#endif