// TODO: Remove example class
#pragma once

#include "Core.h"
#include "Node.h"
#include "Log.h"

namespace Altair {

// Method must be public and static to support __declspec(dllexport)
ALTAIR_API void Print();

class ALTAIR_API Astar
{
public:

	Astar::Astar() {}

	Astar::~Astar() {}

	// Method must be public and static to support __declspec(dllexport)
	static double Run(int* nodeVector, int size);
};

}