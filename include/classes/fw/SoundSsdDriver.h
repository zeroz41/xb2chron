#ifndef CLASSES_FW_SOUNDSSDDRIVER_H
#define CLASSES_FW_SOUNDSSDDRIVER_H

#include "classes/fw/ISoundDriver.h"
#include "classes/fw/PointerMap.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/List.h"
#include "classes/fw/SoundSsdBank.h"
#include "mm/mtl/Hash.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/SoundCategory.h"
#include "mm/mtl/FixStr.h"
#include "mm/Mat44.h"
#include "ml/CriticalSection.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/Map.h"
#include "mm/mtl/ObjectAllocator.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundHandle/Notify.h"

namespace fw { enum SoundCategory : int; }
namespace fw { class SoundCategoryDebugInfo; }
namespace fw { class SoundHandleDebugInfo; }
namespace fw { enum SoundOutputType : int; }
namespace fw { class SoundPack; }
namespace fw { class SoundPlayInfo; }
namespace fw { class SoundResult; }
// what getVolume reads (0: the handle's volume, 1: its distance volume, 2: a third volume; the names are not known)
namespace fw { enum SoundVolumeType : int; }
namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace fw {
// the kinds stopSoundAll stops (stopBgmAll passes 1, stopVoiceAll 2, stopSeAll 3; the names are not known)
enum SoundType : int;
enum SoundPriority : int;
class SoundSsdPlayer;
class SoundPoolMemory;
}  // namespace fw
namespace ssd { class SoundCore; class SoundHandle; class SoundListener; }
namespace csvb { class CCsvbData; }
namespace fw {
// table 0x7100B42EF0; the base at 0x8 is mm::mtl::PtrSingleton<SoundSsdDriver> (the constructor stores its
// table there and asserts get()==0 from singleton.h)
class SoundSsdDriver : public ::fw::ISoundDriver, public ::mm::mtl::PtrSingleton<SoundSsdDriver> {
public:
    // ssd's allocator over the IAllocator the driver is constructed with (its table: ssd::Allocator's slots)
    class SoundAllocator : public ::ssd::Allocator {
    public:
        explicit SoundAllocator(mm::mtl::IAllocator* allocator) : m_allocator(allocator) {}
        virtual void* AllocInstance(unsigned long size);  // slot 2
        virtual void FreeInstance(void* address);  // slot 3
        virtual void* AllocBuffer(unsigned long size, unsigned long alignment);  // slot 4
        virtual void FreeBuffer(void* address);  // slot 5
        virtual void* AllocStream(unsigned long size, unsigned long alignment);  // slot 6
        virtual void FreeStream(void* address);  // slot 7

