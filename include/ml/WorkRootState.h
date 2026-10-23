#ifndef ML_WORKROOTSTATE_H
#define ML_WORKROOTSTATE_H

#include "mtl/AllocHandle.h"

namespace ml { class WorkObj; }

namespace ml {
// the root of the work objects (libs/monolib_mm/source/WorkRoot.cpp)
class WorkRootState {
public:
    static void initialize();
    // the works entered since the last call put under their parents
    static void entryWork();
    static void finalize();
    // the work of id wid, null when it is gone (the parameter names are not the original's)
    static WorkObj* getWork(unsigned int wid);
    // an id for work: its slot, and the count of ids handed out in the bits from 20
    static unsigned int allocWID(WorkObj* work);
    static void freeWID(unsigned int wid);
    static mtl::ALLOC_HANDLE getWorkMem();
    // work named name, or of id wid, in work's tree
    static WorkObj* getWork(WorkObj* work, const char* name);
    static WorkObj* getWork(WorkObj* work, unsigned int wid);
    static void setThreadRender(bool threadRender);
    static bool isThreadRender();
    // work entered under parent (the parameter names are not the original's)
    static void entryWork(WorkObj* work, WorkObj* parent, bool flag);
    static bool isEntryWork(unsigned int wid, const WorkObj* parent);
    static bool requestParent(WorkObj* work, WorkObj* parent);
    static void standbyWork(WorkObj* work);
    static void updateWork(WorkObj* work);
    static void tailWork(WorkObj* work);
    static void renderWork();
    static bool runSingle();
};
}  // namespace ml

#endif
