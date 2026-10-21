#ifndef CLASSES_FW_PARAMMANAGER_H
#define CLASSES_FW_PARAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ParamList; }
namespace fw { class ParamManager; }

namespace fw {
// table 0x7100B41898
class ParamManager : public ::mm::mtl::PtrSingleton< ::fw::ParamManager> {
public:
    virtual ~ParamManager();  // slot 0
    unsigned char pad_8[0x400];  // 128 more references its destructor releases
    mm::mtl::IntrusivePtr<ParamList> m_paramLists[128];  // ParamBuilder::create(binary, index, name) sets index's
};
}  // namespace fw

#endif
