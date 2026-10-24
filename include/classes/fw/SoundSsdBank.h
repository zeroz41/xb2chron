#ifndef CLASSES_FW_SOUNDSSDBANK_H
#define CLASSES_FW_SOUNDSSDBANK_H

#include "classes/fw/SoundReferenceObject.h"
#include "classes/ssd/SoundBank.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { enum SoundCategory : int; }
namespace fw { enum SoundPriority : int; }
namespace fw { class SoundSsdSource; }

namespace fw {
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

    virtual ~SoundSsdBank();  // slot 0

    static SoundSsdBank* create(const char* name, SoundCategory category, unsigned int maxSound);
    void setMaxSound(int maxSound);
    void stopAll();
    mm::mtl::IntrusivePtr<SoundSsdSource> addWave(const WaveInfo& info);

    ssd::SoundBank m_bank;  // 0x10 (stopAll stops it; the name is not the original's)
};
}  // namespace fw

#endif
