#include "AStar.h"

void AStar::astarAlgo(ImageGraph& imageGraph, int nodeX, int nodeY, int goalX, int goalY, int pathWeight, int elevationWeight, int euclidianWeight) {

	nodeStart = ANode(nodeX, nodeY, nodeX, nodeY);
	nodeEnd = ANode(goalX, goalY, 0, 0);

	openSet.push_back(nodeStart);

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
				//break;
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

int AStar::calculateNodePathCost(ANode& nodeCurrent, int pathWeight) {
	// Calculating the path cost:
	// If node is next to parent node (1) (And delta elevation)
	int nodePathCost = nodeCurrent.getNodePathCost();
	if ((nodeCurrent.getNodeX() == nodeCurrent.getParentX()) || (nodeCurrent.getNodeY() == nodeCurrent.getParentY())) {
		nodePathCost += 10;//sqrt(pow(1, 2) + pow((m_nodeElevation - m_parentElevation), 2));
	}
	// Else its diagonal (1.4) (And delta elevation)
	else {
		nodePathCost += 14;// sqrt(pow(1.414213f, 2) + pow((m_nodeElevation - m_parentElevation), 2));
	}

	return nodePathCost * pathWeight;
}

int AStar::calculateNodeCost(ImageGraph& imageGraph, ANode& nodeCurrent, ANode& node, int goalX, int goalY, int elevationWeight, int euclidianWeight) {
	// Calculating the path cost:
	// If node is next to parent node (1) (And delta elevation)
	float nodeCost = 0;

	nodeCost = nodeCurrent.getNodePathCost();

	// Calculating the height cost
	nodeCost += abs(imageGraph.getPixelValue(node.getNodeX(), node.getNodeY()) - imageGraph.getPixelValue(nodeCurrent.getNodeX(), nodeCurrent.getNodeY())) * elevationWeight;
	//nodeCost += imageParser.getPixelValue(node.getNodeX(), node.getNodeY()) * elevationWeight;
	//nodeCost += 255 - imageParser.getPixelValue(node.getNodeX(), node.getNodeY()) * elevationWeight;

	// Calculating the distance cost
	//nodeCost += sqrt(pow(nodeCurrent.getNodeX() - goalCoordinateX, 2) + pow(nodeCurrent.getNodeY() - goalCoordinateY, 2)) * 1.4;
	//nodeCost += pow(nodeCurrent.getNodeX() - goalCoordinateX, 2) + pow(nodeCurrent.getNodeY() - goalCoordinateY, 2);
	nodeCost += (abs(nodeCurrent.getNodeX() - goalX) + abs(nodeCurrent.getNodeY() - goalY)) * euclidianWeight;

	return nodeCost;
}

void AStar::expandNode(ImageGraph& imageParser, ANode& nodeCurrent, int x, int y, int goalX, int goalY, int pathWeight, int elevationWeight, int euclidianWeight) {
	// local variables:
	int nodeCurrentX = nodeCurrent.getNodeX();
	int nodeCurrentY = nodeCurrent.getNodeY();
	
	// Check if node to be created is not outside the boundary of the image
	bool rightFree = (nodeCurrentX + x < imageParser.getImageWidth() - 1);
	bool topFree = (nodeCurrentY + y > 0);
	bool leftFree = (nodeCurrentX + x > 0);
	bool bottomFree = (nodeCurrentY +   y < imageParser.getImageHeight() - 1);

	if (rightFree && topFree && leftFree && bottomFree) {
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
			ANode node = ANode(nodeCurrentX + x, nodeCurrentY + y, nodeCurrentX, nodeCurrentY);
			node.setNodePathCost(calculateNodePathCost(nodeCurrent, pathWeight));
			node.setNodeCost(calculateNodeCost(imageParser, nodeCurrent, node, goalX, goalY, elevationWeight, euclidianWeight));
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