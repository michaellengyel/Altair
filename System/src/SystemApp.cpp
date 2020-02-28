#include <Altair.h>
#include <iostream>
#include <iostream>

namespace Altair {
	// TODO: Remove example code.
	ALTAIR_API void Print();
	ALTAIR_API Astar;
	// End example code
}

int main(int argc, char** argv) {

	// TODO: Remove example code.
	Altair::Log::Init();
	ALTAIR_CORE_WARN("Initializind log!");
	ALTAIR_CORE_ERROR("Initializind log!");

	Altair::Print();

	Altair::Astar a;

	int values[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	double result = a.Run(values, 11);
	std::cout << result << std::endl;
	// End example code

	return 0;
}