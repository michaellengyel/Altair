// Class Node
// TODO: Create a namespace for the whole software because "Node" is used in the std namespace 

#pragma once

#ifndef ANode_h
#define ANode_h

#include <iostream>
#include <math.h>
#include <stdint.h>
#include <limits.h>

using namespace std;

class ANode {
public:

	// Default C'tor
	ANode() {

	}

	// C'tor

	ANode(int nodeX, int nodeY, int parentX, int parentY, int elevation) :
		m_nodeX(nodeX),
		m_nodeY(nodeY),
		m_parentX(parentX),
		m_parentY(parentY),
		m_elevation(elevation),
		m_nodeCost(0.0f),
		m_nodePathCost(0.0f)
	{

	}

	// Cost
	double getNodeCost() {
		return m_nodeCost;
	}

	void setNodeCost(double nodeCost) {
		m_nodeCost = nodeCost;
	}

	// Path Cost
	double getNodePathCost() {
		return m_nodePathCost;
	}

	void setNodePathCost(double nodePathCost) {
		m_nodePathCost = nodePathCost;
	}

	// Elevaton
	int getElevation() {
		return m_elevation;
	}

	void setElevation(int elevation) {
		m_elevation = elevation;
	}

	// Node
	int getNodeX() {
		return m_nodeX;
	}

	void setNodeX(int nodeX) {
		m_nodeX = nodeX;
	}

	int getNodeY() {
		return m_nodeY;
	}

	void setNodeY(int nodeY) {
		m_nodeY = nodeY;
	}

	// Parent
	int getParentX() {
		return m_parentX;
	}

	void setParentX(int parentX) {
		m_parentX = parentX;
	}

	int getParentY() {
		return m_parentY;
	}

	void setParentY(int parentY) {
		m_parentY = parentY;
	}

private:

	int m_nodeX;
	int m_nodeY;
	int m_parentX;
	int m_parentY;
	int m_elevation;
	double m_nodePathCost;
	double m_nodeCost;

};

#endif