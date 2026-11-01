#ifndef CLASSES_FW_SOUNDPOOLMEMORY_H
#define CLASSES_FW_SOUNDPOOLMEMORY_H

#include "classes/fw/SoundSsdDriver.h"
#include "classes/ssd/SoundCore.h"
#include "nn/audio.h"
#include "nn/diag.h"

namespace fw {
// a memory block SoundSsdDriver::attachPoolMemory hands to the audio renderer as a memory pool (0x18, no table;
// the driver's m_poolMemories lists them, updatePoolMemory releases the detached ones). Member names are not the
// original's.
class SoundPoolMemory {
public:
    SoundPoolMemory(void* memory, unsigned int size) : m_memory(memory), m_size(size), m_state(1) {
        NN_ABORT_UNLESS(nn::audio::AcquireMemoryPool(getConfig(), &m_pool, memory, size) &&
                        nn::audio::RequestAttachMemoryPool(&m_pool));
    }
    ~SoundPoolMemory() {
        detach();
        release();
    }

    // the driver's renderer config, null without a driver or core
    static nn::audio::AudioRendererConfig* getConfig() {
        SoundSsdDriver* driver = SoundSsdDriver::sys();
        if (driver == nullptr || driver->m_core == nullptr) {
            return nullptr;
        }
        return driver->m_core->GetPlatformData<nn::audio::AudioRendererConfig>(
            ssd::SoundCore::audioRendererConfigName_);
    }
    // an attached pool's detach requested (state 2); a pool with no memory is done (state 3)
    void detach() {
        if (m_state == 1) {
            getConfig();
            nn::audio::RequestDetachMemoryPool(&m_pool);
            m_state = 2;
        } else if (m_memory == nullptr) {
            m_state = 3;
        }
    }
    // a detaching pool whose detach finished (pool state 3) released; done in any case (state 3)
    void release() {
        if (m_state == 2) {
            if (nn::audio::GetMemoryPoolState(&m_pool) == static_cast<nn::audio::MemoryPoolType::State>(3)) {
                nn::audio::ReleaseMemoryPool(getConfig(), &m_pool);
                m_memory = nullptr;
                m_size = 0;
                m_state = 3;
            }
        }
        m_state = 3;
    }

    void* m_memory;  // 0x0
    nn::audio::MemoryPoolType m_pool;  // 0x8
    unsigned int m_size;  // 0x10
    int m_state;  // 0x14 (1 attached, 2 detaching, 3 done)
};
}  // namespace fw

#endif
