#ifndef CLASSES_FW_SOUNDSSDPLAYER_H
#define CLASSES_FW_SOUNDSSDPLAYER_H

#include "classes/ssd/SoundActor3D.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/fw/SoundSsdSource.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"
#include "ssd/Math.h"

namespace fw { enum SoundCategory : int; }
namespace fw { class SoundPack; }
namespace fw { enum SoundVolumeType : int; }
namespace ssd { class SoundListener; }

namespace fw { enum SoundType : int; }
namespace mm { namespace mtl { class IAllocator; }}
namespace fw {
// what fw::SoundSsdDriver's play functions hand the player's constructor, which keeps a copy at 0x78 (the type's
// name is from the constructor's symbol; the member names are not the original's)
struct SoundPlayerSetupParam {
    // playSeLocal's and playStream's setup before they fill it: category 3, volume and pitch rate 1, the rest 0
    SoundPlayerSetupParam()
        : allocator(nullptr), handle(nullptr), listener(nullptr), category(static_cast<SoundCategory>(3)), volume(1.0f),
          pitch(0.0f), pitchRate(1.0f), pan(0.0f), bankId(0), type(static_cast<SoundType>(0)) {}
    // FrameworkMemory::getAllocator(5) in playSeLocal and playStream
    mm::mtl::IAllocator* allocator;
    mm::mtl::IntrusivePtr<SoundSsdSource> source;  // 0x08 (the copy adds a reference)
    ssd::SoundHandle* handle;  // 0x10
    const ssd::SoundListener* listener;  // 0x18 (setListener)
    fw::SoundCategory category;  // 0x20
    float volume;  // 0x24
    float pitch;  // 0x28
    float pitchRate;  // 0x2C (setPitch)
    float pan;  // 0x30 (setPan)
    int bankId;  // 0x34: the source's m_bankId (playSeLocal)
    fw::SoundType type;  // 0x38 (fw::SoundSsdDriver::findSe looks for 3)
};

// one playing sound of fw::SoundSsdDriver (its handle functions reach it through the driver's PointerMap).
// 1.0.0 has its members out of line in sound_ssd_drv.cpp; 3.0.1 keeps none of them (inlined into the driver).
// Field names are not the original's. It holds its SoundActor3D as a member, not as a base: the constructor calls the
// complete-object SoundActor3D constructor and stores no table of its own (the original has no SoundSsdPlayer table),
// and the destructor (deleteObject<SoundSsdPlayer>) calls Quit and the member's destructor directly.
class SoundSsdPlayer {
public:
    SoundSsdPlayer(const SoundPlayerSetupParam& param);
    ~SoundSsdPlayer() { m_actor.Quit(); }
    // the actor through a pointer (stop() calls Stop through its table; the name is not the original's)
    ssd::SoundActor3D* getActor() { return &m_actor; }
    bool isValid() const { return m_setup.handle != nullptr && m_setup.handle->IsValidHandle(); }
    bool isPlaying() const { return m_setup.handle != nullptr && m_setup.handle->IsPlay(); }
    bool isReady() const { return m_setup.handle != nullptr && m_setup.handle->GetState() == 8; }
    bool isPreparing() const {
        if (m_setup.handle == nullptr) {
            return false;
        }
        int state = m_setup.handle->GetState();
        return (state | 1) == 7 || state == 5;
    }
    bool isPause() const { return m_pauseCount > 0; }
    bool start() {
        if (m_setup.handle->GetState() != 8) {
            return false;
        }
        return m_setup.handle->Start(&m_actor, m_setup.volume, m_setup.pitch) >= 0;
    }
    void stop(float fadeTime) {
        if (isValid()) {
            m_setup.volume = 0.0f;
            m_pauseCount = 0;
            m_setup.handle->Stop(fadeTime);
            getActor()->Stop(fadeTime);
        }
    }
    bool getTotalTime(float& time) const {
        time = 0.0f;
        if ((m_flags & 0x4) && isValid()) {
            return m_setup.handle->GetDataTime(&time) >= 0;
        }
        return false;
    }
    bool setPlayTime(float time) {
        if ((m_flags & 0x4) && isValid()) {
            return m_setup.handle->SetPlayTime(time) >= 0;
        }
        return false;
    }
    bool getPlayTime(float& time) const {
        time = 0.0f;
        if ((m_flags & 0x4) && isValid()) {
            return m_setup.handle->GetPlayTime(&time) >= 0;
        }
        return false;
    }
    bool setRemainLoopCount(int count) {
        if ((m_flags & 0x4) && isValid()) {
            return m_setup.handle->SetRemainLoopCount(count) >= 0;
        }
        return false;
    }
    bool getRemainLoopCount(int& count) const {
        count = 0;
        if ((m_flags & 0x4) && isValid()) {
            return m_setup.handle->GetRemainLoopCount(&count) >= 0;
        }
        return false;
    }
    bool is3DSource() const {
        if (!isValid()) {
            return false;
        }
        return m_setup.source->is3D();
    }
    bool isLoop() const {
        if (!isValid()) {
            return false;
        }
        return m_setup.source->isLoop();
    }
    void pause(bool pause, float fadeTime) {
        if (isValid()) {
            if (pause) {
                if (m_pauseCount == 0) {
                    m_setup.handle->Pause(true, fadeTime);
                }
                m_pauseCount++;
            } else if (m_pauseCount > 0) {
                m_pauseCount--;
                if (m_pauseCount == 0) {
                    m_setup.handle->Pause(false, fadeTime);
                }
            }
        }
    }
    void setListener(const ssd::SoundListener* listener) {
        if (listener != nullptr && m_setup.handle != nullptr && !is3DSource()) {
            return;
        }
        if (listener != nullptr) {
            m_flags |= 0x8;
        } else {
            m_flags &= ~0x8;
        }
        m_setup.listener = listener;
        m_actor.SetListener(listener);
    }
    void setVolume(float volume, float fadeTime) {
        if (isValid()) {
            m_setup.volume = volume;
            m_setup.handle->SetCategoryId(m_setup.category);
            m_setup.handle->SetVolume(volume, fadeTime);
        }
    }
    float getVolume(SoundVolumeType type) const {
        float volume = 0.0f;
        if (isValid()) {
            if (type == 0) {
                volume = m_setup.handle->volume_.current;
            } else if (type == 1) {
                return m_setup.handle->GetDistanceVolume();
            } else if (type == 2) {
                volume = m_setup.handle->volume2_;
            }
        }
        return volume;
    }
    void setPitch(float pitch, float fadeTime) {
        pitch = pitch < 0.0f ? 0.0f : (pitch > 8.0f ? 8.0f : pitch);
        if (isValid()) {
            m_setup.pitchRate = pitch;
            m_setup.handle->SetPitch(pitch, fadeTime);
        }
    }
    void setPan(float pan, float fadeTime) {
        pan = pan < -1.0f ? -1.0f : (pan > 1.0f ? 1.0f : pan);
        if (isValid()) {
            m_setup.pan = pan;
            m_setup.handle->SetPan(pan, fadeTime);
        }
    }
    void setPos(const mm::Vec3& pos) { setPos(pos.x, pos.y, pos.z); }
    void setPos(float x, float y, float z) {
        ssd::Vec3 position = {x, y, z};
        m_actor.SetPosition(position);
    }
    void setCategory(fw::SoundCategory category) {
        m_setup.category = category;
        if (isValid()) {
            m_setup.handle->SetCategoryId(m_setup.category);
        }
    }

    ssd::SoundActor3D m_actor;  // 0x0
    // 0x78: the setup the constructor copies whole (the copy constructor memcpys the 0x2C bytes after the source)
    SoundPlayerSetupParam m_setup;
    // the handle the driver's PointerMap gave it, its top byte the SoundType (1.0.0's setHandle stores it; the
    // name is not the original's)
    unsigned int m_soundHandle;  // 0xB8
    float pad_bc;  // -1 at construction
    unsigned char pad_c0[0x4];
    unsigned int m_flags;  // 0xC4 (bit 2: a stream source, bit 3: has a listener)
    int m_pauseCount;  // 0xC8
};
}  // namespace fw

#endif
