#ifndef CLASSES_FW_SOUNDSSDPLAYER_H
#define CLASSES_FW_SOUNDSSDPLAYER_H

#include "classes/ssd/SoundActor3D.h"
#include "classes/ssd/SoundHandle.h"

namespace fw { enum SoundCategory : int; }
namespace fw { class SoundPack; }
namespace fw { class SoundSsdSource; }

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
    void setCategory(fw::SoundCategory category) {
        m_category = category;
        if (isValid()) {
            m_handle->SetCategoryId(m_category);
        }
    }

    SoundPack* m_pack;  // 0x78
    SoundSsdSource* m_source;  // 0x80 (an IntrusivePtr<SoundSsdSource>: the constructor adds a reference)
    ssd::SoundHandle* m_handle;  // 0x88
    unsigned char pad_90[0x8];
    fw::SoundCategory m_category;  // 0x98
    float m_volume;  // 0x9C
    float m_pitch;  // 0xA0
    unsigned char pad_a4[0x20];
    unsigned int m_flags;  // 0xC4 (bit 2: a stream source, bit 3: has a listener)
    int m_pauseCount;  // 0xC8
};
}  // namespace fw

#endif
