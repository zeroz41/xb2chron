#ifndef CLASSES_GF_GFCOMPROPERTYPC_H
#define CLASSES_GF_GFCOMPROPERTYPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComProperty.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B69448
class GfComPropertyPc : public ::gf::GfComProperty {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPropertyPc();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
