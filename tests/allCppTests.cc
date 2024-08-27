#include <gtest/gtest.h>

// create a simple test
TEST(SimpleTest, Test1) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}