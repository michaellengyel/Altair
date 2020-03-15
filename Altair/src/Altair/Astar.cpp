#include "AStar.h"

void AStar::astarAlgo(ImageGraph& imageGraph, int nodeX, int nodeY, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight) {

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
		expandNode(imageGraph, nodeCurrent, 1, 0, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// TOP RIGHT
		expandNode(imageGraph, nodeCurrent, 1, -1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// TOP
		expandNode(imageGraph, nodeCurrent, 0, -1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// TOP LEFT
		expandNode(imageGraph, nodeCurrent, -1, -1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// LEFT
		expandNode(imageGraph, nodeCurrent, -1, 0, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// BOTTOM LEFT
		expandNode(imageGraph, nodeCurrent, -1, 1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// BOTTOM
		expandNode(imageGraph, nodeCurrent, 0, 1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);
		// BOTTOM RIGHT
		expandNode(imageGraph, nodeCurrent, 1, 1, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);


		// If a node has been expanded, erase from open set
		for (int i = 0; i < openSet.size(); i++) {
			if (nodeCurrent.getNodeX() == openSet.at(i).getNodeX() && nodeCurrent.getNodeY() == openSet.at(i).getNodeY()) {
				openSet.erase(openSet.begin() + i);
				// break;
			}
		}

		// Keeping track of open and closed setSize
		cout << openSet.size() << ", " << closedSet.size() << endl;
		
	}

	traceBackPath(nodeStart, nodeCurrent);
	convertfinalSetToCleaned();
	convertClosedSetToCleaned();
	drawBackPath(imageGraph);

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

void AStar::expandNode(ImageGraph& imageGraph, ANode& nodeCurrent, int x, int y, int goalX, int goalY, double pathWeight, double elevationWeight, double euclidianWeight) {
	// local variables:
	int nodeCurrentX = nodeCurrent.getNodeX();
	int nodeCurrentY = nodeCurrent.getNodeY();
	
	// Check if node to be created is not outside the boundary of the image
	bool rightFree = (nodeCurrentX + x < imageGraph.getImageWidth());
	bool topFree = (nodeCurrentY + y >= 0);
	bool leftFree = (nodeCurrentX + x >= 0);
	bool bottomFree = (nodeCurrentY +   y < imageGraph.getImageHeight());

	if ((rightFree && topFree) && (leftFree && bottomFree)) {
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
			if (xCoordsMatch && yCoordsMatch && newNodeGreater) {
				openSet.at(openedNodeID) = node;
			}
			// If node already exists, and is more efficient, do nothing
			else if (xCoordsMatch && yCoordsMatch && newNodeLesser) {
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

void AStar::drawBackPath(ImageGraph& imageParserArtist) {

	for (int i = 0; i < finalSet.size(); i++) {
		//imageParserArtist.imageDrawLine(finalSet.at(i).getNodeX(), finalSet.at(i).getNodeY(), finalSet.at(i).getNodeX(), finalSet.at(i).getNodeY(), 0, 255, 0, 1);
	}

	//imageParserArtist.userResize(4);
	//imageParserArtist.imageShow("Lidar Based Topologial Terrain Map");
	//imageParserArtist.userWaitKey(60000, 'c');
	//imageParserArtist.userResize(1);
	
}