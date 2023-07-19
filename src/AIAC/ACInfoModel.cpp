#include "aiacpch.h"

#include "AIAC/Application.h"
#include "ACInfoModel.h"

using namespace std;

namespace AIAC
{
    ///< Base Component
    void TimberInfo::Component::SetAsCurrent() {
        m_State = ACIMState::CURRENT;
        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetDoc().child("acim").child("timber").child("current").last_child().set_value(m_ID.c_str());
        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().Save();
    }

    void TimberInfo::Component::SetAsDone() {
        AIAC_INFO("timberInfo::Component::SetAsDone()");

        m_State = ACIMState::DONE;
        m_ACIMDocNode.child("state").last_child().set_value("Done");
        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().Save();
    }

    void TimberInfo::Component::SetAsNotDone() {
        m_State = ACIMState::NOT_DONE;
        m_ACIMDocNode.child("state").last_child().set_value("NotDone");
        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().Save();
    }

    ///< Hole 
    void TimberInfo::Hole::SetAsCurrent() {
        TimberInfo::Component::SetAsCurrent();
        AIAC_INFO("Set Current Component to Hole #" + m_ID);
        m_AxisGO->SetColor(HOLE_AXIS_COLOR[ACIMState::CURRENT]);
        m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[ACIMState::CURRENT]);
        m_RadiusLabelGO->SetVisibility(true);
    }

    void TimberInfo::Hole::SetAsDone() {
        TimberInfo::Component::SetAsDone();
        AIAC_INFO("Set " + m_ID + " as Done");
        m_AxisGO->SetColor(HOLE_AXIS_COLOR[ACIMState::DONE]);
        m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[ACIMState::DONE]);
        m_RadiusLabelGO->SetVisibility(false);
    }

    void TimberInfo::Hole::SetAsNotDone() {
        TimberInfo::Component::SetAsNotDone();
        AIAC_INFO("Set " + m_ID + " as Not Done");
        m_AxisGO->SetColor(HOLE_AXIS_COLOR[ACIMState::NOT_DONE]);
        m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[ACIMState::NOT_DONE]);
        m_RadiusLabelGO->SetVisibility(false);
    }

    ///< Cut
    void TimberInfo::Cut::SetAsCurrent() {
        TimberInfo::Component::SetAsCurrent();
        AIAC_INFO("Set Current Component to " + m_ID);
        for (const auto& [_, edge] : m_Edges) {
            edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::CURRENT]);
        }
    }

    void TimberInfo::Cut::SetAsDone() {
        TimberInfo::Component::SetAsDone();
        AIAC_INFO("Set " + m_ID + " as Done");
        for (const auto& [_, edge] : m_Edges) {
            edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::DONE]);
        }
    }

    void TimberInfo::Cut::SetAsNotDone() {
        TimberInfo::Component::SetAsNotDone();
        AIAC_INFO("Set " + m_ID + " as Not Done");
        for (const auto& [_, edge] : m_Edges) {
            edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::NOT_DONE]);
        }
    }

    void TimberInfo::Cut::Face::SetAsCurrent() {
        AIAC_INFO("Face::SetAsCurrent");
    }

    void TimberInfo::Cut::Edge::SetAsCurrent() {
        AIAC_INFO("Edge::SetAsCurrent");
    }



    std::vector<std::string> TimberInfo::GetAllComponentsIDs() const {
        // This is only for C++20, but we're using C++17, I leave it here for future reference
        // #include <ranges>
        // auto kv = std::views::keys(m_Components);
        // std::vector<std::string> keys{ kv.begin(), kv.end() };
        // return keys;
        std::vector<std::string> keys;
        for (const auto& [key, _] : m_Components) {
            keys.push_back(key);
        }
        return keys;
    }

    void TimberInfo::SetCurrentComponentTo(std::string id) {
        if(GetCurrentComponent() != nullptr){
            if(GetCurrentComponent()->IsMarkedDone){
                GetCurrentComponent()->SetAsDone();
            } else { // Not Done
                GetCurrentComponent()->SetAsNotDone();
            }
        }
        m_CurrentComponentID = id;
        m_Components[id]->SetAsCurrent();
    }

    void ACInfoModel::Load(std::string path) {
        m_FilePath = path;
        
        Clear();
        
        pugi::xml_parse_result result = m_ACIMDoc.load_file(path.c_str());
        if (!result){
            AIAC_ERROR("Could not load ACInfoModel from file: {0}", path);
            return;
        }
        for(auto timber = m_ACIMDoc.child("acim").child("timber"); timber; timber = timber.next_sibling("timber")){
            TimberInfo timberInfo;
            timberInfo.m_ID = timber.attribute("id").as_string();
            timberInfo.m_State = StringToState(timber.child("state").child_value());
            timberInfo.m_CurrentComponentID = timber.child("current").child_value();
            AIAC_INFO("Timber: {0}", timberInfo.m_ID);
            
            // Bounding Box
            auto bboxNode = timber.child("bbox");
            for(auto corner = bboxNode.child("corner"); corner; corner = corner.next_sibling("corner")){
                auto c = StringToVec3(corner.child_value());
                timberInfo.m_Bbox.push_back(c * m_Scale);
            }
            m_TimberInfo = timberInfo;

            // Holes
            for(auto hole = timber.child("hole"); hole; hole=hole.next_sibling("hole")){
                TimberInfo::Hole holeInfo;
                holeInfo.m_ACIMDocNode = hole;
                holeInfo.m_ID = hole.attribute("id").as_string();
                holeInfo.m_State = StringToState(hole.child("state").child_value());
                holeInfo.IsMarkedDone = holeInfo.m_State == ACIMState::DONE;
                holeInfo.m_Neighbors = StringToSet(hole.child("neighbours").child_value());
                if(holeInfo.m_Neighbors.size() == 1 && *holeInfo.m_Neighbors.begin() == "-1"){
                    AIAC_INFO("Hole: {0} has no neighbors", holeInfo.m_ID);
                    holeInfo.m_Neighbors.clear();
                }
                holeInfo.m_Start = StringToVec3(hole.child("start").child("coordinates").child_value()) * m_Scale;
                holeInfo.m_StartAccessible = StringToBool(hole.child("start").child("accessible").child_value());
                holeInfo.m_End = StringToVec3(hole.child("end").child("coordinates").child_value()) * m_Scale;
                holeInfo.m_EndAccessible = StringToBool(hole.child("end").child("accessible").child_value());
                holeInfo.m_Radius = std::stof(hole.child("radius").child_value()) * m_Scale;

                // build GOPrimitive
                holeInfo.m_AxisGO = GOLine::Add(holeInfo.m_Start, holeInfo.m_End, 2.0f);
                holeInfo.m_AxisGO->SetColor(HOLE_AXIS_COLOR[holeInfo.m_State]);
                holeInfo.m_CylinderGO = GOCylinder::Add(holeInfo.m_Start, holeInfo.m_End, holeInfo.m_Radius);
                holeInfo.m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[holeInfo.m_State]);
                holeInfo.m_StartPointGO = GOPoint::Add(holeInfo.m_Start, 2.0f);
                holeInfo.m_EndPointGO = GOPoint::Add(holeInfo.m_End, 2.0f);
                auto centerPoint = (holeInfo.m_Start + holeInfo.m_End) * 0.5f;
                holeInfo.m_IDLabelGO = GOText::Add(holeInfo.m_ID, centerPoint, 0.75f);
                auto radiusText = std::to_string(holeInfo.m_Radius);
                radiusText = radiusText.substr(0, radiusText.find(".") + 3);
                holeInfo.m_RadiusLabelGO = GOText::Add(radiusText, holeInfo.m_Start, 0.75f);
                holeInfo.m_RadiusLabelGO->SetVisibility(false);

                holeInfo.m_GOPrimitives.push_back(holeInfo.m_AxisGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_CylinderGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_StartPointGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_EndPointGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_IDLabelGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_RadiusLabelGO);

                m_TimberInfo.m_Holes[holeInfo.m_ID] = holeInfo;
                m_TimberInfo.m_Components[holeInfo.m_ID] = &m_TimberInfo.m_Holes[holeInfo.m_ID];
            }

            // cuts
            for(auto cut = timber.child("cut"); cut; cut=cut.next_sibling("cut")){
                TimberInfo::Cut cutInfo;
                cutInfo.m_ACIMDocNode = cut;
                cutInfo.m_ID = cut.attribute("id").as_string();
                cutInfo.m_State = StringToState(cut.child("state").child_value());
                cutInfo.IsMarkedDone = cutInfo.m_State == ACIMState::DONE;
                cutInfo.m_Center = StringToVec3(cut.child("center").child_value()) * m_Scale;
                cutInfo.m_IDLabelGO = GOText::Add(cutInfo.m_ID, cutInfo.m_Center, 0.75f);
                cutInfo.m_GOPrimitives.push_back(cutInfo.m_IDLabelGO);

                auto nonExposedEdges = std::set<std::string>();

                auto faces = cut.child("faces");
                for(auto face = faces.child("face"); face; face=face.next_sibling("face")){
                    TimberInfo::Cut::Face faceInfo;
                    faceInfo.m_ID = face.attribute("id").as_string();
                    faceInfo.m_Exposed = StringToBool(face.child("exposed").child_value());
                    faceInfo.m_State = StringToState(face.child("state").child_value());
                    faceInfo.m_Edges = StringToSet(face.child("edges").child_value());
                    if(!faceInfo.m_Exposed){
                        nonExposedEdges.insert(faceInfo.m_Edges.begin(), faceInfo.m_Edges.end());
                    }
                    cutInfo.m_Faces[faceInfo.m_ID] = faceInfo;
                }

                auto edges = cut.child("edges");
                for(auto edge = edges.child("edge"); edge; edge=edge.next_sibling("edge")){
                    auto id = edge.attribute("id").as_string();
                    // only work with non-exposed edges
                    if(nonExposedEdges.find(id) == nonExposedEdges.end()){
                        continue;
                    }

                    TimberInfo::Cut::Edge edgeInfo;
                    edgeInfo.m_ID = edge.attribute("id").as_string();
                    edgeInfo.m_Start = StringToVec3(edge.child("start").child_value()) * m_Scale;
                    edgeInfo.m_End = StringToVec3(edge.child("end").child_value()) * m_Scale;

                    // build GOPrimitive
                    edgeInfo.m_GO = GOLine::Add(edgeInfo.m_Start, edgeInfo.m_End, 2.0f);
                    edgeInfo.m_GO->SetColor(CUT_EDGE_COLOR[cutInfo.m_State]);
                    edgeInfo.m_GOPrimitives.push_back(edgeInfo.m_GO);


                    cutInfo.m_Edges[edgeInfo.m_ID] = edgeInfo;
                }
                m_TimberInfo.m_Cuts[cutInfo.m_ID] = cutInfo;
                m_TimberInfo.m_Components[cutInfo.m_ID] = &m_TimberInfo.m_Cuts[cutInfo.m_ID];
            }
            if(m_TimberInfo.GetCurrentComponent() == nullptr){
                m_TimberInfo.m_CurrentComponentID = m_TimberInfo.m_Components.begin()->first;
            }
            m_TimberInfo.GetCurrentComponent()->SetAsCurrent();
        }
        UpdateBboxGOLine();
    }

    void ACInfoModel::Save() {
        m_ACIMDoc.save_file(m_FilePath.c_str());        
    }

    void ACInfoModel::Clear() {
        for(auto& line : m_BboxGOLines)
            GOLine::Remove(line);
        m_BboxGOLines.clear();

        for(auto& hole : m_TimberInfo.m_Holes){
            for(auto& primitive : hole.second.m_GOPrimitives)
                GOPrimitive::Remove(primitive);
        }
        m_TimberInfo.m_Holes.clear();

        for(auto& cut : m_TimberInfo.m_Cuts){
            for(auto& face : cut.second.m_Faces){
                for(auto& primitive : face.second.m_GOPrimitives)
                    GOPrimitive::Remove(primitive);
            }
            for(auto& edge : cut.second.m_Edges){
                for(auto& primitive : edge.second.m_GOPrimitives)
                    GOPrimitive::Remove(primitive);
            }
        }
        m_TimberInfo.m_Cuts.clear();
        m_TimberInfo.m_Components.clear();
    }

    void ACInfoModel::UpdateBboxGOLine() {
        auto bbox = m_TimberInfo.m_Bbox;

        // update the GOLine references
        for(auto& line : m_BboxGOLines)
            GOLine::Remove(line);

        // bottom
        // auto vec = glm::normalize(bbox[1] - bbox[0]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[0] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[1] - vec, 2.0f));
        // vec = glm::normalize(bbox[2] - bbox[1]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[1] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[2] - vec, 2.0f));
        // vec = glm::normalize(bbox[3] - bbox[2]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[2] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[3] - vec, 2.0f));
        // vec = glm::normalize(bbox[0] - bbox[3]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[3] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[0] - vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[1], 1.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[2], 1.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[3], 1.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[0], 1.0f));

        // top
        // vec = glm::normalize(bbox[5] - bbox[4]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[4] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[5] - vec, 2.0f));
        // vec = glm::normalize(bbox[6] - bbox[5]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[5] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[6] - vec, 2.0f));
        // vec = glm::normalize(bbox[7] - bbox[6]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[6] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[7] - vec, 2.0f));
        // vec = glm::normalize(bbox[4] - bbox[7]);
        // m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[7] + vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[4] - vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[5], 1.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[6], 1.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[7], 1.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[4], 1.0f));
        
        // side
        m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[4], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[5], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[6], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[7], 2.0f));

        // change color of the bounding box
        for(auto line : m_BboxGOLines)
            line->SetColor(glm::vec4(0.7f, 0.7f, 0.5f, 0.5f));
            
    }

    void ACInfoModel::TransformGOPrimitives(glm::mat4x4 transformMat) {
        // bounding box
        auto bbox = m_TimberInfo.m_Bbox;
        for(int i = 0 ; i < bbox.size() ; i++){
            m_TimberInfo.m_Bbox[i] = glm::vec3(transformMat * glm::vec4(bbox[i], 1.0f));
        }
        bbox = m_TimberInfo.m_Bbox;
        UpdateBboxGOLine();

        // holes
        for(auto& kv : m_TimberInfo.m_Holes){
            auto holeInfo = kv.second;
            for(auto& objs : holeInfo.m_GOPrimitives){
                objs->Transform(transformMat);
            }
        }

        // cuts
        for(auto& kv : m_TimberInfo.m_Cuts){
            auto cutInfo = kv.second;
            for(auto& objs : cutInfo.m_GOPrimitives){
                objs->Transform(transformMat);
            }
            // Face has no GOPrimitives now
            for(auto& kv : cutInfo.m_Faces){
                auto faceInfo = kv.second;
                for(auto& objs : faceInfo.m_GOPrimitives){
                    objs->Transform(transformMat);
                }
            }
            // Edge
            for(auto& kv : cutInfo.m_Edges){
                auto edgeInfo = kv.second;
                for(auto& objs : edgeInfo.m_GOPrimitives){
                    objs->Transform(transformMat);
                }
            }
        }

    }

    float ACInfoModel::GetLength(){
        auto bbox = m_TimberInfo.m_Bbox;
        
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
        // convert str to lowercase
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        std::string trueStr = "true";
        std::string falseStr = "false";
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

