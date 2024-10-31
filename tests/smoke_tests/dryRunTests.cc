#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

class PoseInfo {
public:
    PoseInfo() = default;
    PoseInfo(const bool isTracked, const std::array<float, 7> &data) {
        // copy data to member
        m_IsTracked = isTracked;
        m_Data = data;
    }

    void print() {
        std::cout << "Tracked: " << m_IsTracked << " ";
        if (m_IsTracked) {
            for(int i = 0 ; i < 7 ; i++) {
                std::cout << m_Data[i] << " ";
            }
        }
    }

    bool operator==(const PoseInfo &other) const {
        if (m_IsTracked != other.m_IsTracked) {
            return false;
        }

        for(int i = 0 ; i < 7 ; i++) {
            if(abs(m_Data[i] - other.m_Data[i]) > 1e-2) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const PoseInfo &other) const {
        return !(*this == other);
    };

private:
    bool m_IsTracked = false;
    std::array<float, 7> m_Data = {0};
};


class FrameInfo {
public:
    FrameInfo() = default;
    FrameInfo(const int frameId, const PoseInfo &slamPoseInfo, const PoseInfo &ttoolPoseInfo) {
        m_FrameId = frameId;
        m_SLAMPoseInfo = slamPoseInfo;
        m_TToolPoseInfo = ttoolPoseInfo;
    }

    void SetSLAMInfo(const PoseInfo &slamInfo) {
        m_SLAMPoseInfo = slamInfo;
    }

    void SetTToolInfo(const PoseInfo &ttoolInfo) {
        m_TToolPoseInfo = ttoolInfo;
    }

    void print() {
        std::cout << "FrameId: " << m_FrameId << std::endl;
        std::cout << "SLAM Pose: ";
        m_SLAMPoseInfo.print();

        std::cout << "TTool Pose: ";
        m_TToolPoseInfo.print();
    }

    bool operator==(const FrameInfo &other) const {
        if (m_FrameId != other.m_FrameId) {
            return false;
        }

        if (m_SLAMPoseInfo != other.m_SLAMPoseInfo) {
            return false;
        }

        if (m_TToolPoseInfo != other.m_TToolPoseInfo) {
            return false;
        }

        return true;
    }

    bool operator!=(const FrameInfo &other) const {
        return !(*this == other);
    };

private:
    int m_FrameId = 0;
    PoseInfo m_SLAMPoseInfo;
    PoseInfo m_TToolPoseInfo;
};

std::unordered_map<int, FrameInfo> parseLog(const std::string& path) {
    // check if file exist
    if(!std::filesystem::exists(path)){
        throw std::invalid_argument("No log file found at " + path);
    }

    // Open the text file named "input.txt"
    std::ifstream f(path);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
        return {};
    }

    // String variable to store the read data
    std::string s;

    // Result map
    std::unordered_map<int, FrameInfo> logInfo;

    // Skip until reach content block
    while (getline(f, s)) {
        if(s.rfind("[Content]", 0) == 0) {
            break;
        }
    }

    int frameId;
    long long timestamp;
    FrameInfo frameInfo;
    bool hasSLAMData = false, hasTToolData = false;

    while (getline(f, s)) {
        if(s.front() == '#') {
            // Record the previous frame info
            if (hasSLAMData) {
                logInfo[frameId] = frameInfo;
                hasSLAMData = false;
            }

            std::stringstream ss(s.substr(1));
            ss >> frameId;
            ss >> timestamp;
        }

        else if (s.rfind("SLAM", 0) == 0) {
            hasSLAMData = true;

            std::stringstream ss(s);

            // Consume the "SLAM" string
            std::string tmp;
            ss >> tmp;

            // Parse the Pose data
            std::array<float, 7> data{};
            for(int i = 0 ; i < 7 ; i++) {
                ss >> data[i];
            }
            frameInfo.SetSLAMInfo(PoseInfo(true, data));
        }

        else if (s.rfind("TTool-pose", 0) == 0) {
            std::stringstream ss(s);

            // Consume the "TTool-pose" and "None"(status) string
            std::string tmp;
            ss >> tmp >> tmp;

            // Parse the Pose data
            std::array<float, 7> data{};
            for(int i = 0 ; i < 7 ; i++) {
                ss >> data[i];
            }
            frameInfo.SetTToolInfo(PoseInfo(true, data));
        }
    }

    return logInfo;
}


TEST(SmokeTest, DryRun) {
    // run the build/bin/AC executable with the config.ini file and run it from root of the repo
    // the executable should run without any errors
    std::cout << "Running smoke test, working path: " << std::filesystem::current_path() << std::endl;
    system("xvfb-run -a bin/AC ../tests/assets/config_smoke_test.ini");

    auto gtData = parseLog("../tests/assets/log_gt.txt");
    auto testData = parseLog("../tests/output/log_recorders/test/log.txt");

    int mismatchCount = 0;
    for(auto &[frameId, frameInfo] : gtData) {
        if (testData.find(frameId) == testData.end()) {
            mismatchCount++;
            continue;
        }

        if (frameInfo != testData[frameId]) {
            mismatchCount++;
        }
    }

    double errorRate = static_cast<double>(mismatchCount) / gtData.size();
    bool isErrorRateAcceptable = errorRate < 0.05f;
    std::cout << "----- Smoke Test Result -----" << std::endl;
    std::cout << "Total frame count: " << gtData.size() << std::endl;
    std::cout << "Missmatch frame count: " << mismatchCount << std::endl;
    std::cout << "Error rate: " << errorRate << " -> Test ";
    if (isErrorRateAcceptable) {
        std::cout << "pass";
    } else {
        std::cout << "failed";
    }
    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;

    EXPECT_TRUE(isErrorRateAcceptable);
}