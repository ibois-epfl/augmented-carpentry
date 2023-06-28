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
            // Bounding Box
            auto bboxNode = timber.child("bbox");
            for(auto corner = bboxNode.child("corner"); corner; corner = corner.next_sibling("corner")){
                glm::vec3 p;
                auto ss = stringstream(corner.value());
                ss >> p.x >> p.y >> p.z;
                timberInfo.m_Bbox.push_back(p);
            }
            m_TimberInfo[timberInfo.m_ID] = timberInfo;
        }
        m_CurrentActiveTimberID = m_TimberInfo.begin()->first;
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

} // namespace AIAC

