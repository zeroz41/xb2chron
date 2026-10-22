#ifndef CLASSES_GF_GFEVTBGM_H
#define CLASSES_GF_GFEVTBGM_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedQueue.h"

namespace fw { class UpdateInfo; }
namespace gf { class EvtBgmTask; }
namespace gf { class GfEvtBgm; }
namespace gf { class GfSetupParam; }

namespace gf {
// an event's BGM request (0x68 bytes): GfEvtBgm::playBgm, stopBgm and changeBgmVolume take one, the tasks they
// queue keep a copy, and GfEvtBgm holds the one that plays
class EventBgmSetup {
public:
    EventBgmSetup() : m_volume(1.0f), m_volumeTime(0.0f), pad_4c(), m_delay(0.0f), m_stopTime(0.0f),
                      m_overTime(0.0f), m_noBgm(false), pad_61(), m_silentIfEmpty(false) {}

    mm::mtl::FixStr<64> m_name;  // the BGM's name (setPlayBgmTakeOver sets it)
    float m_volume;  // EvtBgmTaskVolume moves the playing volume to it; the name is not the original's
    float m_volumeTime;  // how long EvtBgmTaskVolume takes to; the name is not the original's
    unsigned char pad_4c[8];
    float m_delay;  // EvtBgmTaskDelay waits it out before the BGM plays; the name is not the original's
    float m_stopTime;  // EvtBgmTaskDelayStop waits it out before the BGM stops; the name is not the original's
    float m_overTime;  // cancelOverTime clears it; stopBgm queues no stop while it is set
    bool m_noBgm;  // EvtBgmTaskDelay::start plays no BGM for it; the name is not the original's
    unsigned char pad_61[4];
    bool m_silentIfEmpty;  // setPlayParam names "SilentBgm" for a setup without a name; the name is not the original's
};

// table 0x7100B53AD0: the event BGM, run through a queue of tasks
class GfEvtBgm : public ::mm::mtl::PtrSingleton< ::gf::GfEvtBgm> {
public:
    // the state the tasks set (the enumerators' names are not the original's)
    enum PLAY_STATE : int {
        PLAY_STATE_STOP = 0,  // EvtBgmTaskDelayStop::update: stopped
        PLAY_STATE_DELAY = 1,  // EvtBgmTaskDelay::start: waiting out its delay
        PLAY_STATE_NO_BGM = 2,  // EvtBgmTaskDelay::start for a setup's m_noBgm: no name to play
        PLAY_STATE_PLAY = 3,  // EvtBgmTaskDelay::update: playing
        PLAY_STATE_STOP_DELAY = 4,  // EvtBgmTaskDelayStop::start: waiting out its stop time
    };

    // out of line in 1.0.0; inline in 3.0.1
    GfEvtBgm(const GfSetupParam& param) : m_state(PLAY_STATE_STOP), m_currentTask(nullptr) {
        initialize(param);
    }
    virtual ~GfEvtBgm();  // slot 0
    void initialize(const GfSetupParam& param) {
        m_initialized = true;
    }
    void finalize() {
        m_initialized = false;
    }
    bool isInitialized() {
        return m_initialized;
    }
    void clear();
    static void build(const GfSetupParam& param);
    static void destroy();
    void playBgm(const EventBgmSetup& setup);
    bool isPlayBgm() const;
    void stopBgm(const EventBgmSetup& setup);
    void cancelOverTime();
    void changeBgmVolume(const EventBgmSetup& setup);
    void setFadeoutVolume();
    // out of line in 1.0.0; inline in 3.0.1
    void setPlayState(PLAY_STATE state) {
        m_state = state;
    }
    void setPlayParam(const EventBgmSetup& setup) {
        m_setup = setup;
        if (m_setup.m_name.m_nLen == 0 && !setup.m_noBgm && setup.m_silentIfEmpty) {
            m_setup.m_name = "SilentBgm";
        }
    }
    bool isEnableEventBgm() const;
    void setPlayBgmVolume(float volume) {
        m_setup.m_volume = volume;
    }
    void setPlayBgmTakeOver(const char* name);
    float getPlayBgmTime() const;
    float getTotalBgmTime() const;
    void updateBgmTask(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);

    bool m_initialized;  // initialize sets it, finalize clears it
    EventBgmSetup m_setup;  // the BGM that plays (the tasks set it)
    PLAY_STATE m_state;  // setPlayState's
    mm::mtl::FixedQueue<EvtBgmTask*, 128> m_tasks;  // the tasks to run, the first running
    EvtBgmTask* m_currentTask;  // the first task, once updateBgmTask has started it
};
}  // namespace gf

#endif
