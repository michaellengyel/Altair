// TODO: Remove example class
#pragma once

#include "Core.h"

namespace Altair {

// Method must be public and static to support __declspec(dllexport)
class ALTAIR_API Visuals {
public:
	
	// Method must be public and static to support __declspec(dllexport)
	static int visualsTestFunction(int x, int y);

};

}