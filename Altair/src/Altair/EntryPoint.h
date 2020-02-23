#pragma once

#ifdef ALTAIR_PLATFORM_WINDOWS

extern Altair::Application* Altair::CreateApplication();

int main(int argc, char** argv)
{
	// Created on the heap
	auto app = Altair::CreateApplication();
	app->Run();
	delete app;
}

#endif