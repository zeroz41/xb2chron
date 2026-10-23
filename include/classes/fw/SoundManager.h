#ifndef CLASSES_FW_SOUNDMANAGER_H
#define CLASSES_FW_SOUNDMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }
namespace fw { class SoundPack; }
namespace fw { enum SoundCategory : int; }
namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// a base of fw::SoundManager no evidence names yet
class TUnk_B42E00 {
public:
    virtual ~TUnk_B42E00();
};
// table 0x7100B42DA0; base at 0x10 unknown (TUnk_B42E00)
class SoundManager : public ::fw::ManagerObject, public TUnk_B42E00 {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in SoundManager's unit and
    // GfManager::fn_710032A1FC calls it on PtrSingleton<fw::SoundManager>'s instance. What it does: stores its bool at 0x44C8
    void fn_71001A0EF8(bool flag);
    virtual ~SoundManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void tail(fw::UpdateInfo const&);  // slot 9

    // the registered pack of a name and allocator, or null
    SoundPack* findPack(const char* name, mm::mtl::IAllocator* allocator);
    void registPack(SoundPack* pack);
    // plays sound id of pack in category, at volume: the sound's handle, 0 when nothing plays
    unsigned int playSe(unsigned int id, SoundPack* pack, float volume, SoundCategory category);
    // stops the sound of handle, fading over fade (the driver's stopSe)
    void stopSe(unsigned int handle, float fade);
    void removePack(SoundPack* pack);
};
}  // namespace fw

#endif
