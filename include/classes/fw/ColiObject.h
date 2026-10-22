#ifndef CLASSES_FW_COLIOBJECT_H
#define CLASSES_FW_COLIOBJECT_H

#include "mm/mtl/RTTI.h"
namespace mm { class Vec3; }

namespace fw {
// a collision attribute (idcoli::IDColiParmsBase::isAttr tests it); no value has a name yet
enum ColiAtrr {};
}  // namespace fw

namespace fw {
// table 0x7100B41180
class ColiObject {
public:
    virtual ~ColiObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update();  // slot 3
    virtual void postUpdate();  // slot 4
    virtual void setDir(mm::Vec3 const&) {}  // slot 5
    bool testAttribute(fw::ColiAtrr attribute) const;
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
