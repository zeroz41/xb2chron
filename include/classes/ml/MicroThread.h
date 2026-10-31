#ifndef CLASSES_ML_MICROTHREAD_H
#define CLASSES_ML_MICROTHREAD_H

#include <string.h>
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/DevClock.h"
#include "ml/CriticalSection.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"
#include "nn/os.h"

namespace ml { class MicroThread; }
// a group's handle: its index in MicroThread's groups, -1 for none (MicroUpdater, GfReqManager)
namespace ml { class MLTHG; }
// a thread's handle: its group's index << 28 | its slot << 16 | a serial number, -1 for none
namespace ml { class MLTH; }

namespace ml {
// table 0x7100B78478
class MicroThread : public ::mm::mtl::PtrSingleton< ::ml::MicroThread> {
public:
    // one micro thread, 0x40 bytes (createThread allocates it; the field names are not the original's)
    class MTHREAD {
    public:
        // the handle is createThread's to set
        MTHREAD(void* userData)
            : m_unk0(50), m_unk8(nullptr), m_fiber(nullptr), m_userData(userData), m_sleepClock(0), m_sleepTime(0),
              m_exit(false), m_waitFrames(false), m_ownerThread(nn::os::GetCurrentThread()) {}
        // whether its sleep is over: no sleep left, or a sleep in milliseconds that has passed (sleep and update
        // test it so; the name is not the original's)
        bool isAwake() const {
            if (m_sleepTime == 0) {
                return true;
            }
            if (m_waitFrames) {
                return false;
            }
            float time;
            DevClock::getTimeNow(time, m_sleepClock);
            if (time < m_sleepTime * 0.001f) {
                return false;
            }
            return true;
        }
        int m_unk0;                         // 0x0: 50 from creation, read nowhere in this unit
        void* m_unk8;                       // 0x8: null from creation, read nowhere in this unit
        nn::os::FiberType* m_fiber;         // 0x10: the fiber MicroThreadNx::setupThread gave it
        void* m_userData;                   // 0x18: createThread's arg (getCurrentUserData)
        long m_sleepClock;                  // 0x20: the clock when sleep started
        unsigned int m_sleepTime;           // 0x28: milliseconds, or frames when m_waitFrames
        bool m_exit;                        // 0x2C: set by exit; update releases it
        bool m_waitFrames;                  // 0x2D: sleep's wait: m_sleepTime counts update's frames
        nn::os::ThreadType* m_ownerThread;  // 0x30: the thread that created it
        MLTH* m_id;                         // 0x38: its handle
    };
    // a group of micro threads, 0x678 bytes (createGroup allocates it; the names are not the original's)
    class GROUP {
    public:
        GROUP() {
            memset(m_threads, 0, sizeof(m_threads));
            m_threadNum = 0;
        }
        MLTHG* m_id;                                 // 0x0: its handle
        int m_threadNum;                             // 0x8
        MTHREAD* m_threads[64];                      // 0x10: by the slot in their handle
        ::mm::mtl::FixedList<MTHREAD*, 64> m_list;   // 0x210: the order update runs them in
        MTHREAD* m_current;                          // 0x670: the one running now
    };

    MicroThread() : m_groupNum(0), m_serial(0), m_currentGroup(nullptr) {
        memset(m_groups, 0, sizeof(m_groups));
    }
    // the instance, a MicroThreadNx made from the product memory, if there is none yet
    static MicroThread* create();
    // deletes the instance, if any (ProcDesktop::wkStandbyLogout calls it)
    static void destroy();
    virtual ~MicroThread();  // slot 0
    virtual void destroyThread(ml::MicroThread::MTHREAD*) = 0;  // slot 2
    virtual void switchThreadMain(ml::MicroThread::MTHREAD*) = 0;  // slot 3
    virtual void switchThread(ml::MicroThread::MTHREAD*, ml::MicroThread::MTHREAD*) = 0;  // slot 4
    virtual void setupThread(ml::MicroThread::MTHREAD*, nn::os::FiberType* (*)(void*)) = 0;  // slot 5
    void destroyAll();
    MLTHG* createGroup();
    void releaseThread(MLTH* thread);
    void releaseGroup(MLTHG* group);
    MLTH* createThread(MLTHG* group, nn::os::FiberType* (*func)(void*), void* arg);
    void sleep(unsigned int frames, bool wait);
    void update(MLTHG* group);
    // moves the threads createThread made into their groups
    void tail();
    void exit();
    // the arg the running thread was created with (MicroUpdater::fnMicroUpdate reads its updater through it)
    void* getCurrentUserData();

    GROUP* m_groups[16];                         // 0x8: by group handle
    ::mm::mtl::FixedVector<MTHREAD*, 64> m_newThreads;  // 0x88: made by createThread, not yet in a group (tail)
    int m_groupNum;                              // 0x290
    unsigned int m_serial;                       // 0x294: the next thread handle's serial number
    CriticalSection m_cs;                        // 0x298
    GROUP* m_currentGroup;  // 0x2C0: the group running now (getCurrentThreadID reads its thread); the name is not the original's
};
}  // namespace ml

#endif
