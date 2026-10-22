#ifndef CLASSES_GF_GFCOMPROPERTY_H
#define CLASSES_GF_GFCOMPROPERTY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfStatusProperty.h"
#include "gf/GfDebugStatusProperty.h"  // the tree: "gf/GfDebugStatusProperty.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/UniquePtr.h"
namespace gf { class GfTargetProperty; }  // gf/GfTargetProperty.h
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B69C30
class GfComProperty : public ::gf::GfComponent {
public:
    GfComProperty();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComProperty();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int) {}  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;
    // fields: its constructor zeroes 0x10-0x38, its destructor releases and deletes them last to first
    mm::mtl::IntrusivePtr<gf::GfStatusProperty> m_status;  // the object's hit points (none: it takes no damage)
    // what those targeting or following the object read (the PC's flush fills it; the name is not the original's)
    mm::mtl::UniquePtr<gf::GfTargetProperty> m_target;
    unsigned char pad_20[0x10];  // two more UniquePtrs
    mm::mtl::UniquePtr<gf::GfDebugStatusProperty> m_debugStatus;  // debug switches (procMsgObjectDamage's)
};
}  // namespace gf

#endif
