#ifndef CLASSES_FW_ANIMAFTERMODIFIERINTERFACE_H
#define CLASSES_FW_ANIMAFTERMODIFIERINTERFACE_H

#include "mm/mtl/IntrusiveList.h"

namespace fw {
// table none (its derived classes'): what the AnimationManager applies to a layer's poses after sampling them
// (AnimColPoseModifier is one: its table's slots past the destructors). Its links in a group's list follow its table
// (AnimationManager::addAfterModifier; self-linked by AnimColPoseModifier's constructor).
class AnimAfterModifierInterface : public mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~AnimAfterModifierInterface() {}  // slot 0
    virtual void apply() = 0;  // slot 2
};
}  // namespace fw

#endif
