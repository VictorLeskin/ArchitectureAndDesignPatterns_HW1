#include <gtest/gtest.h>

#include <math.h>
#include <tuple>

class QuadraticEquation
{

    public:
    inline static const double eps = 1.0e-15;

    static std::tuple<int, double, double> solve(double a, double b, double c)
    {
        if (fabs(a) < eps)
            throw(std::domain_error("Leading coeff should not be 0"));

        double D = b * b - 4 * a * c;
        if (D < -eps)
            return std::tuple(0,0,0);

        a *= 2;
        if( D > eps )
        {
            D = sqrt(D);
            return std::tuple(2, (-b - D)/a, (-b + D)/a);
        }
        else
            return std::tuple(1, -b/a, -b/a);
    }
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

TEST_F(test_QuadraticEquation, test_solve_no_roots)
{
    auto res = Test_QuadraticEquation::solve(1, 0, 1);

    EXPECT_EQ(0, std::get<0>(res));
}

TEST_F(test_QuadraticEquation, test_solve_2_roots)
{
    auto res = Test_QuadraticEquation::solve(1, 0, -1);

    EXPECT_EQ(2, std::get<0>(res));
    EXPECT_NEAR(-1, std::get<1>(res), 1.0e-15);
    EXPECT_NEAR( 1, std::get<2>(res), 1.0e-15);
}

TEST_F(test_QuadraticEquation, test_solve_1_roots)
{
    auto res = Test_QuadraticEquation::solve(1, 2, 1);

    EXPECT_EQ(1, std::get<0>(res));
    EXPECT_NEAR(-1, std::get<1>(res), 1.0e-15);
    EXPECT_EQ(std::get<1>(res), std::get<2>(res));
}


TEST_F(test_QuadraticEquation, test_solve_leading_coefficient_is_0 )
{
    // -eps < a = 0.9999*eps < eps
    EXPECT_THROW({
            try
            {
                auto res = Test_QuadraticEquation::solve(0.9999 * 1.0e-15, 2, 1);
            }
            catch (const std::domain_error& e)
            {
                // and this tests that it has the correct message
                EXPECT_STREQ("Leading coeff should not be 0", e.what());
                throw;
            }
        }, std::domain_error);

    // -eps < a = -0.9999*eps < eps
    EXPECT_THROW({
            try
            {
                auto res = Test_QuadraticEquation::solve(-0.9999 * 1.0e-15, 2, 1);
            }
            catch (const std::domain_error& e)
            {
                // and this tests that it has the correct message
                EXPECT_STREQ("Leading coeff should not be 0", e.what());
                throw;
            }
        }, std::domain_error);

}
