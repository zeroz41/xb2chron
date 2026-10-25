#ifndef CLASSES_FW_COLIOBJUSERDATA_H
#define CLASSES_FW_COLIOBJUSERDATA_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ColiUserData.h"
namespace fw {
// table 0x7100B411C0
class ColiObjUserData : public ColiUserData {
public:
    ColiObjUserData() : m_handle(0) {}
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    static mm::mtl::RTTI m_rtti;

    unsigned int m_handle;  // fw::ColiObject::setHandle's
};
}  // namespace fw

#endif
