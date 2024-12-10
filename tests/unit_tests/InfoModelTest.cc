#include <gtest/gtest.h>
#include "AIAC/ACInfoModel.h"

#include <glm/gtx/string_cast.hpp>
#include <set>

auto const MAX_ABS_ERROR = 1e-3f;

class InfoModelTest : public ::testing::Test {
protected:
    void SetUp() override { }

    void TearDown() override {}
};

TEST_F(InfoModelTest, FileIO) {
    AIAC::ACInfoModel acim;

    std::string path = "/mnt/augmented-carpentry/assets/ACModel/test.acim";
    acim.Load(path);

    EXPECT_EQ(acim.GetFilePath(), path);
    EXPECT_EQ(acim.GetName(), "test");
}

TEST_F(InfoModelTest, ContentParsing) {
    AIAC::ACInfoModel acim;

    std::string path = "/mnt/augmented-carpentry/assets/ACModel/test.acim";
    acim.Load(path);

    auto& timberInfo = acim.GetTimberInfo();

    // bounding box
    auto bboxPts = timberInfo.GetBoundingBox();
    EXPECT_EQ(bboxPts.size(), 8);

    ASSERT_TRUE(glm::distance(glm::vec3(0, 0, -8.07965638975e-07f),             bboxPts[0]) < MAX_ABS_ERROR);
    ASSERT_TRUE(glm::distance(glm::vec3(1.85073895234f, 0, 0.130034050856f),    bboxPts[5]) < MAX_ABS_ERROR);
    ASSERT_TRUE(glm::distance(glm::vec3(0, 0.129643784514f, 0.130034050856f),   bboxPts[7]) < MAX_ABS_ERROR);
    
    // components
    std::vector<std::string> allComponentsIDs = timberInfo.GetAllComponentsIDs();
    std::unordered_set<std::string> allComponentsIDsSet(allComponentsIDs.begin(), allComponentsIDs.end());

    std::vector<std::string> expectedIDs = {
        "Hole#1", "Hole#2", "Hole#3", "Hole#4", "Hole#5", "Hole#6", "Hole#7", "Hole#8", "Hole#9", "Hole#10",
        "Cut#1", "Cut#2", "Cut#3", "Cut#4", "Cut#5", "Cut#6", "Cut#7"
    };

    ASSERT_EQ(allComponentsIDsSet.size(), expectedIDs.size());
    for (auto& id : expectedIDs) {
        ASSERT_NE(allComponentsIDsSet.find(id), allComponentsIDsSet.end());
    }

    // holes
    auto hole1 = static_cast<AIAC::TimberInfo::Hole*>(timberInfo.GetComponent("Hole#1"));
    ASSERT_EQ(hole1->GetRadius(), 0.025f);
    ASSERT_EQ(hole1->GetStartPointGO()->GetPosition(), glm::vec3(0.171164716736f, 0.0874013529763f, 0.130030809657f));
    ASSERT_EQ(hole1->GetEndPointGO()->GetPosition(), glm::vec3(0.171164716736f, 0.0874013529763f, 6.34902733979e-16f));
    ASSERT_EQ(hole1->GetCenter(), glm::vec3(0.171164716736f, 0.0874013529763f, 0.0650154048285f));
    
    // cuts
    auto cut1 = static_cast<AIAC::TimberInfo::Cut*>(timberInfo.GetComponent("Cut#1"));
    ASSERT_EQ(cut1->GetCenter(), glm::vec3(0.543917917169f, 0.064821892257f, 0.10202644336f));
    ASSERT_EQ(cut1->GetAllFaces().size(), 3); // 3 unexposed faces
    ASSERT_EQ(cut1->GetAllEdges().size(), 12);

    auto face1 = cut1->GetFace("1");
    auto edges = face1.GetEdges();
    ASSERT_EQ(edges.size(), 4);
    auto edgeIdSet = std::unordered_set<std::string>(edges.begin(), edges.end());
    for(auto& edgeId : {"0", "2", "5", "7"}) {
        ASSERT_NE(edgeIdSet.find(edgeId), edgeIdSet.end());
    }

    auto corners = face1.GetCorners();
    ASSERT_EQ(corners.size(), 4);
    ASSERT_TRUE(glm::distance(corners[0], glm::vec3(0.650908f,  0.129637f, 0.074019f)) < MAX_ABS_ERROR);
    ASSERT_TRUE(glm::distance(corners[1], glm::vec3(0.583188f,  0.000000f, 0.074019f)) < MAX_ABS_ERROR);
    ASSERT_TRUE(glm::distance(corners[2], glm::vec3(0.583188f, -0.000000f, 0.130034f)) < MAX_ABS_ERROR);
    ASSERT_TRUE(glm::distance(corners[3], glm::vec3(0.650908f,  0.129644f, 0.130034f)) < MAX_ABS_ERROR);

    auto edge0 = cut1->GetEdge("0");
    ASSERT_EQ(edge0.GetStartPt().GetPosition(), glm::vec3(0.583187494871f, -1.33226762955e-15f, 0.130034050856f));
    ASSERT_EQ(edge0.GetEndPt().GetPosition(), glm::vec3(0.583187494871f, 6.66133814775e-16f, 0.0740188358647f));
}