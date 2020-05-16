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

	std::string mapFile = "res/Mars_MGS_Final_Resized_by_6p.png";

	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser(mapFile);

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
	int nodeX = 122;
	int nodeY = 571;
	int goalX = 460;
	int goalY = 59;

	double gravConst = 3.711;
	double vehMass = 899;
	double dragCoeff = 0.01;
	double verProp = 114.95;
	double horProp = 2315;

	double energyVertical = vehMass * gravConst * verProp;
	double energyHorizontal = dragCoeff * vehMass * gravConst * horProp;

	double pathWeight = 1;
	double elevationWeight = energyVertical / energyHorizontal;// 2.0825;
	double euclidianWeight = 1;
	double maxGrade = 90;

	const int IMAGE_MAGNIFICATION = 1;
	const bool ANIMATION_ON = false;
	const bool DRAW_OPEN_SET = false;

	// AStar algorithm
	ALTAIR_WARN("Initialitzing Altair Class...");
	Altair::AStar astar;
	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

	astar.calculatePathLength(verProp, horProp);
	astar.calculateDeltaElevation();
	astar.calculateEnergy(gravConst, vehMass, dragCoeff, verProp, horProp);
	astar.calculateNeededEnergy(gravConst, vehMass, dragCoeff, verProp, horProp);

	ALTAIR_CORE_INFO("Total length of path [m]: {0}", astar.pathLength);
	ALTAIR_CORE_INFO("Delta elevation [Pixel Value]: {0}", astar.deltaElevation);
	ALTAIR_CORE_INFO("Total energy [J]: {0}", astar.netEnergy);
	ALTAIR_CORE_INFO("Total needed energy [J]: {0}", astar.netNeededEnergy);

	ALTAIR_WARN("Drawing Closed Set.");

	imageParser.imageDrawLine(nodeX, nodeY, nodeX, nodeY, 0, 255, 0, 1);
	imageParser.imageDrawLine(goalX, goalY, goalX, goalY, 0, 255, 0, 1);

	if (ANIMATION_ON && DRAW_OPEN_SET) {
		for (int i = 1; i < astar.closedSetClean.size(); i++) {

			int colorWeight = imageParser.getPixelValue(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord);

			imageParser.imageDrawLine(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, 0, 0, colorWeight, 1);
			imageParser.userResize(IMAGE_MAGNIFICATION);
			imageParser.imageShow("Map");
			cv::waitKey(1);
			imageParser.userResize(1);
		}
	}
	else if (DRAW_OPEN_SET){
		for (int i = 1; i < astar.closedSetClean.size(); i++) {

			int colorWeight = imageParser.getPixelValue(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord);
			imageParser.imageDrawLine(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, 0, 0, colorWeight, 1);

		}
		imageParser.userResize(IMAGE_MAGNIFICATION);
		imageParser.imageShow("Map");
		cv::waitKey(1);
		imageParser.userResize(1);
	}
	else {
		// Do Nothing
	}

	imageParser.imageDrawLine(nodeX, nodeY, nodeX, nodeY, 0, 255, 0, 1);
	imageParser.imageDrawLine(goalX, goalY, goalX, goalY, 0, 255, 0, 1);
	

	ALTAIR_WARN("Writing image...");
	imageParser.userResize(2);
	imageParser.imageWrite("res/N00E117_Closed.png");
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
	imageParser.userResize(2);
	imageParser.imageWrite("res/N00E117_Open.png");
	imageParser.userResize(1);

	/*
	// ***********************************************************************
	
	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser_hillshade("res/N00E117_Hillshade.png");

	ALTAIR_WARN("Drawing Open Set.");

	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		imageParser_hillshade.imageDrawLine(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, 0, 255, 0, 1);
	}

	imageParser_hillshade.userResize(IMAGE_MAGNIFICATION);
	imageParser_hillshade.imageShow("Map_Hillshade");

	ALTAIR_WARN("Writing image...");
	imageParser_hillshade.imageWrite("res/N00E117_Hillshade_Out.png");
	imageParser_hillshade.userResize(1);

	// ***********************************************************************

	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser_contures("res/N00E117_Contures.png");

	ALTAIR_WARN("Drawing Open Set.");

	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		imageParser_contures.imageDrawLine(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, 0, 255, 0, 1);
	}

	imageParser_contures.userResize(IMAGE_MAGNIFICATION);
	imageParser_contures.imageShow("Map_Contures");

	ALTAIR_WARN("Writing image...");
	imageParser_contures.imageWrite("res/N00E117_Contures_Out.png");
	imageParser_contures.userResize(1);

	// ***********************************************************************

	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser_tri("res/N00E117_TRI.png");

	ALTAIR_WARN("Drawing Open Set.");

	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		imageParser_tri.imageDrawLine(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, 0, 255, 0, 1);
	}

	imageParser_tri.userResize(IMAGE_MAGNIFICATION);
	imageParser_tri.imageShow("Map_TRI");

	// ***********************************************************************

	ALTAIR_WARN("Writing image...");
	imageParser_tri.imageWrite("res/N00E117_TRI_Out.png");
	imageParser_tri.userResize(1);

	*/
	

	//imageParser.userResize(IMAGE_MAGNIFICATION);
	//imageParser.imageShow("Map");
	ALTAIR_ERROR("Press Any Key to End System!");
	cv::waitKey(0);
	ALTAIR_ERROR("Ending System!");

	return 0;
}