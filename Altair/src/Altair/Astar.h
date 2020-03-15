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
	void astarAlgo(ImageGraph& imageGraph, int nodeX, int nodeY, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight);

private:

	// A struct used to represent the node as a x and y coordinate when passing the path back to the user (system)
	struct Point {
		int xCoord;
		int yCoord;
	};

	// Calculate the cost of the node based on the path (distance which needs to be driven to get to node)
	double calculateNodePathCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, double pathWeight, double elevationWeight);

	// Calculate the heuristics (Euclidian distance, Elevation)
	double calculateNodeCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, int goalX, int goalY, double elevationWeight, double euclidianWeight);

	// Open the nodes adjasent the current node
	void expandNode(ImageGraph& imageGraph, ANode& nodeCurrent, int x, int y, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight);

	void traceBackPath(ANode nodeStart, ANode nodeCurrent);

	void convertfinalSetToCleaned();

	void convertClosedSetToCleaned();

	void drawBackPath(ImageGraph& imageGraphArtist);

	ANode nodeStart;
	ANode nodeEnd;
	ANode nodeCurrent;

	const double SQRTWO = 1.414213562373095;

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