#ifndef CLASSES_SSD_SOUNDGROUP_H
#define CLASSES_SSD_SOUNDGROUP_H

#include "classes/ssd/Object.h"

namespace ssd {
// table 0x7100B43128: a group sounds belong to (SoundBank::AddSoundGroup collects them; SoundEntry::GetSoundGroup
// finds an entry's by id). An Object (the SystemCore constructor builds its group at 0x480 with type 4); the field
// name is not the original's
class SoundGroup : public Object {
public:
    virtual ~SoundGroup();  // slot 0

    int id_;  // 0x18: compared with SoundParam::groupId_
};
}  // namespace ssd

#endif
