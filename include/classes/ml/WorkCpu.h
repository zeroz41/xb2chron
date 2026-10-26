#ifndef CLASSES_ML_WORKCPU_H
#define CLASSES_ML_WORKCPU_H

#include "classes/ml/WorkObj.h"
#include "mtl/AllocHandle.h"
#include "classes/mm/mtl/PtrSingleton.h"
namespace ml {
enum CPUID : int;
// how WorkCpu::sync waits (enumerators not recovered: DrCalcTexStreamMan::jobWait passes 0)
enum WKCPU_SYNC : int;
class IWorkInfomation; class IWorkBackground; class IThreadValue; }

namespace ml {
// table 0x7100B78E08; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkCpu>'s table)
class WorkCpu : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkCpu> {
public:
    virtual ~WorkCpu();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // its object made and every CPU thread logged in
    static bool isInitialized();
    // starts a job group's threads (DrCalcTexStreamMan::entryJob) and waits for them (DrCalcTexStreamMan::jobWait)
    static void wakeup(int group);
    static void sync(int group, WKCPU_SYNC sync, CPUID cpu);
    static const unsigned int& getFrameCount();  // the work CPU's frame counter (fw::Framework::getFrameCount)
    // a listener told of the HOME menu no more (fw::MovieManager's destructor)
    static void addBackgroundListener(IWorkBackground* listener);
    static void removeBackgroundListener(IWorkBackground* listener);
    // a listener of system information (operation and performance mode) no more (ml::DevPerfNx's destructor)
    static void removeSystemInfoListener(IWorkInfomation* listener);
    // a value swapped every frame no more (threadval's destructor)
    static void removeSwap(IThreadValue* value);
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

    static bool s_bRenderSubCpu;

    struct {
        unsigned char pad_bit0 : 1;
        unsigned char m_shutdown : 1;  // isShutdown (the name is not the original's)
    } m_state;                         // 0x1B0 (the name is not the original's)
    unsigned char pad_1b1[0x7];
    mtl::ALLOC_HANDLE m_memStack;      // 0x1B8 getMemStack (the name is not the original's)
    unsigned char pad_1bc[0x15A8];
    int m_bank;                        // 0x1764 getEven (the name is not the original's)
};
}  // namespace ml

#endif
