#include <gtest/gtest.h>

#include "aiacpch.h"
#include "AIAC.h"

// create a simple test
TEST(SmokeTests, DryRun) {
    // run the build/bin/AC executable with the config.ini file and run it from root of the repo
    // the executable should run without any errors
    bool success = system("build/bin/AC tests/assets/config_smoke_test.ini") == 0;
    EXPECT_TRUE(success);
}