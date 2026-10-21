#ifndef CLASSES_FW_COLIOBJUSERDATA_H
#define CLASSES_FW_COLIOBJUSERDATA_H

#include "mm/mtl/RTTI.h"
namespace fw {
// table 0x7100B411C0
class ColiObjUserData {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
