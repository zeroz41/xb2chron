#ifndef CLASSES_SSD_SOUNDBANK_H
#define CLASSES_SSD_SOUNDBANK_H

#include "classes/ssd/Array.h"
#include "classes/ssd/List.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/ssd/TextFixed.h"
#include "ssd/Debug.h"

namespace ssd { class SoundGroup; }

namespace ssd {
// table 0x7100B81AA0: a named set of sound entries and the groups they belong to. Init gives it its id and name
// and adds it to the SystemCore (which links it through the Node base at 0x18), Quit removes it. sizeof 0x120
// (fw::SoundSsdBank's fields after it start at 0x130). The field names are not the original's.
class SoundBank : public Object, public List<SoundBank>::Node {
public:
    SoundBank();
    virtual ~SoundBank();  // slot 0

    Result Init(int id, const TextRef& name);
    // -1 without a library instance, -14 before Init, -120 while a source is in use, -122 while it holds entries
    Result Quit();
    // the sum of the entries' sources' reference counts
    int GetReferenceCounter() const;
    int NumSoundEntry() const;
    // the entry, or null without a library instance or before Init
    SoundEntry* AddSoundEntry(SoundEntry* entry);
    Result RemoveSoundEntry(SoundEntry* entry);
    Result AddSoundGroup(SoundGroup* group);
    Result Stop(float fadeTime);

    int id_;  // 0x30: -1 until Init
    TextFixed<64> name_;  // 0x38
    List<SoundEntry> entries_;  // 0xE0
    Array<SoundGroup*> groups_;  // 0x108
};
}  // namespace ssd

#endif
