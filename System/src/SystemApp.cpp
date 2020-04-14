#include <Altair.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "ImageParser.h"

namespace Altair {
	ALTAIR_API void Print();
	ALTAIR_API AStar;
	ALTAIR_API ImageGraph;
}

int main(int argc, char** argv) {

	ALTAIR_LOG_INIT;

	ImageGraph;

	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser("res/map2.png");

	// ImageGraph stores image in a 2D vector
	ImageGraph imageGraph(imageParser.getImageWidth(), imageParser.getImageHeight());

	// Copy the image from ImageParser format to ImageGraph format
	ALTAIR_ERROR("Generating ImageGraph Format...");
	for (int i = 0; i < imageParser.getImageWidth(); i++) {
		for (int j = 0; j < imageParser.getImageHeight(); j++) {
			int ie = imageParser.getPixelValue(j, i);
			imageGraph.setPixelValue(j, i, imageParser.getPixelValue(j, i));
		}
	}

	// AStar algorithm parameters
	ALTAIR_WARN("Initializing A-Star parameters...");
	int nodeX = 0;
	int nodeY = 0;
	int goalX = 56;
	int goalY = 56;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;
	double maxGrade = 1;

	const int IMAGE_MAGNIFICATION = 9;

	// AStar algorithm
	ALTAIR_WARN("Initialitzing Altair Class...");
	Altair::AStar astar;
	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

	astar.calculatePathLength(1, 10);
	astar.calculateDeltaElevation();
	astar.calculateEnergy(9.81, 2000, 0.3, 1, 10);
	astar.calculateNeededEnergy(9.81, 2000, 0.3, 1, 10);

	ALTAIR_CORE_INFO("Total length of path [m]: {0}", astar.pathLength);
	ALTAIR_CORE_INFO("Delta elevation [m]: {0}", astar.deltaElevation);
	ALTAIR_CORE_INFO("Total energy [J]: {0}", astar.netEnergy);
	ALTAIR_CORE_INFO("Total needed energy [J]: {0}", astar.netNeededEnergy);

	
	
	ALTAIR_WARN("Drawing Closed Set.");
	for (int i = 0; i < astar.closedSetClean.size(); i++) {

		int colorWeight = imageParser.getPixelValue(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord);

		imageParser.imageDrawLine(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, 0, 0, colorWeight, 1);
		imageParser.userResize(IMAGE_MAGNIFICATION);
		imageParser.imageShow("Map");
		cv::waitKey(1);
		imageParser.userResize(1);
	}
	

	ALTAIR_WARN("Writing image...");
	imageParser.userResize(12);
	imageParser.imageWrite("res/map2_OUT_Simple.png");
	imageParser.userResize(1);
	
	ALTAIR_WARN("Drawing Open Set.");
	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		imageParser.imageDrawLine(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, 0, 255, 0, 1);
		imageParser.userResize(IMAGE_MAGNIFICATION);
		imageParser.imageShow("Map");
		cv::waitKey(1);
		imageParser.userResize(1);
	}

	ALTAIR_WARN("Writing image...");
	imageParser.userResize(12);
	imageParser.imageWrite("res/map2_OUT_Full.png");
	imageParser.userResize(1);

	//imageParser.userResize(IMAGE_MAGNIFICATION);
	//imageParser.imageShow("Map");
	ALTAIR_ERROR("Press Any Key to End System!");
	cv::waitKey(0);
	ALTAIR_ERROR("Ending System!");

	return 0;
}