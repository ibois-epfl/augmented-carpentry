#include "aiacpch.h"

#include "AIAC/Application.h"
#include "ACInfoModel.h"

using namespace std;

//FIXME:: do we still need this class?
namespace AIAC
{
    void ACInfoModel::Load(std::string path) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(path.c_str());
        if (!result){
            AIAC_ERROR("Could not load ACInfoModel from file: {0}", path);
            return;
        }
        for(auto timber = doc.child("acim").child("timber"); timber; timber = timber.next_sibling("timber")){
            TimberInfo timberInfo;
            timberInfo.m_ID = timber.attribute("id").as_string();
            timberInfo.m_State = StringToState(timber.child("state").child_value());
            AIAC_INFO("Timber: {0}", timberInfo.m_ID);
            
            // Bounding Box
            auto bboxNode = timber.child("bbox");
            for(auto corner = bboxNode.child("corner"); corner; corner = corner.next_sibling("corner")){
                auto c = StringToVec3(corner.child_value());
                timberInfo.m_Bbox.push_back(c * m_Scale);
            }
            m_TimberInfo[timberInfo.m_ID] = timberInfo;

            // Holes
            for(auto hole = timber.child("hole"); hole; hole=hole.next_sibling("hole")){
                TimberInfo::Hole holeInfo;
                holeInfo.m_ID = hole.attribute("id").as_string();
                holeInfo.m_State = StringToState(hole.child("state").child_value());
                holeInfo.m_Neighbors = StringToSet(hole.child("neighbours").child_value());
                if(holeInfo.m_Neighbors.size() == 1 && *holeInfo.m_Neighbors.begin() == "-1"){
                    AIAC_INFO("Hole: {0} has no neighbors", holeInfo.m_ID);
                    holeInfo.m_Neighbors.clear();
                }
                holeInfo.m_Start = StringToVec3(hole.child("start").child("coordinates").child_value()) * m_Scale;
                holeInfo.m_StartAccessible = StringToBool(hole.child("start").child("accessible").child_value());
                holeInfo.m_End = StringToVec3(hole.child("end").child("coordinates").child_value()) * m_Scale;
                holeInfo.m_EndAccessible = StringToBool(hole.child("end").child("accessible").child_value());
                holeInfo.m_Radius = std::stof(hole.child("radius").child_value());

                // print out the hole info
                // AIAC_INFO("Hole: {0}", holeInfo.m_ID);
                // AIAC_INFO("State: {0}", int(holeInfo.m_State));
                // AIAC_INFO("Radius: {0}", holeInfo.m_Radius);
                // AIAC_INFO("Start: {0}, {1}, {2}", holeInfo.m_Start.x, holeInfo.m_Start.y, holeInfo.m_Start.z);
                // AIAC_INFO("End: {0}, {1}, {2}", holeInfo.m_End.x, holeInfo.m_End.y, holeInfo.m_End.z);
                // AIAC_INFO("Start Accessible: {0}", holeInfo.m_StartAccessible);
                // AIAC_INFO("End Accessible: {0}", holeInfo.m_EndAccessible);
                // for(auto& n : holeInfo.m_Neighbors){
                //     AIAC_INFO("Neighbor: {0}", n);
                // }

                // build primitive
                auto holeAxis = GOLine::Add(holeInfo.m_Start, holeInfo.m_End, 3.0f);
                holeAxis->SetColor(glm::vec4(0.27f, 0.75f, 0.86f, 0.7f));
                auto holeCylinder = GOCylinder::Add(holeInfo.m_Start, holeInfo.m_End, holeInfo.m_Radius);
                holeCylinder->SetColor(glm::vec4(0.27f, 0.75f, 0.86f, 0.2f));
                auto startPoint = GOPoint::Add(holeInfo.m_Start, 2.0f);
                auto endPoint = GOPoint::Add(holeInfo.m_End, 2.0f);
                auto radiusText = std::to_string(holeInfo.m_Radius);
                radiusText = radiusText.substr(0, radiusText.find(".") + 3);
                auto label = GOText::Add(radiusText, holeInfo.m_Start, 2.0f);
                holeInfo.m_GOPrimitives.push_back(holeAxis);
                holeInfo.m_GOPrimitives.push_back(startPoint);
                holeInfo.m_GOPrimitives.push_back(endPoint);
                holeInfo.m_GOPrimitives.push_back(label);

                m_TimberInfo[timberInfo.m_ID].m_Holes[holeInfo.m_ID] = holeInfo;
            }
        }
        m_CurrentActiveTimberID = m_TimberInfo.begin()->first;
        UpdateBboxGOLine();
    }

    std::vector<std::string> ACInfoModel::GetTimberIDs() const {
        std::vector<std::string> ids;
        for (auto& kv : m_TimberInfo) {
            ids.push_back(kv.first);
        }
        return ids;
    }

    TimberInfo ACInfoModel::GetTimberInfo(std::string id) {
        return m_TimberInfo[id];
    }

    void ACInfoModel::UpdateBboxGOLine() {
        auto bbox = GetActiveTimberInfo().m_Bbox;
        
        // print the axis of the bounding box
        // for(auto& p : bbox){
        //     AIAC_INFO("Bbox: {0}, {1}, {2}", p.x, p.y, p.z);
        // }

        // update the GOLine references
        for(auto& line : m_BboxGOLines)
            GOLine::Remove(line);

        // bottom
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[0], 2.0f)); // O
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[2], 2.0f)); // X
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[3], 2.0f)); // O
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[0], 2.0f)); // X
        // top
        m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[5], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[6], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[7], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[4], 2.0f));
        // side
        m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[4], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[5], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[6], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[7], 2.0f));

        // change color of the bounding box
        // for(int i = 0; i < 4; i++)
        //     GOLine::Get(m_BboxGOLineIDs[i])->SetColor(glm::vec4(0.0f, 2.0f, 0.0f, 0.3f));
        // for(int i = 4; i < 8; i++)
        //     GOLine::Get(m_BboxGOLineIDs[i])->SetColor(glm::vec4(0.0f, 2.0f, 2.0f, 0.3f));
        // for(int i = 8; i < 12; i++)
        //     GOLine::Get(m_BboxGOLineIDs[i])->SetColor(glm::vec4(2.0f, 0.0f, 2.0f, 0.3f));
    }

    void ACInfoModel::TransformGOPrimitives(glm::mat4x4 transformMat) {
        // bounding box
        auto bbox = m_TimberInfo[m_CurrentActiveTimberID].m_Bbox;
        for(int i = 0 ; i < bbox.size() ; i++){
            m_TimberInfo[m_CurrentActiveTimberID].m_Bbox[i] = glm::vec3(transformMat * glm::vec4(bbox[i], 2.0f));
        }
        bbox = m_TimberInfo[m_CurrentActiveTimberID].m_Bbox;
        UpdateBboxGOLine();

        // holes
        for(auto& kv : m_TimberInfo[m_CurrentActiveTimberID].m_Holes){
            auto holeInfo = kv.second;
            for(auto& objs : holeInfo.m_GOPrimitives){
                objs->Transform(transformMat);
            }
        }
    }

    float ACInfoModel::GetLength(){
        auto bbox = m_TimberInfo[m_CurrentActiveTimberID].m_Bbox;
        
        float dist = 0.0f;
        dist += glm::distance(bbox[0], bbox[1]);
        dist += glm::distance(bbox[2], bbox[3]);
        dist += glm::distance(bbox[4], bbox[5]);
        dist += glm::distance(bbox[6], bbox[7]);
        dist /= 4.0f;

        return dist;
    }

    ACIMState ACInfoModel::StringToState(std::string state){
        std::string notDoneStr = "NotDone";
        std::string doneStr = "Done";
        std::string currentStr = "Current";
        if(!state.compare(0, notDoneStr.length(), notDoneStr)){
            return ACIMState::NOT_DONE;
        }
        else if(!state.compare(0, doneStr.length(), doneStr)){
            return ACIMState::DONE;
        }
        else if(!state.compare(0, currentStr.length(), currentStr)){
            return ACIMState::CURRENT;
        }
        else {
            AIAC_ERROR("Invalid state string: {0}", state);
            return ACIMState::NOT_DONE;
        }
    }

    glm::vec3 ACInfoModel::StringToVec3(std::string str){
        glm::vec3 vec;
        auto ss = stringstream(str);
        ss >> vec.x >> vec.y >> vec.z;
        return vec;
    }

    std::vector<std::string> ACInfoModel::StringToTokens(std::string str){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, ' ')){
            tokens.push_back(token);
        }
        return tokens;
    }

    std::set<std::string> ACInfoModel::StringToSet(std::string str){
        std::set<std::string> set;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, ' ')){
            set.insert(token);
        }
        return set;
    }

    bool ACInfoModel::StringToBool(std::string str){
        std::string trueStr = "True";
        std::string falseStr = "False";
        if(!str.compare(0, trueStr.length(), trueStr)){
            return true;
        }
        else if(!str.compare(0, falseStr.length(), falseStr)){
            return false;
        }
        else {
            AIAC_ERROR("Invalid bool string: {0}", str);
            return false;
        }
    }

} // namespace AIAC

