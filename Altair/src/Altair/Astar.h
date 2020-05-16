// Class Bstar contains the A* algorithms functions and data

#pragma once

#ifndef Astar_h
#define Astar_h

#include "Core.h"
#include "Log.h"
#include "ANode.h"
#include "ImageGraph.h"

#include <vector>
#include <iterator>

namespace Altair {

class ALTAIR_API AStar {
public:

	// Default C'tor
	AStar();

	// Default Destructor
	~AStar();

	// Astar algorithm
	void run(ImageGraph& imageGraph, int nodeX, int nodeY, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight, double maxGrade);

	// Calculate the Path Length by summing all distances between the final path's nodes.
	void calculatePathLength(double verticalProportion, double horizontalProportion);

	// Calculate the Delta Elevation by summing all differenced between the final path's nodes.
	void calculateDeltaElevation();

	// Calculate the energy needed to traverse the final path using G, Mass, Rolling Resistance.
	void calculateEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion);

	// Calculate the energy needed to traverse the final path using G, Mass, Rolling Resistance without energy regeneration.
	void calculateNeededEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion);

private:

	// A struct used to represent the node as a x and y coordinate when passing the path back to the user (system)
	struct Point {
		int xCoord;
		int yCoord;
	};

	// Calculate the cost of the node based on the path (distance which needs to be driven to get to node)
	double calculateNodePathCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, int goalX, int goalY, double pathWeight, double elevationWeight);

	// Calculate the heuristics (Euclidian distance, Elevation)
	double calculateNodeCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight);

	// Open the nodes adjasent the current node
	void expandNode(ImageGraph& imageGraph, ANode& nodeCurrent, int x, int y, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight, double maxGrade);

	void traceBackPath(ANode nodeStart, ANode nodeCurrent);

	void convertfinalSetToCleaned();

	void convertClosedSetToCleaned();

	ANode nodeStart;
	ANode nodeEnd;
	ANode nodeCurrent;

	const double SQRTWO = 1.414213562373095;
	const double PI = 3.141592653589793;

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

	// Variable for holding the total length of the path
	double pathLength;

	// Variable for holding the delta elevation
	double deltaElevation;

	// Variable for holding the net energy
	double netEnergy;

	// Variable for holding the net needed energy
	double netNeededEnergy;

};

}

#endif