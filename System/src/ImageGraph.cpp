#include "ImageGraph.h"

ImageGraph::ImageGraph(int xSize, int ySize) : m_xSize(xSize), m_ySize(ySize) {
	vectorImage.resize(xSize * ySize);
}

ImageGraph::~ImageGraph() {}


int ImageGraph::getImageWidth() {
	return m_xSize;
}

int ImageGraph::getImageHeight() {
	return m_ySize;
}

void ImageGraph::setPixelValue(int xCoord, int yCoord, int pixel) {
	vectorImage[xCoord * yCoord + xCoord] = pixel;
}

uint8_t ImageGraph::getPixelValue(int xCoord, int yCoord) {
	return vectorImage[xCoord * yCoord + xCoord];
}