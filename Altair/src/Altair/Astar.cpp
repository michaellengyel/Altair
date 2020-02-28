#include "Astar.h"
#include <vector>

namespace Altair {

void Print() {
	ALTAIR_CORE_TRACE("Calling Print()");
}


void Astar::Run()
{
	ALTAIR_CORE_TRACE("Calling Run()");
}

double Astar::bubbleSort(int* nodeVector, int size) {

	double mixed = 0;

	std::vector<Node> nodes;
	for (int i = 0; i < size/3; i++) {
		Node node(*(nodeVector + 0), *(nodeVector + 1), *(nodeVector + 2));
		ALTAIR_CORE_TRACE("Creating Node");
		nodes.push_back(node);
	}

	for (int i = 0; i < nodes.size(); i++) {
		mixed += nodes.at(i).absoluteLength();
	}

	return mixed;
}


}