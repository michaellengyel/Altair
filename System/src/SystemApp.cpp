#include <Altair.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "ImageParser.h"

namespace Altair {
	// TODO: Remove example code.
	ALTAIR_API void Print();
	ALTAIR_API AStar;
	ALTAIR_API ImageGraph;
	// End example code
}

int main(int argc, char** argv) {

	ImageGraph;

	// AStar START
	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser("res/map2.png");

	// ImageGraph stores image in a 2D vector
	ImageGraph imageGraph(imageParser.getImageWidth(), imageParser.getImageHeight());

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < imageParser.getImageWidth(); i++) {
		for (int j = 0; j < imageParser.getImageHeight(); j++) {
			int ie = imageParser.getPixelValue(j, i);
			imageGraph.setPixelValue(j, i, imageParser.getPixelValue(j, i));
		}
	}

	// AStar algorithm
	int nodeX = 0;
	int nodeY = 0;
	int goalX = 56;
	int goalY = 56;
	double pathWeight = 1;
	double elevationWeight = 0.1;
	double euclidianWeight = 1;

	const int IMAGE_MAGNIFICATION = 8;

	AStar astar;
	astar.astarAlgo(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	
	for (int i = 0; i < astar.closedSetClean.size(); i++) {
		imageParser.imageDrawLine(astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, astar.closedSetClean.at(i).xCoord, astar.closedSetClean.at(i).yCoord, 0, 0, 255, 1);
		imageParser.userResize(IMAGE_MAGNIFICATION);
		imageParser.imageShow("Map");
		cv::waitKey(1);
		imageParser.userResize(1);
	}
	

	// Drawing of the path moved from Altair dll to the System
	for (int i = 0; i < astar.finalSetClean.size(); i++) {
		imageParser.imageDrawLine(astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, astar.finalSetClean.at(i).xCoord, astar.finalSetClean.at(i).yCoord, 0, 255, 0, 1);
		imageParser.userResize(IMAGE_MAGNIFICATION); // Resize
		imageParser.imageShow("Map");
		cv::waitKey(1);
		imageParser.userResize(1);
	}

	imageParser.userResize(IMAGE_MAGNIFICATION); // Resize
	imageParser.imageShow("Map");
	cv::waitKey(0);


	// AStar END

	// TODO: Remove example code.
	Altair::Log::Init();
	ALTAIR_CORE_WARN("Initializind log!");
	ALTAIR_CORE_ERROR("Initializind log!");

	/*
	Altair::Print();
	Altair::Astar a;
	int values[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	double result = a.Run(values, 11);
	std::cout << result << std::endl;

	Altair::Node node(1, 1, 1);
	std::cout << node.absoluteLength() << std::endl;
	// End example code
	*/

	/*
	cv::Mat map = cv::imread("res/map.png");
	cv::namedWindow("Map", cv::WINDOW_NORMAL);
	cv::imshow("Map", map);
	cv::waitKey(0);
	*/

	return 0;
}