#include <gtest/gtest.h>
#include "../include/lab1.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(eliminate_unset_bits("111") == 7);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(eliminate_unset_bits("1000000")==1);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(eliminate_unset_bits("000")==0);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(eliminate_unset_bits("101010101010101")==255);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(eliminate_unset_bits("1")==1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
