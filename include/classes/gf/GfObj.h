#ifndef CLASSES_GF_GFOBJ_H
#define CLASSES_GF_GFOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/MessageObject.h"
#include "classes/fw/UpdatableObject.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B69E08; its fw::MessageObject at 0xE0 (that table: getRTTI, the destructors, recieveMessage)
class GfObj : public ::fw::UpdatableObject, public ::fw::MessageObject {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObj();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 4
    virtual void onEvent(fw::ObjectEvent const&);  // slot 5
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 6
    static mm::mtl::RTTI m_rtti;
    GF_OBJ_HANDLE* m_handle;  // its handle: GfObjAcc(GfObj*) looks the object's info up by it
};
}  // namespace gf

#endif
