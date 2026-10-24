#ifndef CLASSES_FW_SOUNDSSDDRIVER_H
#define CLASSES_FW_SOUNDSSDDRIVER_H

#include "classes/fw/ISoundDriver.h"
#include "classes/fw/PointerMap.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ssd/Allocator.h"
#include "mm/Mat44.h"
#include "ml/CriticalSection.h"

namespace fw { enum SoundCategory : int; }
namespace fw { class SoundCategoryDebugInfo; }
namespace fw { class SoundHandleDebugInfo; }
namespace fw { class SoundOutputType; }
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
class SoundSsdPlayer;
}  // namespace fw
namespace ssd { class SoundCore; class SoundListener; }
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
    virtual void getCategoryVolume(fw::SoundCategory) const;  // slot 9
    virtual void setCategoryMute(fw::SoundCategory, bool, float);  // slot 10
    virtual void setCategoryPitch(fw::SoundCategory, float, float);  // slot 11
    virtual void setOutputMode(fw::SoundOutputType);  // slot 12
    virtual void addCategory(fw::SoundCategory, float, char const*);  // slot 13
    virtual void removeCategory(fw::SoundCategory);  // slot 14
    virtual void pauseCategory(fw::SoundCategory, bool, float);  // slot 15
    virtual bool isDeviceEnable() const;  // slot 16
    virtual void playBgm(char const*, float, bool, int, fw::SoundCategory);  // slot 17
    virtual bool startBgm(unsigned int);  // slot 18
    virtual bool stopBgm(unsigned int, float);  // slot 19
    virtual void stopBgmAll();  // slot 20
    virtual void playVoice(char const*, float, bool, fw::SoundCategory);  // slot 21
    virtual bool startVoice(unsigned int);  // slot 22
    virtual bool stopVoice(unsigned int, float);  // slot 23
    virtual void playSe(char const*, fw::SoundPack*, float, fw::SoundCategory);  // slot 24
    virtual void playSe(unsigned int, fw::SoundPack*, float, fw::SoundCategory);  // slot 25
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
    virtual void findSe(char const*) const;  // slot 52
    virtual void attachPoolMemory(void*, unsigned int);  // slot 53
    virtual void detachPoolMemory(void*, unsigned int);  // slot 54

    bool isValid() const { return m_core != nullptr; }
    // the player a handle names, null for an unknown handle (out of line in 1.0.0)
    SoundSsdPlayer* getPlayer(unsigned int handle) {
        return m_players.isValid(handle) ? static_cast<SoundSsdPlayer*>(m_players.getPtr(handle)) : nullptr;
    }
    const SoundSsdPlayer* getPlayer(unsigned int handle) const {
        return m_players.isValid(handle) ? static_cast<const SoundSsdPlayer*>(m_players.getPtr(handle)) : nullptr;
    }
    bool stopSound(unsigned int handle, float fadeTime);  // out of line in 1.0.0
    void stopSoundAll(fw::SoundType type, float fadeTime);

    // field names are not the original's
    ssd::SoundCore* m_core;  // 0x10 (ssd::SoundCore::NewInstance(&m_allocator))
    SoundAllocator m_allocator;  // 0x18
    ssd::SoundListener* m_listener;  // 0x28
    mm::Mat44 m_listeningPoint;  // 0x30 (getListeningPoint; identity at construction)
    ml::CriticalSection m_cs;  // 0x70 (every handle function holds it)
    ml::CriticalSectionNC m_csNC;  // 0x98
    ml::CriticalSection m_cs2;  // 0xC0
    unsigned char pad_e8[0x7D0];  // 18 ssd::SoundCategory (0x68 each), List<SoundSsdBank*>, List<ssd::SoundHandle*>
    fw::PointerMap m_players;  // 0x8B8 (handle -> SoundSsdPlayer*)
};
}  // namespace fw

#endif
