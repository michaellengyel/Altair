#include <Altair.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

#include "ImageParser.h"
#include "LinePath.h"

namespace Altair {
	ALTAIR_API void Print();
	ALTAIR_API AStar;
	ALTAIR_API ImageGraph;
}

int main(int argc, char** argv) {

	// ********** SETUP **********

	ALTAIR_LOG_INIT;

	ImageGraph;

	std::string mapFile = "res/N00E117.png";

	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser(mapFile);

	// ImageGraph stores image in a 2D vector
	ImageGraph imageGraph(imageParser.getImageWidth(), imageParser.getImageHeight());

	// Copy the image from ImageParser format to ImageGraph format
	ALTAIR_VAL_ERROR("Generating ImageGraph Format...");
	for (int i = 0; i < imageParser.getImageWidth(); i++) {
		for (int j = 0; j < imageParser.getImageHeight(); j++) {
			int ie = imageParser.getPixelValue(j, i);
			imageGraph.setPixelValue(j, i, imageParser.getPixelValue(j, i));
		}
	}

	// ********** Random Parameters **********
	srand(time(NULL));

	// ********** AStar algorithm parameters **********
	ALTAIR_VAL_WARN("Initializing A-Star parameters...");
	//int nodeX = rand() % imageParser.getImageWidth();
	//int nodeY = rand() % imageParser.getImageHeight();
	//int goalX = rand() % imageParser.getImageWidth();
	//int goalY = rand() % imageParser.getImageHeight();

	int nodeX = 50;
	int nodeY = 50;
	int goalX = 350;
	int goalY = 350;

	// CHANGE ONLY THESE!!!
	double gravConst = 9.81;
	double vehMass = 1000;
	double dragCoeff = 0.01;
	double verProp = 2.1641;
	double horProp = 103.92;
	// END CHANGE ONLY THESE!!!

	double energyVertical = vehMass * gravConst * verProp;
	double energyHorizontal = dragCoeff * vehMass * gravConst * horProp;

	double pathWeight = energyHorizontal;
	double elevationWeight = energyVertical;// / energyHorizontal;// 2.0825;
	double euclidianWeight = 1;
	double maxGrade = 90;

	const int IMAGE_MAGNIFICATION = 1;

	// ********** AStar algorithm **********
	ALTAIR_VAL_WARN("Initialitzing Altair Class...");
	Altair::AStar astar;
	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

	astar.calculatePathLength(verProp, horProp);
	astar.calculateDeltaElevation();
	astar.calculateEnergy(gravConst, vehMass, dragCoeff, verProp, horProp);
	astar.calculateNeededEnergy(gravConst, vehMass, dragCoeff, verProp, horProp);

	ALTAIR_CORE_INFO("A* total length of path [m]: {0}", astar.pathLength);
	ALTAIR_CORE_INFO("A* delta elevation [Pixel Value]: {0}", astar.deltaElevation);
	ALTAIR_CORE_INFO("A* total energy [J]: {0}", astar.netEnergy);
	ALTAIR_CORE_INFO("A* total needed energy [J]: {0}", astar.netNeededEnergy);

	// ********** CREATING LINE DATA **********
	ALTAIR_VAL_WARN("Initialitzing LinePath Class...");
	ImageParser imageParserLinepath(mapFile);

	LinePath linepath(imageParserLinepath, nodeX, nodeY, goalX, goalY);

	linepath.calculatePathLength(verProp, horProp);
	linepath.calculateDeltaElevation();
	linepath.calculateEnergy(gravConst, vehMass, dragCoeff, verProp, horProp);
	linepath.calculateNeededEnergy(gravConst, vehMass, dragCoeff, verProp, horProp);

	ALTAIR_CORE_INFO("Line total length of path [m]: {0}", linepath.pathLength);
	ALTAIR_CORE_INFO("Line delta elevation [Pixel Value]: {0}", linepath.deltaElevation);
	ALTAIR_CORE_INFO("Line total energy [J]: {0}", linepath.netEnergy);
	ALTAIR_CORE_INFO("Line total needed energy [J]: {0}", linepath.netNeededEnergy);

	// ********** COMPAIRING LINE WITH A* **********

	if (astar.netNeededEnergy <= linepath.netNeededEnergy) {
		ALTAIR_CORE_ERROR("A* Energy Need Greater by {0}", astar.netNeededEnergy / linepath.netNeededEnergy);
	}
	else {
		ALTAIR_CORE_ERROR("There is an issue with the settings.");
	}

	ALTAIR_CORE_ERROR("A* Path Length Greater by {0}", astar.pathLength / linepath.pathLength);

	// ********** RENDERING **********

	ALTAIR_VAL_WARN("Drawing Closed Set.");

	imageParser.imageDrawLine(nodeX, nodeY, nodeX, nodeY, 0, 255, 0, 1);
	imageParser.imageDrawLine(goalX, goalY, goalX, goalY, 0, 255, 0, 1);

	// DELETE THIS
	/*
	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		std::cout << imageParser.getPixelValue(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord) << std::endl;
	}

	std::cout << "BREAK" << std::endl;

	for (int i = 0; i < linepath.m_imageParser.bresenhamPath.size(); i++) {
		std::cout << imageParser.getPixelValue(linepath.m_imageParser.bresenhamPath.at(i).xCoord, linepath.m_imageParser.bresenhamPath.at(i).yCoord) << std::endl;
	}
	*/

	// END DELETE

	
	ALTAIR_VAL_WARN("Drawing Open Set.");

	for (int i = 1; i < astar.closedSetClean.size(); i++) {
		int colorWeight = imageParser.getPixelValue(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord);
		imageParser.imageDrawLine(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, 0, 0, colorWeight, 1);
	}

	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		imageParser.imageDrawLine(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, 0, 255, 0, 1);
	}

	for (int i = 0; i < linepath.m_imageParser.bresenhamPath.size(); i++) {
		imageParser.imageDrawLine(linepath.m_imageParser.bresenhamPath.at(i).xCoord, linepath.m_imageParser.bresenhamPath.at(i).yCoord, linepath.m_imageParser.bresenhamPath.at(i).xCoord, linepath.m_imageParser.bresenhamPath.at(i).yCoord, 255, 255, 255, 1);
	}


	imageParser.userResize(IMAGE_MAGNIFICATION);
	imageParser.imageShow("Map");

	ALTAIR_VAL_WARN("Writing image...");
	imageParser.imageWrite("res/N00E117_Val.png");
	imageParser.userResize(1);

	/*
	ALTAIR_WARN("Writing image...");
	imageParser.imageWrite("res/N00E117_Open.png");
	imageParser.userResize(1);

	ALTAIR_WARN("Drawing LinePath Set.");

	for (int i = 0; i < imageParserLinepath.bresenhamPath.size(); i++) {
		imageParser.imageDrawLine(imageParserLinepath.bresenhamPath.at(i).xCoord, imageParserLinepath.bresenhamPath.at(i).yCoord, imageParserLinepath.bresenhamPath.at(i).xCoord, imageParserLinepath.bresenhamPath.at(i).yCoord, 0, 0, 255, 1);
	}

	imageParser.userResize(IMAGE_MAGNIFICATION);
	imageParser.imageShow("Map");

	ALTAIR_WARN("Writing image...");
	imageParser.imageWrite("res/N00E117_Open.png");
	imageParser.userResize(1);

	*/

	//imageParser.imageShow("Map");
	ALTAIR_VAL_ERROR("Press Any Key to End System!");
	cv::waitKey(0);
	ALTAIR_VAL_ERROR("Ending System!");

	return 0;
}