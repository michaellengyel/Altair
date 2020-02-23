#pragma once

#include "Core.h"

namespace Altair {

	class ALTAIR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}