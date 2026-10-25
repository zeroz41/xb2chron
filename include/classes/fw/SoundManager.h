#ifndef CLASSES_FW_SOUNDMANAGER_H
#define CLASSES_FW_SOUNDMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/fw/ISoundDriver.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/mm/mtl/List.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/SoundResource.h"
#include "classes/fw/SoundResSourceManager.h"
#include "classes/fw/SoundReferenceObject.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace mm { class Mat44; }
namespace fw { class SoundPack; }
namespace fw { enum SoundCategory : int; }
namespace fw { enum SoundVolumeType : int; }
namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// table 0x7100B42DA0; the base at 0x10 is mm::mtl::PtrSingleton<fw::SoundManager> (the constructor installs its
// table 0x7100B42E40 and asserts singleton.h's `get()==0`)
class SoundManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::SoundManager> {
public:
    SoundManager(mm::mtl::IAllocator* allocator);
    virtual ~SoundManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void tail(fw::UpdateInfo const&);  // slot 9

    void attachPoolMemory(void* memory, unsigned int size);
    bool loadBattleSe();
    void pauseAll(bool pause, float fade);
    static mm::mtl::IAllocator* getProcAllocator();
    // a new handle: the next of m_uniqueID's serial numbers, category in the top byte
    static unsigned int getUniqueID(SoundCategory category);
    void setListeningPoint(const mm::Mat44& mtx);
    void setCategoryVolume(SoundCategory category, float volume, float fade);
    void setCategoryPitch(SoundCategory category, float pitch, float fade);
    unsigned int playBgm(const char* name, float volume, bool flag, int param, SoundCategory category);
    bool startBgm(unsigned int handle);
    void stopBgm(unsigned int handle, float fade);  // GfMenuObjUtil::stopBGM's, for a nonzero handle
    unsigned int playVoice(const char* name, float volume, bool flag, SoundCategory category);
    bool startVoice(unsigned int handle);
    void stopVoice(unsigned int handle, float fade);
    SoundPack* getCommonPack();
    // the registered pack of a name and allocator, or null
    SoundPack* findPack(const char* name, mm::mtl::IAllocator* allocator);
    // plays the sound of that name (GfMenuObjUtil::playSE passes category 3)
    unsigned int playSe(const char* name, SoundPack* pack, float volume, SoundCategory category);
    // plays sound id of pack in category, at volume: the sound's handle, 0 when nothing plays
    unsigned int playSe(unsigned int id, SoundPack* pack, float volume, SoundCategory category);
    // stops the sound of handle, fading over fade (the driver's stopSe)
    void stopSe(unsigned int handle, float fade);
    // whether handle's sound still plays (GfComSound::flush drops its cache entry otherwise)
    bool isValid(unsigned int handle) const;
    bool isPlaying(unsigned int handle) const;
    bool isPause(unsigned int handle) const;
    bool isPreparing(unsigned int handle) const;
    bool isPrepared(unsigned int handle) const;
    void setCategory(unsigned int handle, SoundCategory category);
    void setVolume(unsigned int handle, float volume, float fade);
    float getVolume(unsigned int handle, SoundVolumeType type);
    void setPitch(unsigned int handle, float pitch, float fade);
    void setPan(unsigned int handle, float pan, float fade);
    void setPos(unsigned int handle, const mm::Vec3& pos);
    bool setPlayTime(unsigned int handle, float time);
    bool getPlayTime(unsigned int handle, float& time);
    bool getTotalTime(unsigned int handle, float& time);
    bool isLoop(unsigned int handle);
    bool isLoop(unsigned int handle, SoundPack* pack);
    void pause(unsigned int handle, bool pause, float fade);
    void stopBgmAll();
    void stopSeAll();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in SoundManager's unit and
    // GfManager::fn_710032A1FC calls it on PtrSingleton<fw::SoundManager>'s instance. What it does: stores its bool at 0x44C8
    void fn_71001A0EF8(bool flag);
    void registPack(SoundPack* pack);
    void removePack(SoundPack* pack);
    bool isCommonLoaded() const;
    bool isBattleLoaded() const;
    void detachPoolMemory(void* memory, unsigned int size);

    // whether the manager's driver plays anything: the singleton exists, the driver is made and its device enabled
    // (every driver forwarder tests these three; the name is not the original's)
    bool isDriverEnable() const {
        return mm::mtl::PtrSingleton<SoundManager>::get() != nullptr && m_driver != nullptr && m_deviceEnable;
    }

    // serial number, first and last of the handles getUniqueID hands out (1.0.0 names the object; its fields'
    // names are not the original's)
    struct UniqueID {
        unsigned int current;
        unsigned int min;
        unsigned int max;
    };
    static UniqueID m_uniqueID;

    // a volume that moves from start to target over time seconds (update steps it; the names are not the
    // original's)
    struct Fade {
        Fade() : current(1.0f), target(1.0f), start(1.0f), time(0.0f), timer(0.0f) {}
        void update(float delta) {
            timer += delta;
            if (timer >= time) {
                timer = time;
                current = target;
            } else {
                current = start + (timer / time) * (target - start);
            }
        }
        float current;
        float target;
        float start;
        float time;
        float timer;
    };

    // the names are not the original's
    ISoundDriver* m_driver;  // initialize makes a SoundSsdDriver
    // what finalize releases (SoundReferenceObject::release per element)
    mm::mtl::FixedVector<SoundReferenceObject*, 8> m_references;
    unsigned int pad_68;
    Fade m_volume;  // 0x6C: update hands m_volume * m_volume2 to the driver's setMasterVolume
    Fade m_volume2;  // 0x80
    int m_pauseCount;  // pauseAll's nesting count: the driver pauses at the first, resumes at the last
    bool m_deviceEnable;  // the driver's isDeviceEnable after initialize
    unsigned char pad_99[0x7];
    mm::mtl::List<SoundPack*> m_packs;  // 0xA0
    // the sound resources initialize and loadBattleSe request (the names are not the original's: from their files)
    SoundResource* m_commonSe;  // 0xE0: "/sound/se/common.xsp" (dlc_common.xsp when m_dlc)
    SoundResource* m_battleSystemSe;  // "/sound/se/se_btl_system.xsp"
    SoundResource* m_battleElemSe;  // "/sound/se/se_btl_elem.xsp"
    SoundResource* m_battleWeaponSe;  // "/sound/se/se_btl_weapon.xsp"
    // the driver's updateDebugInfo takes vectors of these sizes (an inference from the layout: 128 0x80-byte entries
    // end at 0x4100, 18 0x30-byte ones at 0x4470)
    mm::mtl::FixedVector<SoundHandleDebugInfo, 128> m_handleDebugInfo;  // 0x100
    unsigned char pad_4108[0x8];
    mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> m_categoryDebugInfo;  // 0x4110
    SoundResSourceManager m_resSourceManager;  // 0x4478
    bool m_dlc;  // 0x44C8: getCommonPack finds "dlc_common" instead of "common" when set
    unsigned char pad_44c9[0x7];
};
}  // namespace fw

#endif
