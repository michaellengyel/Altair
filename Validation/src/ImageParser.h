// Class ImageInput reads an image file with the help of openCV.
// This an interface class
// TODO: Add try-catch to reading of image
// TODO: Check if image is Black and White, if not, make it black and white

#pragma once

#ifndef ImageParser_h
#define ImageParser_h

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "ImageInput.h"

#include <string>

using namespace cv;
using namespace std;

class ImageParser {
public:

	// Default C'tor
	ImageParser() {

	}

	// C'tor
	ImageParser(string imagePath) : m_imagePath(imagePath) {
		m_imageInput = ImageInput(m_imagePath);
		m_image = m_imageInput.getImage();
		m_imageWidth = m_image.cols;
		m_imageHeight = m_image.rows;
	}

	// Returns the image width
	int getImageWidth();

	// Return the image height
	int getImageHeight();

	// Returns the grayscale pixel value at xCoord and yCoord
	int getPixelValue(int xCoord, int yCoord);

	// Returns the grayscale pixel value at pixel ID
	int getPixelValue(int id);

	// Draw to the image of the ImageParser object.
	void imageDrawLine(int startX, int startY, int endX, int endY, int red, int green, int blue, int width);

	// Show the image
	void imageShow(string imageName);

	// Write the image to disk
	void imageWrite(string imageName);

	// waitKey function. Must be called for animation to work
	// TODO: Uncomment the "break"
	void userWaitKey(int time, char exitKey);

	void userResize(int resizeRate);

	void calculateBresenham(int startX, int startY, int endX, int endY);

private:

	string m_imagePath;
	ImageInput m_imageInput;
	Mat m_image;

	int m_imageWidth;
	int m_imageHeight;

public:

	// A struct used to represent the node as a x and y coordinate when passing the path back to the user (system)
	struct UserPoint {
		int xCoord;
		int yCoord;
		int value;
	};

	std::vector<UserPoint> bresenhamPath;
};

#endif