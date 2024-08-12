#include <gtest/gtest.h>
#include "../include/vector.hpp"


namespace lin_op = linalgebra;
TEST(VectorTest, PrintVectorTest )
{
    EXPECT_TRUE(true);
}

TEST(VectorTest, DotProduct)
{
    lin_op::vecT<double> v1(10);
    lin_op::vecT<double> v2(10);
    ASSERT_EQ(0.0, lin_op::dotprod<double>(v1,v2));
    // lin_op::print_vec<double>(v1);
    EXPECT_TRUE(true);
}