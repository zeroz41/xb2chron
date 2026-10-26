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
namespace fw {
// one playing sound of fw::SoundSsdDriver (its handle functions reach it through the driver's PointerMap).
// 1.0.0 has its members out of line in sound_ssd_drv.cpp; 3.0.1 keeps none of them (inlined into the driver).
// Field names are not the original's.
class SoundSsdPlayer : public ::ssd::SoundActor3D {
public:
    bool isValid() const { return m_handle != nullptr && m_handle->IsValidHandle(); }
    bool isPlaying() const { return m_handle != nullptr && m_handle->IsPlay(); }
    bool isReady() const { return m_handle != nullptr && m_handle->GetState() == 8; }
    bool isPreparing() const {
        if (m_handle == nullptr) {
            return false;
        }
        int state = m_handle->GetState();
        return (state | 1) == 7 || state == 5;
    }
    bool isPause() const { return m_pauseCount > 0; }
    bool start() {
        if (m_handle->GetState() != 8) {
            return false;
        }
        return m_handle->Start(this, m_volume, m_pitch) >= 0;
    }
    void stop(float fadeTime) {
        if (isValid()) {
            m_volume = 0.0f;
            m_pauseCount = 0;
            m_handle->Stop(fadeTime);
            Stop(fadeTime);
        }
    }
    bool getTotalTime(float& time) const {
        time = 0.0f;
        if ((m_flags & 0x4) && isValid()) {
            return m_handle->GetDataTime(&time) >= 0;
        }
        return false;
    }
    bool setPlayTime(float time) {
        if ((m_flags & 0x4) && isValid()) {
            return m_handle->SetPlayTime(time) >= 0;
        }
        return false;
    }
    bool getPlayTime(float& time) const {
        time = 0.0f;
        if ((m_flags & 0x4) && isValid()) {
            return m_handle->GetPlayTime(&time) >= 0;
        }
        return false;
    }
    bool setRemainLoopCount(int count) {
        if ((m_flags & 0x4) && isValid()) {
            return m_handle->SetRemainLoopCount(count) >= 0;
        }
        return false;
    }
    bool getRemainLoopCount(int& count) const {
        count = 0;
        if ((m_flags & 0x4) && isValid()) {
            return m_handle->GetRemainLoopCount(&count) >= 0;
        }
        return false;
    }
    bool is3DSource() const {
        if (!isValid()) {
            return false;
        }
        return m_source->is3D();
    }
    bool isLoop() const {
        if (!isValid()) {
            return false;
        }
        return m_source->isLoop();
    }
    void pause(bool pause, float fadeTime) {
        if (isValid()) {
            if (pause) {
                if (m_pauseCount == 0) {
                    m_handle->Pause(true, fadeTime);
                }
                m_pauseCount++;
            } else if (m_pauseCount > 0) {
                m_pauseCount--;
                if (m_pauseCount == 0) {
                    m_handle->Pause(false, fadeTime);
                }
            }
        }
    }
    void setListener(const ssd::SoundListener* listener) {
        if (listener != nullptr && m_handle != nullptr && !is3DSource()) {
            return;
        }
        if (listener != nullptr) {
            m_flags |= 0x8;
        } else {
            m_flags &= ~0x8;
        }
        m_listener = listener;
        SetListener(listener);
    }
    void setVolume(float volume, float fadeTime) {
        if (isValid()) {
            m_volume = volume;
            m_handle->SetCategoryId(m_category);
            m_handle->SetVolume(volume, fadeTime);
        }
    }
    float getVolume(SoundVolumeType type) const {
        float volume = 0.0f;
        if (isValid()) {
            if (type == 0) {
                volume = m_handle->volume_.current;
            } else if (type == 1) {
                return m_handle->GetDistanceVolume();
            } else if (type == 2) {
                volume = m_handle->volume2_;
            }
        }
        return volume;
    }
    void setPitch(float pitch, float fadeTime) {
        pitch = pitch < 0.0f ? 0.0f : (pitch > 8.0f ? 8.0f : pitch);
        if (isValid()) {
            m_pitchRate = pitch;
            m_handle->SetPitch(pitch, fadeTime);
        }
    }
    void setPan(float pan, float fadeTime) {
        pan = pan < -1.0f ? -1.0f : (pan > 1.0f ? 1.0f : pan);
        if (isValid()) {
            m_pan = pan;
            m_handle->SetPan(pan, fadeTime);
        }
    }
    void setPos(const mm::Vec3& pos) { setPos(pos.x, pos.y, pos.z); }
    void setPos(float x, float y, float z) {
        ssd::Vec3 position = {x, y, z};
        SetPosition(position);
    }
    void setCategory(fw::SoundCategory category) {
        m_category = category;
        if (isValid()) {
            m_handle->SetCategoryId(m_category);
        }
    }

    SoundPack* m_pack;  // 0x78
    mm::mtl::IntrusivePtr<SoundSsdSource> m_source;  // 0x80 (the constructor adds a reference)
    ssd::SoundHandle* m_handle;  // 0x88
    const ssd::SoundListener* m_listener;  // 0x90 (setListener)
    fw::SoundCategory m_category;  // 0x98
    float m_volume;  // 0x9C
    float m_pitch;  // 0xA0
    float m_pitchRate;  // 0xA4 (setPitch)
    float m_pan;  // 0xA8 (setPan)
    unsigned char pad_ac[0x4];
    fw::SoundType m_type;  // 0xB0 (fw::SoundSsdDriver::findSe looks for 3; the name is not the original's)
    unsigned char pad_b4[0x4];
    // the handle the driver's PointerMap gave it, its top byte the SoundType (1.0.0's setHandle stores it; the
    // name is not the original's)
    unsigned int m_soundHandle;  // 0xB8
    unsigned char pad_bc[0x8];
    unsigned int m_flags;  // 0xC4 (bit 2: a stream source, bit 3: has a listener)
    int m_pauseCount;  // 0xC8
};
}  // namespace fw

#endif
