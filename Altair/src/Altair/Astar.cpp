// Preprocessor used to remove logging from UnitTest Project.
// #define UNIT_TEST

#include "AStar.h"

namespace Altair {

AStar::AStar() : pathLength(0.0), deltaElevation(0.0), netEnergy(0.0), netNeededEnergy(0.0) {

}

AStar::~AStar() {

}

void AStar::run(ImageGraph& imageGraph, int nodeX, int nodeY, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight, double maxGrade) {

	ALTAIR_CORE_TRACE("Starting A-Star Algorithm.");

	// Initializing the Start and End node:
	nodeStart = ANode(nodeX, nodeY, nodeX, nodeY, imageGraph.getPixelValue(nodeX, nodeY));
	nodeEnd = ANode(goalX, goalY, 0, 0, imageGraph.getPixelValue(goalX, goalY));

	// Adding the initial node to the openSet:
	openSet.push_back(nodeStart);

	// Repeat
	while (!openSet.empty()) {

		// Find the lowest cost node in the openSet
		nodeCurrent = openSet.at(0);
		for (int i = 0; i < openSet.size(); i++) {
			if (nodeCurrent.getNodeCost() > openSet.at(i).getNodeCost()) {
				nodeCurrent = openSet.at(i);
			}
		}

		// Artist
		//imageGraphArtist.imageDrawLine(nodeStart.getNodeX(), nodeStart.getNodeY(), nodeStart.getNodeX(), nodeStart.getNodeY(), 0, 0, 255, 1);
		//imageGraphArtist.imageDrawLine(nodeEnd.getNodeX(), nodeEnd.getNodeY(), nodeEnd.getNodeX(), nodeEnd.getNodeY(), 0, 0, 255, 1);
		//imageGraphArtist.imageDrawLine(nodeCurrent.getNodeX(), nodeCurrent.getNodeY(), nodeCurrent.getNodeX(), nodeCurrent.getNodeY(), 0, 255, 0, 1);
		//imageParserArtist.userResize(4);
		//imageGraphArtist.imageShow("Lidar Based Topologial Terrain Map");
		//imageParserArtist.userResize(1);
		//imageGraphArtist.userWaitKey(1, 'c');

		// Breaking condition: if nodeCurrent == nodeEnd then break
		if (nodeCurrent.getNodeX() == nodeEnd.getNodeX() && nodeCurrent.getNodeY() == nodeEnd.getNodeY()) {
			closedSet.push_back(nodeCurrent);
			break;
		}

		// Add the current node to the closed set 
		closedSet.push_back(nodeCurrent);

		// RIGHT
		expandNode(imageGraph, nodeCurrent, 1, 0, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// TOP RIGHT
		expandNode(imageGraph, nodeCurrent, 1, -1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// TOP
		expandNode(imageGraph, nodeCurrent, 0, -1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// TOP LEFT
		expandNode(imageGraph, nodeCurrent, -1, -1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// LEFT
		expandNode(imageGraph, nodeCurrent, -1, 0, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// BOTTOM LEFT
		expandNode(imageGraph, nodeCurrent, -1, 1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// BOTTOM
		expandNode(imageGraph, nodeCurrent, 0, 1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
		// BOTTOM RIGHT
		expandNode(imageGraph, nodeCurrent, 1, 1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);


		// If a node has been expanded, erase from open set
		for (int i = 0; i < openSet.size(); i++) {
			if (nodeCurrent.getNodeX() == openSet.at(i).getNodeX() && nodeCurrent.getNodeY() == openSet.at(i).getNodeY()) {
				openSet.erase(openSet.begin() + i);
				// break;
			}
		}

		// Keeping track of open and closed setSize
		//cout << openSet.size() << ", " << closedSet.size() << endl;
		ALTAIR_CORE_INFO("OpenSet: {0}, ClosedSet: {1}", openSet.size(), closedSet.size());

	}

	// In case of finding a path
	if (nodeCurrent.getNodeX() == nodeEnd.getNodeX() && nodeCurrent.getNodeY() == nodeEnd.getNodeY()) {
		ALTAIR_CORE_TRACE("Finishing A-Star Algorithm.");

		ALTAIR_CORE_TRACE("Tracing Back Final Path.");
		traceBackPath(nodeStart, nodeCurrent);

		ALTAIR_CORE_TRACE("Generating Cleaned Final Set.");
		convertfinalSetToCleaned();

		ALTAIR_CORE_TRACE("Generating Closed Final Set.");
		convertClosedSetToCleaned();
	}
	// In case of no path existing
	else {
		ALTAIR_CORE_ERROR("No Solution Exists.");

		ALTAIR_CORE_TRACE("Tracing Back Final Path.");
		//traceBackPath(nodeStart, nodeCurrent);
		finalSet.empty();

		ALTAIR_CORE_TRACE("Generating Cleaned Final Set.");
		convertfinalSetToCleaned();

		ALTAIR_CORE_TRACE("Generating Closed Final Set.");
		convertClosedSetToCleaned();
	}


	//drawBackPath(imageGraph);

}

double AStar::calculateNodePathCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, double pathWeight, double elevationWeight) {

	bool xAdjacent = (nodeCurrent.getNodeX() == node.getNodeX());
	bool yAdjacent = (nodeCurrent.getNodeY() == node.getNodeY());

	double nodePathCost = nodeCurrent.getNodePathCost();
	int nodeElevation = node.getElevation();
	int nodeCurrentElevation = nodeCurrent.getElevation();
	double deltaNodeElevationPow = pow((nodeElevation - nodeCurrentElevation), 2);

	// Testing if elevationWeight should not be used as a heuristic.
	nodePathCost += (static_cast<double>(abs(node.getElevation() - nodeCurrent.getElevation())) * elevationWeight);

	// If node is next to parent node (1) plus the delta elevation
	if (xAdjacent || yAdjacent) {
		// Where 1 is pow(1, 2)
		nodePathCost += sqrt(1 + deltaNodeElevationPow);
	}
	// Else its diagonal (1.4) plus the delta elevation
	else {
		// Where 2 is pow(1.414, 2)
		nodePathCost += sqrt(2 + deltaNodeElevationPow);
	}

	return nodePathCost * pathWeight;
}

double AStar::calculateNodeCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, int goalX, int goalY, double elevationWeight, double euclidianWeight) {

	double nodeCost = 0;
	nodeCost = nodeCurrent.getNodePathCost();

	// Calculating the height cost
	// nodeCost += (static_cast<double>(abs(node.getElevation() - nodeCurrent.getElevation())) * elevationWeight);

	// Calculating the distance cost
	nodeCost += ((sqrt(pow(node.getNodeX() - goalX, 2) + pow(node.getNodeY() - goalY, 2))) * euclidianWeight);

	return nodeCost;
}

void AStar::expandNode(ImageGraph& imageGraph, ANode& nodeCurrent, int x, int y, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight, double maxGrade) {

	// local variables:
	int nodeCurrentX = nodeCurrent.getNodeX();
	int nodeCurrentY = nodeCurrent.getNodeY();

	// Check if node to be created is not outside the boundary of the image
	bool rightFree = (nodeCurrentX + x < imageGraph.getImageWidth());
	bool topFree = (nodeCurrentY + y >= 0);
	bool leftFree = (nodeCurrentX + x >= 0);
	bool bottomFree = (nodeCurrentY + y < imageGraph.getImageHeight());

	// Execute check
	if ((rightFree && topFree) && (leftFree && bottomFree)) {

		// TODO: Refactor this following if statement as a function.
		// Check if node to be create has a steepness above a treshhold defined as y/x aka vertical/horizontal
		// This should only be a restricition for uphill
		// Value can never be 1, so '1' is used to diactivat the calculations
		if (maxGrade != 1) {

			bool xAdjacent = (nodeCurrentX == imageGraph.getPixelValue(nodeCurrentX + x, nodeCurrentY + y));
			bool yAdjacent = (nodeCurrentY == imageGraph.getPixelValue(nodeCurrentX + x, nodeCurrentY + y));

			//double nodePathCost = nodeCurrent.getNodePathCost();
			int nodeElevation = imageGraph.getPixelValue(nodeCurrentX + x, nodeCurrentY + y);
			int nodeCurrentElevation = nodeCurrent.getElevation();
			int deltaNodeElevation = abs(nodeElevation - nodeCurrentElevation);
			//double deltaNodeElevationPow = pow((nodeElevation - nodeCurrentElevation), 2);

			// If node is next to parent node (1) plus the delta elevation
			if (xAdjacent || yAdjacent) {
				// Where 1 is pow(1, 2)
				pathLength = sqrt(pow((1 * pathWeight), 2) + pow((deltaNodeElevation * elevationWeight), 2));
			}
			// Else its diagonal (1.4) plus the delta elevation
			else {
				// Where 2 is pow(1.414, 2)
				pathLength = sqrt(pow((SQRTWO * pathWeight), 2) + pow((deltaNodeElevation * elevationWeight), 2));
			}

			double currentGrade = deltaNodeElevation / pathLength;

			if (currentGrade >= maxGrade) {
				// If grade it steeper then maxGrade, exit the function, do not expand the node.
				return;
			}
		}

		// Iterate through closed Set to check if the node we are about to create has already been expanded.
		bool nodeIsExpended = false;
		int sizeClosed = closedSet.size() - 1;
		for (int i = sizeClosed; i >= 0; i--) {
			bool xClosedCoordsMatch = (closedSet.at(i).getNodeX() == nodeCurrentX + x);
			bool yClosedCoordsMatch = (closedSet.at(i).getNodeY() == nodeCurrentY + y);
			if (xClosedCoordsMatch && yClosedCoordsMatch) {
				nodeIsExpended = true;
				break;
			}
		}

		// If nodeIsExpended is false, check if it is on the open List
		bool nodeIsOpened = false;
		int openedNodeID = 0;
		int sizeOpen = openSet.size() - 1;
		if (!nodeIsExpended) {
			for (int i = sizeOpen; i >= 0; i--) {
				bool xOpenCoordsMatch = (openSet.at(i).getNodeX() == nodeCurrentX + x);
				bool yOpenCoordsMatch = (openSet.at(i).getNodeY() == nodeCurrentY + y);
				if (xOpenCoordsMatch && yOpenCoordsMatch) {
					nodeIsOpened = true;
					openedNodeID = i;
					break;
				}
			}
			// Parent and child node states (todo)

			// Create a new node
			ANode node = ANode(nodeCurrentX + x, nodeCurrentY + y, nodeCurrentX, nodeCurrentY, imageGraph.getPixelValue(nodeCurrentX + x, nodeCurrentY + y));
			node.setNodePathCost(calculateNodePathCost(imageGraph, nodeCurrent, node, pathWeight, elevationWeight));
			node.setNodeCost(calculateNodeCost(imageGraph, nodeCurrent, node, goalX, goalY, elevationWeight, euclidianWeight));
			// Node states
			bool xCoordsMatch = (openSet.at(openedNodeID).getNodeX() == nodeCurrentX + x);
			bool yCoordsMatch = (openSet.at(openedNodeID).getNodeY() == nodeCurrentY + y);
			bool newNodeGreater = (openSet.at(openedNodeID).getNodeCost() > node.getNodeCost());
			bool newNodeLesser = (openSet.at(openedNodeID).getNodeCost() < node.getNodeCost());

			// Check if node already exists, if it does and is less efficient, replace
			if ((xCoordsMatch && yCoordsMatch) && newNodeGreater) {
				openSet.at(openedNodeID) = node;
			}
			// If node already exists, and is more efficient, do nothing
			else if ((xCoordsMatch && yCoordsMatch) && newNodeLesser) {
				// Do nothing
			}
			// if it does not exit, add to open set
			else {
				openSet.push_back(node);
			}
		}
		// If nodeIsExpended is true, check if it can be replaced with a more efficient replacement?
		else if (nodeIsExpended) {
			// Do nothing
		}
	}
	else {
		// Do Nothing 
	}
}

void AStar::traceBackPath(ANode nodeStart, ANode nodeCurrent) {

	bool startReached = false;
	finalSet.push_back(nodeCurrent);

	while (!startReached) {
		for (int i = 0; i < closedSet.size(); i++) {
			if (nodeCurrent.getParentX() == closedSet.at(i).getNodeX() && nodeCurrent.getParentY() == closedSet.at(i).getNodeY()) {
				finalSet.push_back(closedSet.at(i));
				nodeCurrent = closedSet.at(i);
				break;
			}
		}
		if (nodeCurrent.getParentX() == nodeStart.getNodeX() && nodeCurrent.getParentY() == nodeStart.getNodeY()) {
			startReached = true;
		}
	}

	finalSet.push_back(nodeStart);

}

void AStar::convertfinalSetToCleaned() {
	for (int i = 0; i < finalSet.size(); i++) {
		Point point;
		point.xCoord = finalSet.at(i).getNodeX();
		point.yCoord = finalSet.at(i).getNodeY();
		finalSetClean.push_back(point);
	}
}

void AStar::convertClosedSetToCleaned() {
	for (int i = 0; i < closedSet.size(); i++) {
		Point point;
		point.xCoord = closedSet.at(i).getNodeX();
		point.yCoord = closedSet.at(i).getNodeY();
		closedSetClean.push_back(point);
	}
}

void AStar::calculatePathLength(double verticalProportion, double horizontalProportion) {
	
	// Check if final set is empty or not
	if (!finalSet.empty()) {

		for (int i = 1; i < finalSet.size(); i++) {

			bool xAdjacent = (finalSet.at(i - 1).getNodeX() == finalSet.at(i).getNodeX());
			bool yAdjacent = (finalSet.at(i - 1).getNodeY() == finalSet.at(i).getNodeY());

			//double nodePathCost = nodeCurrent.getNodePathCost();
			int nodeElevation = finalSet.at(i - 1).getElevation();
			int nodeCurrentElevation = finalSet.at(i).getElevation();
			int deltaNodeElevation = abs(nodeElevation - nodeCurrentElevation);
			//double deltaNodeElevationPow = pow((nodeElevation - nodeCurrentElevation), 2);

			// If node is next to parent node (1) plus the delta elevation
			if (xAdjacent || yAdjacent) {
				// Where 1 is pow(1, 2)
				pathLength += sqrt(pow((1 * horizontalProportion), 2) + pow((deltaNodeElevation * verticalProportion), 2));
			}
			// Else its diagonal (1.4) plus the delta elevation
			else {
				// Where 2 is pow(1.414, 2)
				pathLength += sqrt(pow((SQRTWO * horizontalProportion), 2) + pow((deltaNodeElevation * verticalProportion), 2));
			}
		}
	}
	// If there is no solution, no path
	else {
		pathLength = 0;
	}
}

void AStar::calculateDeltaElevation() {

	if (!finalSet.empty()) {
		for (int i = 1; i < finalSet.size(); i++) {
			deltaElevation += (finalSet.at(i - 1).getElevation() - finalSet.at(i).getElevation());
		}

		deltaElevation - finalSet.at(0).getElevation();
	}
	else {
		deltaElevation = 0;
	}

}

void AStar::calculateEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion) {

	for (int i = 1; i < finalSet.size(); i++) {

		double deltaDistance = 0;
		double alpha = 0;

		bool xAdjacent = (finalSet.at(i - 1).getNodeX() == finalSet.at(i).getNodeX());
		bool yAdjacent = (finalSet.at(i - 1).getNodeY() == finalSet.at(i).getNodeY());

		//double nodePathCost = nodeCurrent.getNodePathCost();
		int nodeElevation = finalSet.at(i - 1).getElevation();
		int nodeCurrentElevation = finalSet.at(i).getElevation();
		int deltaNodeElevation = abs(nodeElevation - nodeCurrentElevation);

		// If node is next to parent node (1) plus the delta elevation
		if (xAdjacent || yAdjacent) {
			// Where 1 is pow(1, 2)
			deltaDistance = sqrt(pow((1 * horizontalProportion), 2) + pow((deltaNodeElevation * verticalProportion), 2));
			alpha = atan(((nodeElevation - nodeCurrentElevation) * verticalProportion) / (1 * horizontalProportion));
		}
		// Else its diagonal (1.4) plus the delta elevation
		else {
			// Where 2 is pow(1.414, 2)
			deltaDistance = sqrt(pow((SQRTWO * horizontalProportion), 2) + pow((deltaNodeElevation * verticalProportion), 2));
			alpha = atan(((nodeElevation - nodeCurrentElevation) * verticalProportion) / (SQRTWO * horizontalProportion));
		}

		double gradeResistanceForce = gravity * mass * sin(alpha);
		double rollingResistanceForce = gravity * mass * rollingResistance;
		double netForce = gradeResistanceForce + rollingResistanceForce;

		double deltaEnergy = 0;
		deltaEnergy = netForce * deltaDistance;

		netEnergy += deltaEnergy;
	}
}

void AStar::calculateNeededEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion) {

	for (int i = 1; i < finalSet.size(); i++) {

		double deltaDistance = 0;
		double alpha = 0;

		bool xAdjacent = (finalSet.at(i - 1).getNodeX() == finalSet.at(i).getNodeX());
		bool yAdjacent = (finalSet.at(i - 1).getNodeY() == finalSet.at(i).getNodeY());

		//double nodePathCost = nodeCurrent.getNodePathCost();
		int nodeElevation = finalSet.at(i - 1).getElevation();
		int nodeCurrentElevation = finalSet.at(i).getElevation();
		int deltaNodeElevation = abs(nodeElevation - nodeCurrentElevation);

		// If node is next to parent node (1) plus the delta elevation
		if (xAdjacent || yAdjacent) {
			// Where 1 is pow(1, 2)
			deltaDistance = sqrt(pow((1 * horizontalProportion), 2) + pow((deltaNodeElevation * verticalProportion), 2));
			alpha = atan(((nodeElevation - nodeCurrentElevation) * verticalProportion) / (1 * horizontalProportion));
		}
		// Else its diagonal (1.4) plus the delta elevation
		else {
			// Where 2 is pow(1.414, 2)
			deltaDistance = sqrt(pow((SQRTWO * horizontalProportion), 2) + pow((deltaNodeElevation * verticalProportion), 2));
			alpha = atan(((nodeElevation - nodeCurrentElevation) * verticalProportion) / (SQRTWO * horizontalProportion));
		}

		double gradeResistanceForce = gravity * mass * sin(alpha);
		double rollingResistanceForce = gravity * mass * rollingResistance;
		double netForce;

		// Handle the case where rolling down hill is generating energy, but no regenerative breaking available.
		if ((gradeResistanceForce + rollingResistanceForce) >= 0) {
			netForce = gradeResistanceForce + rollingResistanceForce;
		}
		else {
			netForce = 0;
		}

		double deltaEnergy = 0;
		deltaEnergy = netForce * deltaDistance;

		netNeededEnergy += deltaEnergy;
	}
}

void AStar::drawBackPath(ImageGraph& imageParserArtist) {

	/*
	for (int i = 0; i < finalSet.size(); i++) {
		imageParserArtist.imageDrawLine(finalSet.at(i).getNodeX(), finalSet.at(i).getNodeY(), finalSet.at(i).getNodeX(), finalSet.at(i).getNodeY(), 0, 255, 0, 1);
	}
	*/

	//imageParserArtist.userResize(4);
	//imageParserArtist.imageShow("Lidar Based Topologial Terrain Map");
	//imageParserArtist.userWaitKey(60000, 'c');
	//imageParserArtist.userResize(1);

}

}