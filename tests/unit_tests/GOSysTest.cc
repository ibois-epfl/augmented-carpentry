#include <gtest/gtest.h>

#include <utility>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp> // For glm::length2
#include <glm/gtc/constants.hpp> // For glm::pi
#include <memory>

#include "aiacpch.h"
#include "AIAC.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Render/GLObject.h"
#include "AIAC/Base.h"


class GOPrimitiveTest : public ::testing::Test {
protected:
    void SetUp() override {
        primitive = std::make_shared<AIAC::GOPrimitive>();
    }

    std::shared_ptr<AIAC::GOPrimitive> primitive;
};

TEST_F(GOPrimitiveTest, Constructor_DefaultValues) {
    EXPECT_TRUE(primitive->IsVisible());
    EXPECT_EQ(primitive->GetColor(), glm::vec4(0, 0, 0, 1.0));
    EXPECT_EQ(primitive->GetWeight(), AIAC::GOWeight::Default);
}

TEST_F(GOPrimitiveTest, SetName_GetName) {
    std::string name = "TestPrimitive";
    primitive->SetName(name);
    EXPECT_EQ(primitive->GetName(), name);
}

TEST_F(GOPrimitiveTest, SetVisibility_GetVisibility) {
    primitive->SetVisibility(false);
    EXPECT_FALSE(primitive->GetVisibility());
    primitive->SetVisibility(true);
    EXPECT_TRUE(primitive->GetVisibility());
}

TEST_F(GOPrimitiveTest, SetColor_GetColor) {
    glm::vec4 color(1.0, 0.0, 0.0, 1.0);
    primitive->SetColor(color);
    EXPECT_EQ(primitive->GetColor(), color);
}

TEST_F(GOPrimitiveTest, SetWeight_GetWeight) {
    float weight = AIAC::GOWeight::Bold;
    primitive->SetWeight(weight);
    EXPECT_EQ(primitive->GetWeight(), weight);
}

TEST_F(GOPrimitiveTest, GenerateId) {
    uint32_t id = primitive->GenerateId();
    if (AIAC_GOREG->CheckIfKeyExists(id))
        FAIL() << "Id already exists in the registry";
}


class GOPointTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(GOPointTest, ConstructorTest) {
    AIAC::GOPoint point(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(point.X(), 1.0f);
    EXPECT_EQ(point.Y(), 2.0f);
    EXPECT_EQ(point.Z(), 3.0f);
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


class GOLineTest : public ::testing::Test {
protected:
    void SetUp() override {
        p1 = std::make_shared<AIAC::GOPoint>(0.0f, 0.0f, 0.0f);
        p2 = std::make_shared<AIAC::GOPoint>(1.0f, 1.0f, 1.0f);
        line = AIAC::GOLine::Add(*p1, *p2);
    }

    std::shared_ptr<AIAC::GOPoint> p1;
    std::shared_ptr<AIAC::GOPoint> p2;
    std::shared_ptr<AIAC::GOLine> line;
};

TEST_F(GOLineTest, ExtendFromEnd) {
    float length = 1.0f;
    line->ExtendFromEnd(length);
    ASSERT_FLOAT_EQ(line->GetLength(), glm::distance(p1->GetPosition(), p2->GetPosition() + glm::normalize(p2->GetPosition() - p1->GetPosition()) * length));
}

TEST_F(GOLineTest, ExtendBothEnds) {
    float length = 1.0f;
    line->ExtendBothEnds(length);
    ASSERT_FLOAT_EQ(line->GetLength(), glm::distance(p1->GetPosition() - glm::normalize(p2->GetPosition() - p1->GetPosition()) * (length / 2), p2->GetPosition() + glm::normalize(p2->GetPosition() - p1->GetPosition()) * (length / 2)));
}

TEST_F(GOLineTest, GetMidPointValues) {
    glm::vec3 expectedMidPoint = (p1->GetPosition() + p2->GetPosition()) / 2.0f;
    ASSERT_EQ(line->GetMidPointValues(), expectedMidPoint);
}

TEST_F(GOLineTest, GetMidPoint) {
    AIAC::GOPoint expectedMidPoint((p1->GetPosition() + p2->GetPosition()) / 2.0f);
    ASSERT_EQ(line->GetMidPoint().GetPosition(), expectedMidPoint.GetPosition());
}

TEST_F(GOLineTest, GetNormalValues) {
    glm::vec3 expectedNormal = glm::normalize(glm::cross(p2->GetPosition() - p1->GetPosition(), glm::vec3(0, 0, 1)));
    ASSERT_EQ(line->GetNormalValues(), expectedNormal);
}

TEST_F(GOLineTest, Transform) {
    glm::mat4x4 transformMat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    line->Transform(transformMat);
    ASSERT_EQ(line->GetPStart().GetPosition(), glm::vec3(transformMat * glm::vec4(p1->GetPosition(), 1.0f)));
    ASSERT_EQ(line->GetPEnd().GetPosition(), glm::vec3(transformMat * glm::vec4(p2->GetPosition(), 1.0f)));
}

TEST_F(GOLineTest, Translate) {
    glm::vec3 translation(1.0f, 1.0f, 1.0f);
    line->Translate(translation);
    ASSERT_EQ(line->GetPStart().GetPosition(), p1->GetPosition() + translation);
    ASSERT_EQ(line->GetPEnd().GetPosition(), p2->GetPosition() + translation);
}
