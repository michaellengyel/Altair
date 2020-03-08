#include <Altair.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "ImageParser.h"
#include "ImageGraph.h"

namespace Altair {
	// TODO: Remove example code.
	ALTAIR_API void Print();
	ALTAIR_API Astar;
	// End example code
}

int main(int argc, char** argv) {

	// AStar START
	// ImageParser reads in, stores in Mat, provides access services
	ImageParser imageParser("res/map.png");
	// ImageGraph stores image in a 2D vector
	ImageGraph imageGraph(imageParser.getImageWidth(), imageParser.getImageHeight());


	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < imageParser.getImageHeight(); i++) {
		for (int j = 0; j < imageParser.getImageWidth(); j++) {
			int ie = imageParser.getPixelValue(i, j);
			imageGraph.setPixelValue(i, j, imageParser.getPixelValue(i, j));
		}
	}


	// AStar END

	// TODO: Remove example code.
	Altair::Log::Init();
	ALTAIR_CORE_WARN("Initializind log!");
	ALTAIR_CORE_ERROR("Initializind log!");

	Altair::Print();
	Altair::Astar a;
	int values[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	double result = a.Run(values, 11);
	std::cout << result << std::endl;

	Altair::Node node(1, 1, 1);
	std::cout << node.absoluteLength() << std::endl;
	// End example code

	/*
	cv::Mat map = cv::imread("res/map.png");
	cv::namedWindow("Map", cv::WINDOW_NORMAL);
	cv::imshow("Map", map);
	cv::waitKey(0);
	*/

	return 0;
}