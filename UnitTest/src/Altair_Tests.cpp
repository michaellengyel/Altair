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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);

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

// Test for calculatePathLength() 2D
TEST(Astar_Tests, Calculate_Path_Length_2D)
{
	const int width = 5;
	const int height = 5;
	int data[width][height] = { { 0, 255, 0, 0, 0 },{ 0, 255, 0, 255, 0 },{ 0, 0, 0, 255, 0 },{ 255, 255, 255, 255, 0 },{ 0, 0, 0, 0, 0 } };

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
	int goalY = 4;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculatePathLength(1, 1);

	EXPECT_EQ(astar.finalSetClean.size(), 12);
	EXPECT_DOUBLE_EQ(astar.pathLength, 13.071067811865475);
}

// Test for calculatePathLength() 3D
TEST(Astar_Tests, Calculate_Path_Length_3D)
{
	const int width = 5;
	const int height = 5;
	int data[width][height] = { { 0, 255, 0, 0, 0 },{ 1, 255, 0, 255, 1 },{ 0, 1, 0, 255, 1 },{ 255, 255, 255, 255, 1 },{ 1, 1, 0, 0, 0 } };

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
	int goalY = 4;
	double pathWeight = 1;
	double elevationWeight = 1;
	double euclidianWeight = 1;
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculatePathLength(1, 1);

	EXPECT_EQ(astar.finalSetClean.size(), 12);
	EXPECT_DOUBLE_EQ(astar.pathLength, 14.85300667219901);
}

// Testing Energy Calculaton functions
TEST(Astar_Tests, Energy_Calculation_1_3D)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 255, 5, 0 },{ 10, 255, 255 },{ 255, 3, 3 } };

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculatePathLength(1, 10);
	astar.calculateEnergy(10, 10, 0.5, 1, 10);

	EXPECT_EQ(astar.finalSetClean.size(), 5);
	EXPECT_DOUBLE_EQ(astar.pathLength, 51.960073725558445);
	EXPECT_DOUBLE_EQ(astar.netEnergy, 2898.0036862779225);

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

// Testing Energy Calculaton functions
TEST(Astar_Tests, Energy_Calculation_2_3D)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 8, 255, 10 },{ 4, 255, 10 },{ 255, 2, 255 } };

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculatePathLength(1, 10);
	astar.calculateEnergy(9.81, 100, 0.2, 1, 10);

	EXPECT_EQ(astar.finalSetClean.size(), 5);
	EXPECT_DOUBLE_EQ(astar.pathLength, 51.301263280626628);
	EXPECT_DOUBLE_EQ(astar.netEnergy, 8103.3078556589453);

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

// Testing Energy Calculaton functions
TEST(Astar_Tests, Energy_Calculation_2_3D_Example)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 8, 255, 10 },{ 4, 255, 10 },{ 255, 2, 255 } };

	ImageGraph imageGraph(width, height);

	// Copy the image from ImageParser format to ImageGraph format
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			imageGraph.setPixelValue(i, j, data[j][i]);
		}
	}

	// AStar algorithm parameters
	int nodeX = 2, nodeY = 0, goalX = 0, goalY = 0;
	double pathWeight = 1, elevationWeight = 1, euclidianWeight = 1;
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculateEnergy(9.81, 100, 0.2, 1, 10);

	EXPECT_NEAR(astar.netEnergy, 8103.3021, 0.01);
}

// Testing Needed Energy Calculaton functions
TEST(Astar_Tests, Energy_Needed_Calculation_1_3D)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 255, 5, 0 },{ 10, 255, 255 },{ 255, 3, 3 } };

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculatePathLength(1, 10);
	astar.calculateNeededEnergy(10, 10, 0.5, 1, 10);

	EXPECT_EQ(astar.finalSetClean.size(), 5);
	EXPECT_DOUBLE_EQ(astar.pathLength, 51.960073725558445);
	EXPECT_DOUBLE_EQ(astar.netNeededEnergy, 2898.0036862779225);

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

// Testing Needed Energy Calculaton functions
TEST(Astar_Tests, Energy_Needed_Calculation_2_3D)
{
	const int width = 3;
	const int height = 3;
	int data[width][height] = { { 8, 255, 10 },{ 4, 255, 10 },{ 255, 2, 255 } };

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
	double maxGrade = 90;

	AStar astar;

	astar.run(imageGraph, nodeX, nodeY, goalX, goalY, pathWeight, elevationWeight, euclidianWeight, maxGrade);
	astar.calculatePathLength(1, 10);
	astar.calculateNeededEnergy(9.81, 100, 0.2, 1, 10);

	EXPECT_EQ(astar.finalSetClean.size(), 5);
	EXPECT_DOUBLE_EQ(astar.pathLength, 51.301263280626628);
	EXPECT_DOUBLE_EQ(astar.netNeededEnergy, 12763.435185679795);

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

}