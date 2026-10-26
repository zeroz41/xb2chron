#ifndef ML_WORKROOT_H
#define ML_WORKROOT_H

#include "mtl/AllocHandle.h"

namespace ml {

// what the program hands WorkRoot::run: whether the product memory is in use and the memory blocks
// WorkRootMem::initialize allocates and creates its allocators on (the member names are not the original's)
struct WorkRootParam {
    bool m_isProductMem;            // 0x00 isProductMem
    void* m_productMem;             // 0x08 malloc'ed for the product and extra sizes together
    unsigned long m_productSize;    // 0x10
    void* m_extraMem;               // 0x18 the product block's end, when there is an extra size
    unsigned long m_extraSize;      // 0x20
    void* m_graphicMem;             // 0x28 malloc'ed when there is a graphic size
    unsigned long m_graphicSize;    // 0x30
    int m_option;                   // 0x38 run copies it
};

// monolib's work root accessors (libs/monolib_mm/source/work/work_cpu.cpp defines them)
class WorkRoot {
public:
    // the temporary memory's handle (it returns ml::WorkRootMem::getMemTMP()'s; fw::FrameworkMemory::getMem's kind 3)
    static mtl::ALLOC_HANDLE getMemTMP();
    static void setThreadRender(bool threadRender);
    // the screen's size: 1280 x 720
    static int getWidth();
    static int getHeight();
    static bool isWinDestroy();
    static bool isErrorStop();
    static bool isErrorLog();
    static void setInfiniteLoop(bool infiniteLoop);
    static void setErrorRestart(bool errorRestart);
    static void setErrorLogSD(bool errorLogSD);
    static void setBlueScreen(bool blueScreen);
    static bool isRestart();
    // copies param, then runs the work root until it ends (always true; the parameter name is not the original's)
    static bool run(const WorkRootParam* param);
    // the copy of the parameter run keeps (WorkRootMem fills in the blocks it allocates)
    static WorkRootParam* getParam();
    static bool isProductMem();
};

}  // namespace ml

#endif
