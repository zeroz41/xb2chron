#ifndef ML_WORKUTIL_H
#define ML_WORKUTIL_H

#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"
#include "ml/WorkRootState.h"

namespace ml {
// the work objects' helpers (work_cpu.cpp)
class WorkUtil {
public:
    // the allocator work objects are made from
    static mtl::ALLOC_HANDLE getWorkMem();
    static void setDispLogH(bool dispLogH);
    // makes a work of type T under parent and enters it (instances: tl::TitleApp)
    template <typename T>
    static T* createWork(const char* name, WorkObj* parent, bool flag) {
        T* work = new (getWorkMem(), nullptr, 0, 4, false) T(name, parent);
        WorkRootState::entryWork(work, parent, flag);
        return work;
    }
};
}  // namespace ml

#endif
