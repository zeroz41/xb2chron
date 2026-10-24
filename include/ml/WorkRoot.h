#ifndef ML_WORKROOT_H
#define ML_WORKROOT_H

#include "mtl/AllocHandle.h"

namespace ml {

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
};

}  // namespace ml

#endif
