// Class Bstar contains the A* algorithms functions and data

#pragma once

#ifndef Astar_h
#define Astar_h

#include "Core.h"

#include <vector>
#include <iterator>
#include "ANode.h"
#include "ImageGraph.h"
//#include "ImageParser.h"

//using namespace std;

class ALTAIR_API AStar {
public:

	// Default C'tor
	AStar() {

	}

	// Default Destructor
	~AStar() {

	}

	// Astar algorithm
	void astarAlgo(ImageGraph& imageGraph, int nodeX, int nodeY, int goalX, int goalY, int pathWeight, int elevationWeight, int euclidianWeight);

private:

	struct Point {
		int xCoord;
		int yCoord;
	};

	int calculateNodePathCost(ANode& nodeCurrent, int pathWeight);

	int calculateNodeCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, int goalX, int goaleY, int elevationWeight, int euclidianWeight);

	void expandNode(ImageGraph& imageGraph, ANode& nodeCurrent, int x, int y, int goalX, int goalY, int pathWeight, int elevationWeight, int euclidianWeight);

	void traceBackPath(ANode nodeStart, ANode nodeCurrent);

	void convertfinalSetToCleaned();

	void convertClosedSetToCleaned();

	void drawBackPath(ImageGraph& imageGraphArtist);

	ANode nodeStart;
	ANode nodeEnd;
	ANode nodeCurrent;

	// Container for the OPEN set
	vector<ANode> openSet;

	// Container for the CLOSED set
	vector<ANode> closedSet;

	// Container for the FINAL set
	vector<ANode> finalSet;

public:

	// Container for FINAL set cleaned
	std::vector<Point> finalSetClean;

	// Container for CLOSED set cleaned
	std::vector<Point> closedSetClean;

};

#endif