#ifndef CLASSES_FW_FRAMEWORK_H
#define CLASSES_FW_FRAMEWORK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/AllocHandle.h"
#include "fw/UpdateInfo.h"
#include "mm/mtl/FixedVector.h"
#include "classes/fw/MemHandlebaseAllocator.h"
#include "classes/mm/threading/EventWait.h"

namespace fw { class IPauseTrigger; }
namespace fw { class UpdateInfo; }
namespace fw { class Framework; }
namespace ml { class Scn; }
namespace ml { class Thread; }
namespace fw { class UpdateState; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B41668
class Framework : public ::mm::mtl::PtrSingleton< ::fw::Framework> {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in the framework's unit and
    // GfManager::fn_710032A1FC calls it on PtrSingleton<fw::Framework>'s instance. What it does: stores its bool at 0x459
    void fn_71001836D0(bool flag);
    static void addPauseCallback(IPauseTrigger* trigger);
    static void removePauseCallback(IPauseTrigger* trigger);
    // Placeholder name: nothing in 1.0.0 names it (its GfManager::postUpdate calls neither). A member: this is the
    // framework (GfManager::postUpdate passes PtrSingleton<fw::Framework>'s instance). What it does: signals the event
    // wait at 0x3F8 of the framework (EventWait::setSignal(true)); GfManager::postUpdate passes the update info, unused
    void fn_710018369C(const fw::UpdateInfo& info);
    // Placeholder name: as fn_710018369C. What it does: waits while the event wait at 0x3F8 is signalled (loops on
    // EventWait::isSignal); GfManager::postUpdate calls it after the menus' postUpdate
    void fn_71001836A8();
    // one of the 32 update layers (the name is not the original's): beginFrame takes the requested speed and pause
    // into the current ones and scales the frame's delta by the speed
    class Layer {
    public:
        Layer() : m_speedRequest(1.0f), m_deltaTime(1.0f), m_speed(1.0f), m_pauseRequest(false), m_pause(false) {}
        float m_speedRequest;  // setLayerUpdateSpeed stores it
        float m_deltaTime;     // beginFrame: m_speedRequest times the update speed
        float m_speed;         // getLayerUpdateSpeed reads it
        bool m_pauseRequest;   // setLayerPause stores it
        bool m_pause;          // isLayerPause reads it
    };
    Framework();
    virtual ~Framework();  // slot 0
    void prepareEnter();
    void prepareExit();
    void activate();
    void deactivate();
    static void destroyManager();
    static mm::mtl::IAllocator* getAllocator();
    void enterFinalizeApplet();
    static mtl::ALLOC_HANDLE getMemHandle();  // the memory resources are made in (ResourceManager::getMemSYS)
    static void setUpdateSpeed(float speed);
    static void setLayerUpdateSpeed(unsigned int layer, float speed);
    static float getLayerUpdateSpeed(unsigned int layer);
    static void setLayerPause(unsigned int layer, bool pause);
    static unsigned int getFrameCount();
    static bool isLayerPause(unsigned int layer);
    unsigned char pad_8[0xC];
    float m_frameRate;  // frames per second: beginFrame's frame time is 1 / it (the name is not the original's)
    unsigned char pad_18[0x40];
    ml::Scn* m_scn;  // what LayerSetManager gives layer::LayerManager; the name is not the original's
    unsigned char pad_60[0x8];
    mtl::ALLOC_HANDLE m_memHandle;  // getMemHandle hands it out (FrameworkMemory's kind 5 while it is empty)
    unsigned char pad_6C[0xC];
    fw::UpdateInfo m_updateInfo;    // beginFrame fills it; the name is not the original's
    int m_state;                    // prepareEnter sets 3, initialize 1; updates run in 2..4 (name inferred)
    unsigned char pad_88[0x4];
    float m_updateSpeed;            // setUpdateSpeed stores it (the name is not the original's)
    unsigned char pad_90[0x8];
    Layer m_layers[32];             // the layer functions index it (the name is not the original's)
    // addPauseCallback adds to it, activate/deactivate call each one's (the name is not the original's)
    mm::mtl::FixedVector<IPauseTrigger*, 32> m_pauseTriggers;
    fw::MemHandlebaseAllocator m_allocator;  // getAllocator returns it (the name is not the original's)
    // initialize creates it ("PosuUpdateThread") on this field; the destructor waits until it terminates and
    // releases it (the name is not the original's)
    ml::Thread* m_thread;
    mm::threading::EventWait m_threadEvent;  // fn_710018369C signals it, fn_71001836A8 waits on it (name inferred)
    bool m_threadExit;   // the destructor sets it before waking the thread (the name is not the original's)
    bool m_threadFlag;   // fn_71001836D0 stores it, initialize stores the config's flag (name inferred)
};
}  // namespace fw

#endif