        mm::mtl::IAllocator* m_allocator;  // 0x08 (the name is not the original's)
    };
    virtual ~SoundSsdDriver();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void finalize();  // slot 3
    virtual void updateDebugInfo(mm::mtl::FixedVector<fw::SoundHandleDebugInfo, 128ul>&, mm::mtl::FixedVector<fw::SoundCategoryDebugInfo, 18ul>&);  // slot 4
    virtual void setListeningPoint(mm::Mat44 const&);  // slot 5
    virtual const mm::Mat44& getListeningPoint() const;  // slot 6
    virtual void setMasterVolume(float);  // slot 7
    virtual void setCategoryVolume(fw::SoundCategory, float, float);  // slot 8
    virtual float getCategoryVolume(fw::SoundCategory) const;  // slot 9
    virtual void setCategoryMute(fw::SoundCategory, bool, float);  // slot 10
    virtual void setCategoryPitch(fw::SoundCategory, float, float);  // slot 11
    virtual void setOutputMode(fw::SoundOutputType);  // slot 12
    virtual void addCategory(fw::SoundCategory, float, char const*);  // slot 13
    virtual void removeCategory(fw::SoundCategory);  // slot 14
    virtual void pauseCategory(fw::SoundCategory, bool, float);  // slot 15
    virtual bool isDeviceEnable() const;  // slot 16
    virtual unsigned int playBgm(char const*, float, bool, int, fw::SoundCategory);  // slot 17
    virtual bool startBgm(unsigned int);  // slot 18
    virtual bool stopBgm(unsigned int, float);  // slot 19
    virtual void stopBgmAll();  // slot 20
    virtual unsigned int playVoice(char const*, float, bool, fw::SoundCategory);  // slot 21
    virtual bool startVoice(unsigned int);  // slot 22
    virtual bool stopVoice(unsigned int, float);  // slot 23
    virtual unsigned int playSe(char const*, fw::SoundPack*, float, fw::SoundCategory);  // slot 24
    virtual unsigned int playSe(unsigned int, fw::SoundPack*, float, fw::SoundCategory);  // slot 25
    virtual void playSeEx(fw::SoundPlayInfo const&, fw::SoundResult&);  // slot 26
    virtual bool stopSe(unsigned int, float);  // slot 27
    virtual bool isValid(unsigned int) const;  // slot 28
    virtual bool isPlaying(unsigned int) const;  // slot 29
    virtual bool isPreparing(unsigned int) const;  // slot 30
    virtual bool isReady(unsigned int) const;  // slot 31
    virtual bool isLoop(unsigned int);  // slot 32
    virtual bool isLoop(unsigned int, fw::SoundPack*);  // slot 33
    virtual bool isPause(unsigned int) const;  // slot 34
    virtual void setCategory(unsigned int, fw::SoundCategory);  // slot 35
    virtual fw::SoundCategory getCategory(unsigned int);  // slot 36
    virtual void setVolume(unsigned int, float, float);  // slot 37
    virtual float getVolume(unsigned int, fw::SoundVolumeType);  // slot 38
    virtual void setPitch(unsigned int, float, float);  // slot 39
    virtual void setPan(unsigned int, float, float);  // slot 40
    virtual void setPos(unsigned int, mm::Vec3 const&);  // slot 41
    virtual bool setPlayTime(unsigned int, float);  // slot 42
    virtual bool getPlayTime(unsigned int, float&);  // slot 43
    virtual bool getTotalTime(unsigned int, float&);  // slot 44
    virtual bool setRemainLoopCount(unsigned int, int);  // slot 45
    virtual bool getRemainLoopCount(unsigned int, int&);  // slot 46
    virtual void pause(unsigned int, bool, float);  // slot 47
    virtual void stopAll();  // slot 48
    virtual void stopVoiceAll();  // slot 49
    virtual void stopSeAll();  // slot 50
    virtual void pauseAll(bool, float);  // slot 51
    virtual bool findSe(char const*) const;  // slot 52
    virtual void attachPoolMemory(void*, unsigned int);  // slot 53
    virtual void detachPoolMemory(void*, unsigned int);  // slot 54

    // one category's state: the ssd::SoundCategory handed to ssd::SoundCore::SetCategory and the factors its
    // volume is the product of (the names are not the original's; 1.0.0 has no symbol for the type)
    struct CategoryInfo {
        // a value moving from start to target over time seconds
        struct Fade {
            // starts a move to value over time (at once when time is not positive)
            void set(float value, float time) {
                if (time > 0.0f) {
                    start = current;
                } else {
                    time = 0.0f;
                    current = value;
                    start = value;
                }
                target = value;
                this->time = time;
                elapsed = 0.0f;
            }
            float current;  // 0x00
            float target;  // 0x04
            float start;  // 0x08
            float time;  // 0x0C
            float elapsed;  // 0x10
        };
        void applyVolume() { category.volume_ = masterVolume * baseVolume * volume.current * mute.current; }

        ssd::SoundCategory category;  // 0x00
        float baseVolume;  // 0x10 (addCategory's volume)
        Fade volume;  // 0x14 (setCategoryVolume; getCategoryVolume returns its current value)
        Fade mute;  // 0x28 (setCategoryMute: 0 while muted, 1 otherwise)
        float masterVolume;  // 0x3C (setMasterVolume)
        int muteCount;  // 0x40
        float pitch;  // 0x44 (setCategoryPitch; 1 from addCategory)
        int active;  // 0x48 (1 from addCategory, 0 from removeCategory)
        mm::mtl::FixStr<16> name;  // 0x4C
        unsigned char pad_60[0x8];
    };

