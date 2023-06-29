#include "aiacpch.h"

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
            AIAC_INFO("Timber: {0}", timberInfo.m_ID);
            
            // Bounding Box
            auto bboxNode = timber.child("bbox");
            for(auto corner = bboxNode.child("corner"); corner; corner = corner.next_sibling("corner")){
                glm::vec3 p;
                auto ss = stringstream(corner.child_value());
                ss >> p.x >> p.y >> p.z;
                timberInfo.m_Bbox.push_back(p * m_Scale);
            }
            m_TimberInfo[timberInfo.m_ID] = timberInfo;
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
        for(auto& id : m_BboxGOLineIDs)
            GOLine::Remove(id);

        // bottom
        // cout << "bbox[0]: " << bbox[0].x << ", " << bbox[0].y << ", " << bbox[0].z << endl;
        // cout << "bbox[1]: " << bbox[1].x << ", " << bbox[1].y << ", " << bbox[1].z << endl;
        // cout << "bbox[2]: " << bbox[2].x << ", " << bbox[2].y << ", " << bbox[2].z << endl;
        // cout << "bbox[3]: " << bbox[3].x << ", " << bbox[3].y << ", " << bbox[3].z << endl;
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[1], bbox[0], 2.0f)); // O
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[1], bbox[2], 2.0f)); // X
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[2], bbox[3], 2.0f)); // O
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[3], bbox[0], 2.0f)); // X
        // top
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[4], bbox[5], 2.0f));
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[5], bbox[6], 2.0f));
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[6], bbox[7], 2.0f));
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[7], bbox[4], 2.0f));
        // side
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[0], bbox[4], 2.0f));
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[1], bbox[5], 2.0f));
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[2], bbox[6], 2.0f));
        m_BboxGOLineIDs.push_back(GOLine::Add(bbox[3], bbox[7], 2.0f));

        // change color of the bounding box
        // for(int i = 0; i < 4; i++)
        //     GOLine::Get(m_BboxGOLineIDs[i])->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.3f));
        // for(int i = 4; i < 8; i++)
        //     GOLine::Get(m_BboxGOLineIDs[i])->SetColor(glm::vec4(0.0f, 1.0f, 1.0f, 0.3f));
        // for(int i = 8; i < 12; i++)
        //     GOLine::Get(m_BboxGOLineIDs[i])->SetColor(glm::vec4(1.0f, 0.0f, 1.0f, 0.3f));
    }

    void ACInfoModel::TransformGOPrimitives(glm::mat4x4 transformMat) {
        // bounding box
        auto bbox = m_TimberInfo[m_CurrentActiveTimberID].m_Bbox;
        for(int i = 0 ; i < bbox.size() ; i++){
            m_TimberInfo[m_CurrentActiveTimberID].m_Bbox[i] = glm::vec3(transformMat * glm::vec4(bbox[i], 1.0f));
        }
        bbox = m_TimberInfo[m_CurrentActiveTimberID].m_Bbox;
        UpdateBboxGOLine();

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

} // namespace AIAC

