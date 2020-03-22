#include "gtest/gtest.h"
#include <Altair.h>

namespace Altair {

ALTAIR_API AStar;

TEST(Astar_Tests, Top_U_Turn_Test_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = {{0, 0, 0},{0, 255, 0},{0, 255, 0}};

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 0;
	int nodeY = 2;
	int goalX = 2;
	int goalY = 2;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 2);
}

TEST(Astar_Tests, Top_U_Turn_Test_Counter_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 0, 0 },{ 0, 255, 0 },{ 0, 255, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 2;
	int nodeY = 2;
	int goalX = 0;
	int goalY = 2;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 2);
}

TEST(Astar_Tests, Left_U_Turn_Test_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 0, 0 },{ 0, 255, 255 },{ 0, 0, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 2;
	int nodeY = 2;
	int goalX = 2;
	int goalY = 0;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 2);
}

TEST(Astar_Tests, Left_U_Turn_Test_Counter_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 0, 0 },{ 0, 255, 255 },{ 0, 0, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 2;
	int nodeY = 0;
	int goalX = 2;
	int goalY = 2;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 0);
}

TEST(Astar_Tests, Bottom_U_Turn_Test_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 255, 0 },{ 0, 255, 0 },{ 0, 0, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 2;
	int nodeY = 0;
	int goalX = 0;
	int goalY = 0;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 0);
}

TEST(Astar_Tests, Bottom_U_Turn_Test_Counter_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 255, 0 },{ 0, 255, 0 },{ 0, 0, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 0;
	int nodeY = 0;
	int goalX = 2;
	int goalY = 0;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 0);
}

TEST(Astar_Tests, Right_U_Turn_Test_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 0, 0 },{ 255, 255, 0 },{ 0, 0, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 0;
	int nodeY = 0;
	int goalX = 0;
	int goalY = 2;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 0);
}

TEST(Astar_Tests, Right_U_Turn_Test_Counter_Clockwise)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 0, 0, 0 },{ 255, 255, 0 },{ 0, 0, 0 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 0;
	int nodeY = 2;
	int goalX = 0;
	int goalY = 0;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight);

	EXPECT_EQ(astar.finalSetClean.size(), 5);

	EXPECT_EQ(astar.finalSetClean.at(0).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(0).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(1).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(1).yCoord, 0);

	EXPECT_EQ(astar.finalSetClean.at(2).xCoord, 2);
	EXPECT_EQ(astar.finalSetClean.at(2).yCoord, 1);

	EXPECT_EQ(astar.finalSetClean.at(3).xCoord, 1);
	EXPECT_EQ(astar.finalSetClean.at(3).yCoord, 2);

	EXPECT_EQ(astar.finalSetClean.at(4).xCoord, 0);
	EXPECT_EQ(astar.finalSetClean.at(4).yCoord, 2);
}

}