#ifndef CLASSES_GF_GFEVTMODELSALVAGE_H
#define CLASSES_GF_GFEVTMODELSALVAGE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfEvtModelDriver.h"

namespace gf {
// table 0x7100B53D28
class GfEvtModelSalvage : public ::gf::GfEvtModelDriver {
public:
    // a driver model whose table is the salvage's (inline: create's code)
    explicit GfEvtModelSalvage(GfInitParamDriver& param) : GfEvtModelDriver(param) {}
    // a new salvage model, its first reference taken
    static GfEvtModelSalvage* create(GfInitParamDriver& param);
    // warps the object to pos, turned rotY degrees about y, when it is valid
    void setTransform(const mm::Vec3& pos, float rotY);
    virtual ~GfEvtModelSalvage() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    // whether its object is a valid game object
    bool isValid() const;
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
