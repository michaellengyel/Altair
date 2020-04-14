#include "ImageParser.h"

int ImageParser::getImageHeight() {
	return m_imageHeight;
}

int ImageParser::getImageWidth() {
	return m_imageWidth;
}

int ImageParser::getPixelValue(int xCoord, int yCoord) {
	return m_image.at<Vec3b>(yCoord, xCoord)[0];
}

int ImageParser::getPixelValue(int id) {
	return m_image.at<Vec3b>(id / m_image.cols, id % m_image.cols)[0];
}

void ImageParser::imageDrawLine(int startX, int startY, int endX, int endY, int blue, int green, int red, int width) {
	line(m_image, Point(startX, startY), Point(endX, endY), Scalar(blue, green, red), width);
}

void ImageParser::imageShow(string imageName) {
	imshow(imageName, m_image);
}

void ImageParser::imageWrite(string imageName) {
	imwrite(imageName, m_image);
}

void ImageParser::userWaitKey(int time, char exitKey) {
	if (waitKey(time) == exitKey) {
		//break;
	}	
}

void ImageParser::userResize(int resizeRate) {
	cv::Size targetSize = cv::Size(m_imageWidth*resizeRate, m_imageHeight*resizeRate);
	resize(m_image, m_image, targetSize, 0, 0, 0);
}