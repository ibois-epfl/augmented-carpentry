#include "aiacpch.h"

#include "ACInfoModel.h"

using namespace std;

//FIXME:: do we still need this class?
namespace AIAC
{
    void AIAC::ACInfoModel::Load(std::string path) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(path.c_str());
        if (!result){
            AIAC_ERROR("Could not load ACInfoModel from file: {0}", path);
            return;
        }
//        cout << doc.child("acim").child("timber").attribute("id").as_string() << endl;

    }
} // namespace AIAC

