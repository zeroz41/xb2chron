#ifndef CLASSES_ML_WORKCPU_H
#define CLASSES_ML_WORKCPU_H

#include "classes/ml/WorkObj.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixedList.h"
#include "classes/ml/reslist.h"
#include "ml/CriticalSection.h"
#include "classes/mm/mtl/PtrSingleton.h"
namespace ml {
enum CPUID : int;
// how WorkCpu::sync waits (enumerators not recovered: DrCalcTexStreamMan::jobWait passes 0)
enum WKCPU_SYNC : int;
class IErrorCB; class WorkCpuThread; class IWorkInfomation; class IWorkBackground; class IThreadValue; }

namespace ml {
// table 0x7100B78E08; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkCpu>'s table)
class WorkCpu : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkCpu> {
public:
    // a job group beginUpdate wakes every frame: entryAutoExecGrp enters them sorted by the second word (the field
    // names are not the original's)
    struct AUTO_EXEC {
        int m_group;
        unsigned int m_priority;
    };

    WorkCpu(const char* name, WorkObj* parent);
    virtual ~WorkCpu();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // its object made and every CPU thread logged in
    static bool isInitialized();
    // starts a job group's threads (DrCalcTexStreamMan::entryJob) and waits for them (DrCalcTexStreamMan::jobWait)
    static void wakeup(int group);
    static void sync(int group, WKCPU_SYNC sync, CPUID cpu);
    // the undoing of a job group's entryAutoExecGrp and createGroupHandle (navi::NvmshManager's destructor)
    static void removeAutoExecGrp(int group);
    static void releaseGroupHandle(int group);
    static const unsigned int& getFrameCount();  // the work CPU's frame counter (fw::Framework::getFrameCount)
    // a listener told of the HOME menu no more (fw::MovieManager's destructor)
    static void addBackgroundListener(IWorkBackground* listener);
    static void removeBackgroundListener(IWorkBackground* listener);
    // a listener of system information (operation and performance mode) no more (ml::DevPerfNx's destructor)
    static void addSystemInfoListener(IWorkInfomation* listener);
    static void removeSystemInfoListener(IWorkInfomation* listener);
    // a value swapped every frame no more (threadval's destructor)
    static void entrySwap(IThreadValue* value);
    static void removeSwap(IThreadValue* value);
    static unsigned int thSwap(void* bank, void* param);
    static unsigned int thRender(void* cpu, void* param);
    static void beginUpdate();
    static void beginFrame();
    static void resumeThread();
    static WorkCpu* create(WorkObj* parent);
    static CPUID getCurrentCPUID();
    // the library enabled (sets _mlwcpu::s_bEnableLib)
    static void setEnableSystem();
    static void setRenderSubCpu(bool renderSubCpu);
    // the CPU work's stack memory, none before it exists
    static mtl::ALLOC_HANDLE getMemStack();
    // the bank in use this frame: 0 even, else odd (getOdd is its negation)
    static int getEven();
    // the calling thread's id, the main thread's, the thread a CPU runs and the CPU the renderer runs on
    // (ml::CacheDraw's command queue compares them)
    static unsigned long getCurrentThreadId();
    static unsigned long getMainThreadId();
    static unsigned long getThreadId(CPUID cpu);
    static CPUID getRenderCPUID();
    static bool getOdd();
    // shutting down (false before the CPU work exists)
    static bool isShutdown();
    static void backgroundProcess();
    static bool isHomeMenuEnable();
    // callback entered in, removed from the error callbacks (false for none, no CPU work or a full list; the
    // parameter names are not the original's)
    static bool registErrorCB(IErrorCB* callback);
    static bool unregistErrorCB(IErrorCB* callback);
    // the clock the frame began at: [0] of m_beginClock when first, else [4] (the parameter name is not the original's)
    static const long& getBeginClock(bool first);
    // the CPU the sub work runs on
    static CPUID getSubWorkCPUID();
    // starts the render jobs (wakeup) unless stalled or shutting down
    static void beginRender();
    static void endUpdate();
    static void swapBank();

    static bool s_bRenderSubCpu;

    // 0x1B0 0x2: shutting down (isShutdown), 0x20: the update ended (endUpdate) (the name is not the original's)
    unsigned int m_flags;
    unsigned char pad_1b4[0x4];
    mtl::ALLOC_HANDLE m_memStack;      // 0x1B8 getMemStack (the name is not the original's)
    // 0x1BC the CPUs the work runs on: getRenderCPUID and getSubWorkCPUID choose by it (the name is not the original's)
    unsigned int m_cpuNum;
    // 0x1C0 the values swapped each frame, one list per CPU: entrySwap enters a value in the shortest of the first
    // m_cpuNum and keeps the list's index as its getCpuBank, removeSwap picks the list by it, thSwap swaps one list
    // (the name is not the original's)
    reslist<IThreadValue*> m_swap[3];
    unsigned char pad_280[0x14C0];
    // 0x1740 the thread work of each CPU, m_cpuNum of them (isInitialized asks each it is logged in; the name is not
    // the original's)
    WorkCpuThread* m_thread[3];
    // 0x1758 the job group the renderer wakes (beginRender) and syncs (endUpdate); -1 for none (the name is not the
    // original's)
    int m_renderGroup;
    // 0x175C the job group swapBank wakes and syncs; -1 for none (the name is not the original's)
    int m_swapGroup;
    bool m_rendering;                  // 0x1760 set while thRender renders (the name is not the original's)
    unsigned char pad_1761[0x3];
    int m_bank;                        // 0x1764 getEven (the name is not the original's)
    unsigned char pad_1768[0x38];
    // 0x17A0 the job groups beginUpdate wakes (entryAutoExecGrp, removeAutoExecGrp) (the name is not the original's)
    mm::mtl::FixedList<AUTO_EXEC, 32> m_autoExec;
    unsigned char pad_1958[0x248];
    // 0x1BA0 the listeners told of the HOME menu (add/removeBackgroundListener, setBackground) and of the system
    // information (add/removeSystemInfoListener), under one lock (the names are not the original's)
    mm::mtl::FixedList<IWorkBackground*, 32> m_backgroundListener;
    mm::mtl::FixedList<IWorkInfomation*, 32> m_systemInfoListener;  // 0x1DE0
    unsigned long m_mainThreadId;      // 0x2020 getMainThreadId (the name is not the original's)
    int m_bankCount[2];                // 0x2028 beginFrame zeroes the current bank's (the name is not the original's)
    float m_renderTime;                // 0x2030 thRender's time of WorkRootState::renderWork (the name is not the original's)
    unsigned char pad_2034[0x14];
    long m_beginClock[8];              // 0x2048 getBeginClock returns [0] or [4] (the name is not the original's)
    unsigned char pad_2088[0x8];
    unsigned int m_frameCount;         // 0x2090 getFrameCount (the name is not the original's)
    unsigned char pad_2094[0xC];
    // 0x20A0 the error callbacks registErrorCB enters and unregistErrorCB removes, under m_errorCBLock (the names are
    // not the original's)
    mm::mtl::FixedList<IErrorCB*, 32> m_errorCB;
    CriticalSectionNC m_errorCBLock;   // 0x22E0
};
}  // namespace ml

#endif
