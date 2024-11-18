#include <gtest/gtest.h>

#define HEADLESS_TEST

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}