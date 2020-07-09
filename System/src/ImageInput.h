// Class ImageInput reads an image file with the help of openCV.
// This a wrapper class for the image itself
// TODO: Add try-catch to reading of image
// TODO: Check if image is Black and White, if not, make it black and white

#pragma once

#ifndef ImageInput_h
#define ImageInput_h

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>

using namespace cv;
using namespace std;

class ImageInput {
public:

	// Default C'tor
	ImageInput::ImageInput() {

	}

	// C'tor
	ImageInput::ImageInput(string imagePath) : m_imagePath(imagePath) {
		ImageInput::m_image = imread(m_imagePath);
	}

	// Getter for image
	Mat& getImage();

private:
	string m_imagePath;
	Mat m_image;
};

#endif