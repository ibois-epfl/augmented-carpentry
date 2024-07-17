#include "aiacpch.h"

#include "AIAC/Application.h"
#include "ACInfoModel.h"
#include "AIAC/Config.h"

#include <cmath>


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

    void TimberInfo::Component::SetVisibility(bool visible) {
        for (auto& go : m_GOPrimitives) {
            go->SetVisibility(visible);
        }
    }

    ///< Hole 
    void TimberInfo::Hole::SetAsCurrent() {
        TimberInfo::Component::SetAsCurrent();
        AIAC_INFO("Set Current Component to Hole #" + m_ID);
        m_AxisGO->SetColor(HOLE_AXIS_COLOR[ACIMState::CURRENT]);
        m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[ACIMState::CURRENT]);
    }

    void TimberInfo::Hole::SetAsDone() {
        TimberInfo::Component::SetAsDone();
        AIAC_INFO("Set " + m_ID + " as Done");
        m_AxisGO->SetColor(HOLE_AXIS_COLOR[ACIMState::DONE]);
        m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[ACIMState::DONE]);
    }

    void TimberInfo::Hole::SetAsNotDone() {
        TimberInfo::Component::SetAsNotDone();
        AIAC_INFO("Set " + m_ID + " as Not Done");
        m_AxisGO->SetColor(HOLE_AXIS_COLOR[ACIMState::NOT_DONE]);
        m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[ACIMState::NOT_DONE]);
    }

    void TimberInfo::Hole::SwapStartEnd() {
        // holeInfo.m_Start = StringToVec3(hole.child("start").child("coordinates").child_value()) * m_Scale;
        // holeInfo.m_StartExposed = StringToBool(hole.child("start").child("exposed").child_value());
        // holeInfo.m_End = StringToVec3(hole.child("end").child("coordinates").child_value()) * m_Scale;
        // holeInfo.m_EndExposed = StringToBool(hole.child("end").child("exposed").child_value());
        
        // Update .acim doc
        std::swap(m_Start, m_End);
        std::swap(m_StartExposed, m_EndExposed);

        m_ACIMDocNode.child("start").child("coordinates").last_child().set_value(Vec3ToString(m_Start / m_Scale).c_str());
        m_ACIMDocNode.child("start").child("exposed").last_child().set_value(m_StartExposed ? "True" : "False");
        m_ACIMDocNode.child("end").child("coordinates").last_child().set_value(Vec3ToString(m_End / m_Scale).c_str());
        m_ACIMDocNode.child("end").child("exposed").last_child().set_value(m_EndExposed ? "True" : "False");

        // Update system
        auto curStart = m_StartPointGO->GetPosition();
        auto curEnd = m_EndPointGO->GetPosition();

        m_StartPointGO->SetPosition(curEnd);
        m_EndPointGO->SetPosition(curStart);
        m_AxisGO->SetPts(curEnd, curStart);

        AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().Save();
    }
    
    void TimberInfo::Hole::SetVisibility(bool visible) {
        TimberInfo::Component::SetVisibility(visible);
    }

    ///< Cut
    void TimberInfo::Cut::SetAsCurrent() {
        TimberInfo::Component::SetAsCurrent();
        AIAC_INFO("Set Current Component to " + m_ID);
        for (const auto& [_, face] : m_Faces) {
            if(face.m_GO != nullptr){
                face.m_GO->SetColor(CUT_FACE_COLOR[ACIMState::CURRENT]);
            }
        }
        for (const auto& [_, edge] : m_Edges) {
            if(edge.m_GO != nullptr){
                edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::CURRENT]);
            }
        }
    }

    void TimberInfo::Cut::SetAsDone() {
        TimberInfo::Component::SetAsDone();
        AIAC_INFO("Set " + m_ID + " as Done");
        for (const auto& [_, face] : m_Faces) {
            if(face.m_GO != nullptr){
                face.m_GO->SetColor(CUT_FACE_COLOR[ACIMState::DONE]);
            }
        }
        for (const auto& [_, edge] : m_Edges) {
            if(edge.m_GO != nullptr){
                edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::DONE]);
            }
        }
    }

    void TimberInfo::Cut::SetAsNotDone() {
        TimberInfo::Component::SetAsNotDone();
        AIAC_INFO("Set " + m_ID + " as Not Done");
        for (const auto& [_, face] : m_Faces) {
            if(face.m_GO != nullptr){
                face.m_GO->SetColor(CUT_FACE_COLOR[ACIMState::NOT_DONE]);
            }
        }
        for (const auto& [_, edge] : m_Edges) {
            if(edge.m_GO != nullptr){
                edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::NOT_DONE]);
            }
        }
    }

    void TimberInfo::Cut::SetVisibility(bool visible) {
        TimberInfo::Component::SetVisibility(visible);
        for (const auto& [_, face] : m_Faces) {
            if(face.m_GO != nullptr){
                face.m_GO->SetVisibility(visible);
            }
        }
        for (const auto& [_, edge] : m_Edges) {
            if(edge.m_GO != nullptr){
                edge.m_GO->SetVisibility(visible);
            }
        }
    }

    void TimberInfo::Cut::HighlightFace(const std::string& faceID, glm::vec4 color) {
        if(faceID == m_HighlightedFaceID) return;

        // faceID is empty -> Reset everything to CURRENT
        if(faceID.empty()){
            for(auto& [_, face] : m_Faces){
                if(face.m_GO != nullptr){
                    face.m_GO->SetColor(CUT_FACE_COLOR[ACIMState::CURRENT]);
                }
            }
            for(auto& [_, edge] : m_Edges){
                if(edge.m_GO != nullptr){
                    edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::CURRENT]);
                }
            }
            m_HighlightedFaceID = "";
            return;
        }
        
        if(m_HighlightedFaceID.empty()){
            // init : set all to NOT_DONE
            for(auto& [_, face] : m_Faces){
                if(face.m_GO != nullptr){
                    face.m_GO->SetColor(CUT_FACE_COLOR[ACIMState::NOT_DONE]);
                }
            }
            for(auto& [_, edge] : m_Edges){
                if(edge.m_GO != nullptr){
                    edge.m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::NOT_DONE]);
                }
            }
        } else {
            // reset the previous Highlighted face
            m_Faces[m_HighlightedFaceID].m_GO->SetColor(CUT_FACE_COLOR[ACIMState::NOT_DONE]);
            for(auto& edgeID : m_Faces[m_HighlightedFaceID].m_Edges){
                if(m_Edges[edgeID].m_GO != nullptr){
                    m_Edges[edgeID].m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::NOT_DONE]);
                }
            }
        }

        // set the new Highlighted face
        m_HighlightedFaceID = faceID;
        m_Faces[m_HighlightedFaceID].m_GO->SetColor(CUT_FACE_COLOR[ACIMState::CURRENT]);
        for(auto& edgeID : m_Faces[m_HighlightedFaceID].m_Edges){
            if(m_Edges[edgeID].m_GO != nullptr){
                m_Edges[edgeID].m_GO->SetColor(CUT_EDGE_COLOR[ACIMState::CURRENT]);
            }
        }
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

        if(auto cut = dynamic_cast<Cut*>(m_Components[id]))
        {
            if(cut -> IsSingleFace())
            // {
                AIAC_APP.GetLayer<LayerFeedback>()->EnableCutPlane(true);
            // } else {
            //     AIAC_APP.GetLayer<LayerFeedback>()->EnableCutPlane(false);
            // }
        }

        ShowAllComponents();
        HideAllComponentsExceptCurrent();
    }

    std::string TimberInfo::ShortenComponentID(std::string id) {
        if(id.find("Hole") != std::string::npos){
            return "H" + id.substr(5);
        } else if(id.find("Cut") != std::string::npos){
            return "C" + id.substr(4);
        }
        return id;
    }

    void TimberInfo::SetNextComponentAsCurrent()
    {
        auto ids = GetAllComponentsIDs();
        auto it = std::find(ids.begin(), ids.end(), m_CurrentComponentID);
        if(it == ids.end()){
            AIAC_ERROR("TimberInfo::SetNextComponentAsCurrent() : Current Component ID not found");
            return;
        }
        if(++it == ids.end()){
            it = ids.begin();
        }
        SetCurrentComponentTo(*it);
    }

    void TimberInfo::SetPrevComponentAsCurrent()
    {
        auto ids = GetAllComponentsIDs();
        auto it = std::find(ids.begin(), ids.end(), m_CurrentComponentID);
        if(it == ids.end()){
            AIAC_ERROR("TimberInfo::SetPrevComponentAsCurrent() : Current Component ID not found");
            return;
        }
        if(it == ids.begin()){
            it = ids.end();
        }
        SetCurrentComponentTo(*--it);
    }

    void TimberInfo::HideAllComponentsExceptCurrent() {
        for (const auto& [_, component] : m_Components) {
            if(component->m_ID != m_CurrentComponentID){
                component->SetVisibility(false);
                // if the component is a cut, we hide all the other cotas
                if(auto cut = dynamic_cast<Cut*>(component)){
                    cut->SetVisibilityAllCotas(false);
                }
            }
        }
        this->IsShowingAllComponents = false;
    }

    void TimberInfo::ShowAllComponents() {
        for (const auto& [_, component] : m_Components) {
            for(auto& go: component->m_GOPrimitives){
                component->SetVisibility(true);
            }
            // if the component is a cut, we show all the cotas
            if(auto cut = dynamic_cast<Cut*>(component)){
                if(IsShowingCotas)
                    cut->SetVisibilityAllCotas(true);
            }
        }
    }

    void TimberInfo::SetAllCotasVisibility(bool visible)
    {
        this->IsShowingCotas = visible;
        for (const auto& [_, component] : m_Components) {
            if(auto cut = dynamic_cast<Cut*>(component)){
                cut->SetVisibilityAllCotas(visible);
            }
        }
    }

    bool ACInfoModel::Load(std::string path) {
        // check if file is good
        if(path.empty()){
            AIAC_ERROR("ACInfoModel::Load() path is empty");
            return false;
        }
        if(!std::filesystem::exists(path)){
            AIAC_ERROR("ACInfoModel::Load() file does not exist");
            return false;
        }
        if (std::filesystem::is_directory(path)){
            AIAC_ERROR("ACInfoModel::Load() path is a directory");
            return false;
        }
        if (path.find(".acim") == std::string::npos){
            AIAC_ERROR("ACInfoModel::Load() file is not .acim");
            return false;
        }

        m_FilePath = path;
        
        Clear();
        
        pugi::xml_parse_result result = m_ACIMDoc.load_file(path.c_str());
        if (!result){
            AIAC_ERROR("Could not load ACInfoModel from file: {0}", path);
            return false;
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
                holeInfo.m_StartExposed = StringToBool(hole.child("start").child("exposed").child_value());
                holeInfo.m_End = StringToVec3(hole.child("end").child("coordinates").child_value()) * m_Scale;
                holeInfo.m_EndExposed = StringToBool(hole.child("end").child("exposed").child_value());
                holeInfo.m_Radius = std::stof(hole.child("radius").child_value());

                // build GOPrimitive
                holeInfo.m_AxisGO = GOLine::Add(holeInfo.m_Start, holeInfo.m_End, 2.0f);
                holeInfo.m_AxisGO->SetColor(HOLE_AXIS_COLOR[holeInfo.m_State]);
                holeInfo.m_CylinderGO = GOCylinder::Add(holeInfo.m_Start, holeInfo.m_End, holeInfo.m_Radius);
                holeInfo.m_CylinderGO->SetColor(HOLE_CYLINDER_COLOR[holeInfo.m_State]);
                holeInfo.m_StartPointGO = GOPoint::Add(holeInfo.m_Start, 2.0f);
                holeInfo.m_EndPointGO = GOPoint::Add(holeInfo.m_End, 2.0f);
                std::string shortenHoleID = m_TimberInfo.ShortenComponentID(holeInfo.m_ID);
                holeInfo.m_IDLabelGO = GOText::Add(shortenHoleID, holeInfo.m_End, m_LabelSize);

                holeInfo.m_GOPrimitives.push_back(holeInfo.m_AxisGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_CylinderGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_StartPointGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_EndPointGO);
                holeInfo.m_GOPrimitives.push_back(holeInfo.m_IDLabelGO);

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
                std::string shortenCutID = m_TimberInfo.ShortenComponentID(cutInfo.m_ID);
                cutInfo.m_IDLabelGO = GOText::Add(shortenCutID, cutInfo.m_Center, m_LabelSize);
                cutInfo.m_GOPrimitives.push_back(cutInfo.m_IDLabelGO);

                auto faces = cut.child("faces");
                for(auto face = faces.child("face"); face; face=face.next_sibling("face")){
                    TimberInfo::Cut::Face faceInfo;
                    faceInfo.m_ID = face.attribute("id").as_string();
                    faceInfo.m_Exposed = StringToBool(face.child("exposed").child_value());
                    faceInfo.m_State = StringToState(face.child("state").child_value());
                    faceInfo.m_Edges = StringToSet(face.child("edges").child_value());
                    faceInfo.m_Center = glm::vec3(0.0f);
                    if(!faceInfo.m_Exposed){
                        cutInfo.m_NonExposedEdgeIDs.insert(faceInfo.m_Edges.begin(), faceInfo.m_Edges.end());
                    }
                    auto corners = face.child("corners");
                    for(auto corner = corners.child("corner"); corner; corner=corner.next_sibling("corner")){
                        faceInfo.m_Corners.push_back(StringToVec3(corner.child_value()) * m_Scale);
                        faceInfo.m_Center += faceInfo.m_Corners.back();
                    }
                    faceInfo.m_Center /= faceInfo.m_Corners.size();

                    // build face GO
                    if(faceInfo.m_Corners.size()<3){
                        AIAC_ERROR("Face: {0} has less than 3 corners", faceInfo.m_ID);
                        continue;
                    }

                    // skip exposed faces
                    if(faceInfo.m_Exposed){
                        continue;
                    }

                    // build normal
                    faceInfo.m_Normal = glm::normalize(glm::cross(faceInfo.m_Corners[1] - faceInfo.m_Corners[0],
                                                                  faceInfo.m_Corners[2] - faceInfo.m_Corners[0]));

                    std::vector<uint32_t> indices;
                    auto baseCornerIdx = 0;
                    for(int i = 2; i < faceInfo.m_Corners.size(); i++){
                        indices.push_back(baseCornerIdx);
                        indices.push_back(i-1);
                        indices.push_back(i);
                    }
                    faceInfo.m_GO = GOMesh::Add(faceInfo.m_Corners, indices);
                    faceInfo.m_GO->SetColor(CUT_FACE_COLOR[cutInfo.m_State]);
                    // We only show non-exposed faces
                    if(faceInfo.m_Exposed){
                        faceInfo.m_GO->SetVisibility(false);
                    }
                    faceInfo.m_GOPrimitives.push_back(faceInfo.m_GO);

                    cutInfo.m_Faces[faceInfo.m_ID] = faceInfo;
                    if(!faceInfo.m_Exposed){
                        cutInfo.m_NonExposedFaceIDs.insert(faceInfo.m_ID);
                    }
                }

                auto edges = cut.child("edges");
                for(auto edge = edges.child("edge"); edge; edge=edge.next_sibling("edge")){
                    auto id = edge.attribute("id").as_string();

                    TimberInfo::Cut::Edge edgeInfo;
                    edgeInfo.m_ID = edge.attribute("id").as_string();
                    edgeInfo.m_Start = StringToVec3(edge.child("start").child_value()) * m_Scale;
                    edgeInfo.m_End = StringToVec3(edge.child("end").child_value()) * m_Scale;

                    // build GOPrimitive edges and cotas, only on non-exposed edges
                    if(cutInfo.m_NonExposedEdgeIDs.find(id) != cutInfo.m_NonExposedEdgeIDs.end()){
                        // GOLines for edges
                        edgeInfo.m_GO = GOLine::Add(edgeInfo.m_Start, edgeInfo.m_End, m_EdgeWeight);
                        edgeInfo.m_GO->SetColor(CUT_EDGE_COLOR[cutInfo.m_State]);
                        edgeInfo.m_GOPrimitives.push_back(edgeInfo.m_GO);

                        // ----------------------------------------------
                        // GOTexts for cotas
                        float scale_f = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 0.0f);
                        auto mid = (edgeInfo.m_Start + edgeInfo.m_End) / 2.0f;
                        
                        glm::vec3 cutCtr = cutInfo.m_Center;
                        float displacement = 0.02f * scale_f;
                        glm::vec3 vecMidCtr = glm::normalize(mid - cutCtr);
                        // random value between 0 and 1
                        auto midMoved = mid + (vecMidCtr * displacement);
                        auto lineCotas = GOLine::Add(GOPoint(mid), GOPoint(midMoved));
                        lineCotas->SetColor(GOColor::GREEN_PUNK_TRANSP07);
                        lineCotas->SetWeight(GOWeight::Default);
                        edgeInfo.m_CotaLines.push_back(lineCotas);

                        auto cotasPt = GOPoint::Add(mid);
                        cotasPt->SetColor(GOColor::GREEN_DARKER_TRANSP07);
                        cotasPt->SetWeight(GOWeight::MediumThick);
                        edgeInfo.m_CotaPts.push_back(cotasPt);
                        
                        float dist = glm::distance(edgeInfo.m_Start, edgeInfo.m_End);
                        float distmm = dist / scale_f * 1000;
                        int roundedDistmm = std::round(distmm);
                        auto cotas = GOText::Add(
                            std::to_string(roundedDistmm) + "mm",
                            midMoved,
                            GOTextSize::Small);
                        cotas->SetColor(GOColor::GREEN);
                        edgeInfo.m_Cotas.push_back(cotas);

                        if (this->m_TimberInfo.IsShowingCotas) {
                            lineCotas->SetVisibility(true);
                            cotasPt->SetVisibility(true);
                            cotas->SetVisibility(true);
                        } else {
                            lineCotas->SetVisibility(false);
                            cotasPt->SetVisibility(false);
                            cotas->SetVisibility(false);
                        }
                        
                        edgeInfo.m_GOPrimitives.push_back(lineCotas);
                        edgeInfo.m_GOPrimitives.push_back(cotasPt);
                        edgeInfo.m_GOPrimitives.push_back(cotas);
                    }
                    cutInfo.m_Edges[edgeInfo.m_ID] = edgeInfo;
                }

                // here we compute and add the neighbors
                // compare the edges for each face and understand which faces are neighbors
                for(auto& [faceID, face] : cutInfo.m_Faces){
                    for(auto& [edgeID, edge] : cutInfo.m_Edges){
                        if(face.m_Edges.find(edgeID) != face.m_Edges.end()){
                            for(auto& [otherFaceID, otherFace] : cutInfo.m_Faces){
                                if(faceID == otherFaceID) continue;
                                if(otherFace.m_Edges.find(edgeID) != otherFace.m_Edges.end()){
                                    face.m_Neighbors.insert(otherFaceID);
                                }
                            }
                        }
                    }
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
        m_TimberInfo.IsShowingAllComponents = true;

        return true;
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
            for(auto& primitive : cut.second.m_GOPrimitives)
                GOPrimitive::Remove(primitive);
            for(auto& face : cut.second.m_Faces){
                for(auto& primitive : face.second.m_GOPrimitives)
                    GOPrimitive::Remove(primitive);
            }
            for(auto& edge : cut.second.m_Edges){
                for(auto& primitive : edge.second.m_GOPrimitives)
                    GOPrimitive::Remove(primitive);
                edge.second.ClearCotas();
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
        auto vec = glm::normalize(bbox[1] - bbox[0]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[0] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[1] - vec, 2.0f));
        vec = glm::normalize(bbox[2] - bbox[1]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[1] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[2] - vec, 2.0f));
        vec = glm::normalize(bbox[3] - bbox[2]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[2] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[3] - vec, 2.0f));
        vec = glm::normalize(bbox[0] - bbox[3]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[3] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[0] - vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[1], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[2], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[3], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[0], 2.0f));

        // top
        vec = glm::normalize(bbox[5] - bbox[4]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[4] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[5] - vec, 2.0f));
        vec = glm::normalize(bbox[6] - bbox[5]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[5] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[6] - vec, 2.0f));
        vec = glm::normalize(bbox[7] - bbox[6]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[6] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[7] - vec, 2.0f));
        vec = glm::normalize(bbox[4] - bbox[7]);
        m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[7] + vec, 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[4] - vec, 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[4], bbox[5], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[5], bbox[6], 2.0f));
        // m_BboxGOLines.push_back(GOLine::Add(bbox[6], bbox[7], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[7], bbox[4], 2.0f));
        
        // side
        m_BboxGOLines.push_back(GOLine::Add(bbox[0], bbox[4], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[1], bbox[5], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[2], bbox[6], 2.0f));
        m_BboxGOLines.push_back(GOLine::Add(bbox[3], bbox[7], 2.0f));

        // color of the bounding box
        for(auto line : m_BboxGOLines)
            line->SetColor(GOColor::PURPLE);

        SetBboxVisibility(false);
    }

    void ACInfoModel::Transform(glm::mat4x4 transformMat) {
        // bounding box
        auto bbox = m_TimberInfo.m_Bbox;
        for(int i = 0 ; i < bbox.size() ; i++){
            m_TimberInfo.m_Bbox[i] = glm::vec3(transformMat * glm::vec4(bbox[i], 1.0f));
        }
        bbox = m_TimberInfo.m_Bbox;
        UpdateBboxGOLine();

        // holes
        for(auto& kv : m_TimberInfo.m_Holes){
            auto& holeInfo = kv.second;
            for(auto& objs : holeInfo.m_GOPrimitives){
                objs->Transform(transformMat);
            }
        }

        // cuts
        for(auto& kv : m_TimberInfo.m_Cuts){
            auto& cutInfo = kv.second;
            for(auto& objs : cutInfo.m_GOPrimitives){
                objs->Transform(transformMat);
            }

            // Face
            for(auto& kv : cutInfo.m_Faces){
                auto& faceInfo = kv.second;
                for(auto& objs : faceInfo.m_GOPrimitives){
                    objs->Transform(transformMat);
                }
                // FIXME: Add GOVec so we can use GO to manage everything.
                // Normal, Center, and Corners are glm::vec3
                for(auto& corner : faceInfo.m_Corners){
                    corner = glm::vec3(transformMat * glm::vec4(corner, 1.0f));
                }
                faceInfo.m_Center = glm::vec3(transformMat * glm::vec4(faceInfo.m_Center, 1.0f));
                faceInfo.m_Normal = glm::normalize(glm::cross(faceInfo.m_Corners[1] - faceInfo.m_Corners[0],
                                                              faceInfo.m_Corners[2] - faceInfo.m_Corners[0]));
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

    void ACInfoModel::SetBboxVisibility(bool visible){
        for(auto line : m_BboxGOLines){
            line->SetVisibility(visible);
        }
    }

    ACIMState StringToState(std::string state){
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
            AIAC_ERROR("Invalid state string: \"{0}\"", state);
            return ACIMState::NOT_DONE;
        }
    }

    glm::vec3 StringToVec3(std::string str){
        glm::vec3 vec;
        auto ss = stringstream(str);
        ss >> vec.x >> vec.y >> vec.z;
        return vec;
    }

    std::vector<std::string> StringToTokens(std::string str){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, ' ')){
            tokens.push_back(token);
        }
        return tokens;
    }

    std::set<std::string> StringToSet(std::string str){
        std::set<std::string> set;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, ' ')){
            set.insert(token);
        }
        return set;
    }

    bool StringToBool(std::string str){
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

    std::string Vec3ToString(glm::vec3 vec){
        std::stringstream ss;
        ss << vec.x << " " << vec.y << " " << vec.z;
        return ss.str();
    }


} // namespace AIAC

