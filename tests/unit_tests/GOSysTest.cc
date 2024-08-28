#include <gtest/gtest.h>

#include <utility>
#include <iostream>

#include "aiacpch.h"
#include "AIAC.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Render/GLObject.h"
#include "AIAC/Base.h"
#include "glm/glm.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp> // For glm::length2
#include <glm/gtc/constants.hpp> // For glm::pi


class GOPointTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code for setting up initial conditions for tests
    }

    void TearDown() override {
        // Code for cleaning up after tests
    }
};

TEST_F(GOPointTest, ConstructorTest) {
    AIAC::GOPoint point(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(point.X(), 1.0f);
    EXPECT_EQ(point.Y(), 2.0f);
    EXPECT_EQ(point.Z(), 3.0f);
}

TEST_F(GOPointTest, AddMethodTest) {
    auto point = AIAC::GOPoint::Add(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(point->X(), 1.0f);
    EXPECT_EQ(point->Y(), 2.0f);
    EXPECT_EQ(point->Z(), 3.0f);
}

TEST_F(GOPointTest, GetSetPositionTest) {
    AIAC::GOPoint point(1.0f, 2.0f, 3.0f);
    point.SetPosition(glm::vec3(4.0f, 5.0f, 6.0f));
    EXPECT_EQ(point.GetPosition().x, 4.0f);
    EXPECT_EQ(point.GetPosition().y, 5.0f);
    EXPECT_EQ(point.GetPosition().z, 6.0f);
}

TEST_F(GOPointTest, DistanceToTest) {
    AIAC::GOPoint point1(1.0f, 2.0f, 3.0f);
    AIAC::GOPoint point2(4.0f, 6.0f, 8.0f);
    float distance = point1.DistanceTo(point2);
    EXPECT_NEAR(distance, 7.071f, 0.001f);
}

TEST_F(GOPointTest, TransformTest) {
    AIAC::GOPoint point(1.0f, 2.0f, 3.0f);
    glm::mat4x4 transformMat = glm::mat4x4(1.0f);
    transformMat[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Translation matrix
    point.Transform(transformMat);
    EXPECT_EQ(point.X(), 2.0f);
    EXPECT_EQ(point.Y(), 3.0f);
    EXPECT_EQ(point.Z(), 4.0f);
}
