// This Class is used to hold the image in the form of a
// 2D Vector, to be passed to the AStar algorithm.

#pragma once

#include <vector>
#include "Core.h"

class ALTAIR_API ImageGraph {
public:
	ImageGraph(int xSize, int ySize);

	~ImageGraph();

	// Returns the image width
	int getImageWidth();

	// Return the image height
	int getImageHeight();

	void setPixelValue(int xCoord, int yCoord, int pixel);

	int getPixelValue(int xCoord, int yCoord);

private:
	int m_xSize;
	int m_ySize;
	std::vector<int> vectorImage;
};
