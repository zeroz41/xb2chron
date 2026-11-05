#ifndef CLASSES_ML_WORKCPU_H
#define CLASSES_ML_WORKCPU_H

#include "classes/ml/WorkObj.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixedList.h"
#include "classes/ml/reslist.h"
#include "classes/ml/fixed_size_alloc.h"
#include "ml/CriticalSection.h"
#include "classes/mm/mtl/PtrSingleton.h"
namespace mm { class Col3; }
namespace ml {
enum CPUID : int;
// how WorkCpu::sync waits (enumerators not recovered: DrCalcTexStreamMan::jobWait passes 0)
enum WKCPU_SYNC : int;
class IErrorCB; class TJOB; class WorkCpuThread; class IWorkInfomation; class IWorkBackground; class IThreadValue; }

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
    // a job group createGroupHandle hands out and releaseGroupHandle takes back (0x20 bytes, 8-aligned: its
    // FixedList node is 0x28)
    struct GRPLIST {
        unsigned long pad_0;
        // 0x8 the group's jobs on each CPU, by the CPU less one (wkTail moves each job to its own CPU's; the name is
        // not the original's)
        reslist<TJOB*>* m_job[3];
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
    // enters a job group in the groups beginUpdate wakes, on cpu (Scn's constructor: its thUpAfter group on CPU 1,
    // 0xF; the unnamed parameter is not known yet)
    static void entryAutoExecGrp(int group, CPUID cpu, unsigned int);
    static void releaseGroupHandle(int group);
    // a job group of count threads' room (Device::wkStandbyLogin makes one for its jobUpdate; the parameter name is
    // not the original's)
    static int createGroupHandle(unsigned int count);
    // enters job(data, extra) on the group's thread on cpu (Device::wkStandbyLogin: Device::jobUpdate on the render
    // CPU; the unnamed parameters are not known yet)
    static void entryJobThread(int group, unsigned int (*job)(void*, void*), unsigned int, void* data, void* extra,
                               CPUID cpu, bool, bool);
    static const unsigned long& getFrameCount();  // the work CPU's frame counter (fw::Framework::getFrameCount)
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
    // the bank in use this frame: 0 even, else odd (getOdd is its negation; both return int: the callers index with
    // the result unmasked)
    static int getEven();
    // the calling thread's id, the main thread's, the thread a CPU runs and the CPU the renderer runs on
    // (ml::CacheDraw's command queue compares them)
    static unsigned long getCurrentThreadId();
    static unsigned long getMainThreadId();
    static unsigned long getThreadId(CPUID cpu);
    static CPUID getRenderCPUID();
    // runs a function on a CPU's thread (Scn::term runs Scn::thRenderKillTerminate on the render CPU's, passing the
    // scene, no argument, no colour, true and sync 0); the return type is not in the symbols
    static void runThread(CPUID cpu, unsigned int (*func)(void*, void*), void*, void*, const mm::Col3* col,
                          bool, WKCPU_SYNC sync);
    static int getOdd();
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
    // syncs the render and auto groups and waits until no CPU thread holds a job
    static void endRender();
    // closes the frame: frame times, render sync, WorkControl::endFrame, the frame count and updateMessage
    static void endFrame();
    void updateMessage();
    static void swapBank();
    // a job off m_jobAlloc (null when all are in use) and one handed back, under the job lock
    TJOB* allocJob();
    void freeJob(TJOB* job);

    static bool s_bRenderSubCpu;

    // 0x1B0 0x2: shutting down (isShutdown), 0x20: the update ended (endUpdate) (the name is not the original's)
    unsigned int m_flags;
    mtl::ALLOC_HANDLE m_memWork;       // 0x1B4 the destructor erases it first (the name is not the original's)
    mtl::ALLOC_HANDLE m_memStack;      // 0x1B8 getMemStack (the name is not the original's)
    // 0x1BC the CPUs the work runs on: getRenderCPUID and getSubWorkCPUID choose by it (the name is not the original's)
    unsigned int m_cpuNum;
    // 0x1C0 the values swapped each frame, one list per CPU: entrySwap enters a value in the shortest of the first
    // m_cpuNum and keeps the list's index as its getCpuBank, removeSwap picks the list by it, thSwap swaps one list
    // (the name is not the original's)
    reslist<IThreadValue*> m_swap[3];
    // 0x280 the job groups (createGroupHandle, releaseGroupHandle) (the name is not the original's)
    mm::mtl::FixedList<GRPLIST, 128> m_group;
    int pad_1738;                      // 0x1738 the constructor sets 1; getWaitingJob, wakeup test it
    int pad_173c;                      // 0x173C the constructor sets 1
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
    fixed_size_alloc<TJOB> m_jobAlloc;  // 0x1768 the jobs allocJob hands out (the name is not the original's)
    unsigned long pad_1798;            // 0x1798 entryJobThread stores a job pointer here
    // 0x17A0 the job groups beginUpdate wakes (entryAutoExecGrp, removeAutoExecGrp) (the name is not the original's)
    mm::mtl::FixedList<AUTO_EXEC, 32> m_autoExec;
    unsigned int pad_1958;
    int pad_195c;  // 0x195C endFrame counts it up
    // 0x1960 a list of 8-byte values (element type not recovered)
    mm::mtl::FixedList<void*, 32> pad_1960;
    // 0x1BA0 the listeners told of the HOME menu (add/removeBackgroundListener, setBackground) and of the system
    // information (add/removeSystemInfoListener), under one lock (the names are not the original's)
    mm::mtl::FixedList<IWorkBackground*, 32> m_backgroundListener;
    mm::mtl::FixedList<IWorkInfomation*, 32> m_systemInfoListener;  // 0x1DE0
    unsigned long m_mainThreadId;      // 0x2020 getMainThreadId (the name is not the original's)
    int m_bankCount[2];                // 0x2028 beginFrame zeroes the current bank's (the name is not the original's)
    float m_renderTime;                // 0x2030 thRender's time of WorkRootState::renderWork (the name is not the original's)
    // 0x2034 to 0x203C times endFrame takes (DevClock::getTimeNow) from the frame's clocks
    float pad_2034;
    float pad_2038;
    float pad_203c;
    bool pad_2040;                     // 0x2040 updateMessage sets it and clears it once DevFileTh is not saving
    unsigned char pad_2041[0x7];
    long m_beginClock[8];              // 0x2048 getBeginClock returns [0] or [4] (the name is not the original's)
    int pad_2088;                      // 0x2088 createGroupHandle counts up
    unsigned char pad_208c[0x4];
    // a 64-bit count (endFrame adds 1 to all of it; 32-bit readers of getFrameCount take the low half)
    unsigned long m_frameCount;        // 0x2090 getFrameCount (the name is not the original's)
    long pad_2098;                     // 0x2098 the constructor stores std::chrono::system_clock::now()
    // 0x20A0 the error callbacks registErrorCB enters and unregistErrorCB removes, under m_errorCBLock (the names are
    // not the original's)
    mm::mtl::FixedList<IErrorCB*, 32> m_errorCB;
    CriticalSectionNC m_errorCBLock;   // 0x22E0
};
}  // namespace ml

#endif
