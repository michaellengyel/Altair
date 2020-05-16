#pragma once

#include "ImageParser.h"

class LinePath {
public:

	LinePath(ImageParser imageParser, int startX, int startY, int endX, int endY) : m_imageParser(imageParser), pathLength(0), deltaElevation(0), netEnergy(0), netNeededEnergy(0) {
		m_imageParser.calculateBresenham(startX, startY, endX, endY);
	}

	~LinePath() {

	}

	// Calculate the Path Length by summing all distances between the final path's nodes.
	void calculatePathLength(double verticalProportion, double horizontalProportion);

	// Calculate the Delta Elevation by summing all differenced between the final path's nodes.
	void calculateDeltaElevation();

	// Calculate the energy needed to traverse the final path using G, Mass, Rolling Resistance.
	void calculateEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion);

	// Calculate the energy needed to traverse the final path using G, Mass, Rolling Resistance without energy regeneration.
	void calculateNeededEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion);

	ImageParser m_imageParser;

private:

	const double SQRTWO = 1.414213562373095;
	const double PI = 3.141592653589793;

public:

	// Variable for holding the total length of the path
	double pathLength;

	// Variable for holding the delta elevation
	double deltaElevation;

	// Variable for holding the net energy
	double netEnergy;

	// Variable for holding the net needed energy
	double netNeededEnergy;

};
