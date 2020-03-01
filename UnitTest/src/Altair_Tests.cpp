#include "gtest/gtest.h"
#include "Node.cpp"

TEST(Altair_Tests, NodeTest)
{
	Altair::Node node(1, 1, 1);
	EXPECT_DOUBLE_EQ(1.732050807568877, node.absoluteLength());
}
