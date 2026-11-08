#ifndef CLASSES_FW_SOUNDSSDBANK_H
#define CLASSES_FW_SOUNDSSDBANK_H

#include "classes/fw/SoundReferenceObject.h"
#include "classes/ssd/SoundBank.h"
#include "classes/ssd/SoundGroup.h"
#include "classes/mm/mtl/List.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixStr.h"

namespace fw { enum SoundCategory : int; }
namespace fw { enum SoundPriority : int; }
namespace fw { class SoundSsdSource; }

namespace fw {
// what fw::SoundSsdBank's constructor builds a bank from (create fills it: allocator 5, the next unique id, the
// name; the names but the type's are not the original's)
struct SoundBankSetup {
    mm::mtl::IAllocator* allocator;
    unsigned int id;  // 0x08
    const char* name;  // 0x10
    unsigned int pad_18;
    unsigned int maxSound;  // 0x1C: the most sounds the group plays; the sources list reserves at least 256
};

// table 0x7100B42ED0
class SoundSsdBank : public ::fw::SoundReferenceObject {
public:
    // a wave addWave makes a source of: SoundPack::registSource fills one per entry of its pack's binary (the
    // field names are not the original's; the pads are the entry's words it copies unread here)
    // four words a pack binary's entry carries and WaveInfo copies whole (the names are not the original's; the
    // float is pad_8: SoundPack::registSource tests it above 0.00001)
    struct WaveParam {
        unsigned int pad_0;
        unsigned int pad_4;
        float pad_8;
        unsigned int pad_c;
    };

    struct WaveInfo {
        const char* packName;
        const char* name;
        const void* data;
        unsigned int size;
        SoundCategory category;
        int priority;
        bool pad_24;  // whether param's float is above 0.00001
        WaveParam param;
        unsigned int pad_38[3];
        unsigned short pad_44;
    };

    SoundSsdBank(const SoundBankSetup& setup);
    virtual ~SoundSsdBank();  // slot 0

    static SoundSsdBank* create(const char* name, SoundCategory category, unsigned int maxSound);
    void setMaxSound(int maxSound);
    void destroy();
    void stopAll();
    void update();
    mm::mtl::IntrusivePtr<SoundSsdSource> addWave(const WaveInfo& info);
    mm::mtl::IntrusivePtr<SoundSsdSource> addStream(const char* name, SoundCategory category, SoundPriority priority);

    ssd::SoundBank m_bank;  // 0x10 (stopAll stops it; the name is not the original's)
    // 0x130: the bank's one sound group (the constructor builds it, SoundBank::AddSoundGroup adds it; the name is
    // not the original's)
    ssd::SoundGroup m_group;
    unsigned int pad_150;  // the setup's word at 0x18
    // the bank's name and its mm::mtl::hashStrCrc (fw::SoundSsdDriver::findBank compares both; the names are not
    // the original's)
    mm::mtl::FixStr<256> m_name;  // 0x154
    unsigned int m_nameHash;  // 0x258
    // the setup's id (the constructor hands it to SoundBank::Init and the group) and the most sounds the bank
    // plays (setMaxSound; the names are not the original's)
    int m_id;  // 0x25C
    int m_maxSound;  // 0x260
    unsigned int pad_264;
    mm::mtl::IAllocator* m_allocator;  // 0x268: the setup's allocator, the sources list's
    mm::mtl::List<SoundSsdSource*> m_sources;  // 0x270 (the name is not the original's)
};
}  // namespace fw

#endif
