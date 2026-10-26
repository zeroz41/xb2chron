#ifndef CLASSES_SSD_SOUNDGROUP_H
#define CLASSES_SSD_SOUNDGROUP_H

#include "classes/ssd/Object.h"

namespace ssd {
// table 0x7100B43128: a group sounds belong to (SoundBank::AddSoundGroup collects them; SoundEntry::GetSoundGroup
// finds an entry's by id). An Object (the SystemCore constructor builds its group at 0x480 with type 4); the field
// name is not the original's
class SoundGroup : public Object {
public:
    // id 0, at most 256 sounds (fw::SoundSsdBank's constructor)
    SoundGroup() : Object(ObjectType::Id(4)), id_(0), maxSound_(256) {}
    // inline: the table lives in fw::SoundSsdBank's unit, whose constructor builds one; its D2 slot holds
    // Object's destructor
    virtual ~SoundGroup() {}  // slot 0

    int id_;  // 0x18: compared with SoundParam::groupId_
    // 0x1C: the most sounds of the group (fw::SoundSsdBank::setMaxSound sets it with the bank's own count; the
    // constructor's default is 256; the name is not the original's)
    int maxSound_;
};
}  // namespace ssd

#endif
