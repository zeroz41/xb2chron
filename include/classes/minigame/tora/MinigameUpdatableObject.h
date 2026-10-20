#ifndef CLASSES_MINIGAME_TORA_MINIGAMEUPDATABLEOBJECT_H
#define CLASSES_MINIGAME_TORA_MINIGAMEUPDATABLEOBJECT_H

#include "classes/fw/UpdatableObject.h"

namespace fw { class UpdateInfo; }

namespace minigame { namespace tora {
// table 0x7100B72040
class MinigameUpdatableObject : public ::fw::UpdatableObject {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~MinigameUpdatableObject();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}}  // namespace minigame::tora

#endif