    bool isValid() const { return m_core != nullptr; }
    // the entry of a category, or categoryEnd() when no category of that id was added (1.0.0's findCategory)
    CategoryInfo* findCategory(fw::SoundCategory category) {
        CategoryInfo* info = &m_categories[static_cast<unsigned int>(category)];
        return info->category.id_ == category ? info : categoryEnd();
    }
    const CategoryInfo* findCategory(fw::SoundCategory category) const {
        const CategoryInfo* info = &m_categories[static_cast<unsigned int>(category)];
        return info->category.id_ == category ? info : categoryEnd();
    }
    CategoryInfo* categoryEnd() { return m_categories + 18; }
    const CategoryInfo* categoryEnd() const { return m_categories + 18; }
    // the player a handle names, null for an unknown handle (out of line in 1.0.0)
    SoundSsdPlayer* getPlayer(unsigned int handle) {
        return m_players.isValid(handle) ? static_cast<SoundSsdPlayer*>(m_players.getPtr(handle)) : nullptr;
    }
    const SoundSsdPlayer* getPlayer(unsigned int handle) const {
        return m_players.isValid(handle) ? static_cast<const SoundSsdPlayer*>(m_players.getPtr(handle)) : nullptr;
    }
    bool stopSound(unsigned int handle, float fadeTime);  // out of line in 1.0.0
    unsigned int playStream(const char* name, float volume, bool loop, fw::SoundCategory category,
                            fw::SoundPriority priority, SoundSsdBank* bank, fw::SoundType type);
    // the bank registered under a name, null when none is (out of line in 1.0.0)
    SoundSsdBank* findBank(const char* name) {
        unsigned int hash = mm::mtl::hashStrCrc(name);
        for (mm::mtl::List<SoundSsdBank*>::iterator it = m_banks.begin(); it != m_banks.end(); ++it) {
            SoundSsdBank* bank = *it;
            if (bank->m_nameHash == hash && strcmp(bank->m_name.m_str, name) == 0) {
                return bank;
            }
        }
        return nullptr;
    }
    void stopSoundAll(fw::SoundType type, float fadeTime);
    void destroyResourceAll();  // destroys and releases every bank
    // a handle's notification (registered on each handle the driver plays): a handle whose voice is freed drops the
    // delegate and joins m_handles
    ssd::Result SoundHandleDelegate(ssd::Delegate::Handle* delegate, ssd::SoundHandle* handle,
                                    ssd::SoundHandle::Notify::Type type);
    void releaseHandle(ssd::SoundHandle* handle);

    // field names are not the original's
    ssd::SoundCore* m_core;  // 0x10 (ssd::SoundCore::NewInstance(&m_allocator))
    SoundAllocator m_allocator;  // 0x18
    ssd::SoundListener* m_listener;  // 0x28
    mm::Mat44 m_listeningPoint;  // 0x30 (getListeningPoint; identity at construction)
    ml::CriticalSection m_cs;  // 0x70 (every handle function holds it)
    ml::CriticalSectionNC m_csNC;  // 0x98
    ml::CriticalSection m_cs2;  // 0xC0
    CategoryInfo m_categories[18];  // 0xE8 (indexed by fw::SoundCategory; addCategory fills an entry)
    mm::mtl::List<SoundSsdBank*> m_banks;  // 0x838 (stopAll stops each)
    mm::mtl::List<ssd::SoundHandle*> m_handles;  // 0x878
    fw::PointerMap m_players;  // 0x8B8 (handle -> SoundSsdPlayer*)
    mm::mtl::FixedList<SoundPoolMemory*, 256> m_poolMemories;  // 0x8F0 (attachPoolMemory, detachPoolMemory)
    mm::mtl::Map<ssd::SoundHandle*, SoundSsdPlayer*> m_handlePlayers;  // 0x1B10 (releaseHandle finds a handle's player)
    mm::mtl::ObjectAllocator<ssd::SoundHandle> m_handleAllocator;  // 0x1B28 (reserved for the constructor's count)
    bool m_initialized;  // 0x1B60 (set at the end of the constructor)
    int pad_1b64;  // 0x1B64 (1 at the end of the constructor)
    unsigned char pad_1b68[0x8];
    csvb::CCsvbData* m_bgmVolumes;  // 0x1B70 (sound/bgm_vol.csvb or sound/ira_vol.csvb; getBgmVolume reads it)
};
}  // namespace fw

#endif
