#ifndef CLASSES_SSD_SOUNDCATEGORY_H
#define CLASSES_SSD_SOUNDCATEGORY_H

namespace ssd {
// table 0x7100B43330
class SoundCategory {
public:
    // no id, full volume (fw::SoundSsdDriver's category entries: the stores stay apart from the vtable's)
    SoundCategory() : id_(0), volume_(1.0f) {}
    virtual ~SoundCategory() {}  // slot 0

    // what ssd::SoundCore::SetCategory copies (the names are not the original's)
    int id_;  // 0x08 (0: unused)
    float volume_;  // 0x0C
};
}  // namespace ssd

#endif
