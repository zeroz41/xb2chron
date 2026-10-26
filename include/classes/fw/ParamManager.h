#ifndef CLASSES_FW_PARAMMANAGER_H
#define CLASSES_FW_PARAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Map.h"
#include "classes/mm/mtl/ReferenceObject.h"

namespace fw { class ParamList; }
namespace fw { class Reflection; }
namespace fw { class ParamManager; }

namespace fw {
// table 0x7100B41898
class ParamManager : public ::mm::mtl::PtrSingleton< ::fw::ParamManager> {
public:
    // what the managers' maps hold per reflection and per parameter list: each starts with a counted reference
    // (the trees' free_node releases it); the referenced types are not known yet
    struct RefInfo {
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_object;  // the name is not the original's
        unsigned char pad_8[0x88];  // 0x90 bytes: createManager stores the tree sentinel's color at its node's 0xB0
    };
    struct ParamInfo {
        mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_object;  // the name is not the original's
        unsigned char pad_8[0x88];  // 0x90 bytes: createManager stores the tree sentinel's color at its node's 0xB0
    };
    virtual ~ParamManager();  // slot 0
    // 128 more references its destructor releases (their type is not known yet; the name is not the original's)
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_references[128];
    mm::mtl::IntrusivePtr<ParamList> m_paramLists[128];  // ParamBuilder::create(binary, index, name) sets index's
    mm::mtl::Map<const Reflection*, RefInfo> m_refInfos;      // the name is not the original's
    mm::mtl::Map<const ParamList*, ParamInfo> m_paramInfos;   // the name is not the original's
};
}  // namespace fw

#endif
