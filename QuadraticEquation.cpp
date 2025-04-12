#include <gtest/gtest.h>

class QuadraticEquation
{
};

// gTest grouping class
class test_QuadraticEquation : public ::testing::Test
{
public:
    // additional class to access to member of tested class
    class Test_QuadraticEquation : public QuadraticEquation
    {
    public:
        // add here members for free access.
        using QuadraticEquation::QuadraticEquation; // delegate constructors
    };

};

TEST_F(test_QuadraticEquation, test_ctor)
{
    Test_QuadraticEquation t;
    FAIL() << "Just testing";
}


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}