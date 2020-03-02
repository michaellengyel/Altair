#include "gtest/gtest.h"
#include <Altair.h>

namespace Altair {

ALTAIR_API Astar;

TEST(Node_Tests, absoluteLength_test)
{
	Altair::Node node(1, 1, 1);
	EXPECT_DOUBLE_EQ(1.732050807568877, node.absoluteLength());
}

TEST(Astar_Tests, Run_test)
{
	int data[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int size = 9;

	ALTAIR_API Astar;
	Altair::Astar astar;
	EXPECT_DOUBLE_EQ(5.196152422706631880582339, astar.Run(data, size));
}


TEST(Visuals_Tests, visualsTestFunction_test)
{
	Altair::Visuals visuals;
	EXPECT_DOUBLE_EQ(2, visuals.visualsTestFunction(1, 1));
}

}