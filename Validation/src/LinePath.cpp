#include "LinePath.h"

void LinePath::calculatePathLength(double verticalProportion, double horizontalProportion) {

	// Check if final set is empty or not
	if (!m_imageParser.bresenhamPath.empty()) {

		for (int i = 1; i < m_imageParser.bresenhamPath.size(); i++) {

			bool xAdjacent = (m_imageParser.bresenhamPath.at(i - 1).xCoord == m_imageParser.bresenhamPath.at(i).xCoord);
			bool yAdjacent = (m_imageParser.bresenhamPath.at(i - 1).yCoord == m_imageParser.bresenhamPath.at(i).yCoord);

			//double nodePathCost = nodeCurrent.getNodePathCost();
			int nodeElevation = m_imageParser.bresenhamPath.at(i - 1).value;
			int nodeCurrentElevation = m_imageParser.bresenhamPath.at(i).value;
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

void LinePath::calculateDeltaElevation() {

	if (!m_imageParser.bresenhamPath.empty()) {
		for (int i = 1; i < m_imageParser.bresenhamPath.size(); i++) {
			deltaElevation += (m_imageParser.bresenhamPath.at(i - 1).value - m_imageParser.bresenhamPath.at(i).value);
		}

		deltaElevation - m_imageParser.bresenhamPath.at(0).value;
	}
	else {
		deltaElevation = 0;
	}

}

void LinePath::calculateEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion) {

	for (int i = 1; i < m_imageParser.bresenhamPath.size(); i++) {

		double deltaDistance = 0;
		double alpha = 0;

		bool xAdjacent = (m_imageParser.bresenhamPath.at(i - 1).xCoord == m_imageParser.bresenhamPath.at(i).xCoord);
		bool yAdjacent = (m_imageParser.bresenhamPath.at(i - 1).yCoord == m_imageParser.bresenhamPath.at(i).yCoord);

		//double nodePathCost = nodeCurrent.getNodePathCost();
		int nodeElevation = m_imageParser.bresenhamPath.at(i - 1).value;
		int nodeCurrentElevation = m_imageParser.bresenhamPath.at(i).value;
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

void LinePath::calculateNeededEnergy(double gravity, double mass, double rollingResistance, double verticalProportion, double horizontalProportion) {

	for (int i = 1; i < m_imageParser.bresenhamPath.size(); i++) {

		double deltaDistance = 0;
		double alpha = 0;

		bool xAdjacent = (m_imageParser.bresenhamPath.at(i - 1).xCoord == m_imageParser.bresenhamPath.at(i).xCoord);
		bool yAdjacent = (m_imageParser.bresenhamPath.at(i - 1).yCoord == m_imageParser.bresenhamPath.at(i).yCoord);

		//double nodePathCost = nodeCurrent.getNodePathCost();
		int nodeElevation = m_imageParser.bresenhamPath.at(i - 1).value;
		int nodeCurrentElevation = m_imageParser.bresenhamPath.at(i).value;
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