#ifndef CLASSES_GF_GFOBJ_H
#define CLASSES_GF_GFOBJ_H

#include "classes/fw/UpdatableObject.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::GfObj no evidence names yet
class TUnk_B69E50 {
public:
    virtual void getRTTI() const = 0;
    virtual ~TUnk_B69E50();
    virtual void recieveMessage(fw::MessageObject*, fw::Message&) = 0;
};
// table 0x7100B69E08; base at 0xE0 unknown (TUnk_B69E50)
class GfObj : public ::fw::UpdatableObject, public TUnk_B69E50 {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObj();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 4
    virtual void onEvent(fw::ObjectEvent const&);  // slot 5
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 6
};
}  // namespace gf

#endif
