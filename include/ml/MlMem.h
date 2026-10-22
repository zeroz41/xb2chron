#ifndef ML_MLMEM_H
#define ML_MLMEM_H

#include "mtl/AllocHandle.h"

namespace ml {

// monolib's memory handles (ml/LibMain.cpp defines them; fw::FrameworkMemory::getMem hands kinds 1 and 2 out)
class MlMem {
public:
    static void setProductMem(mtl::ALLOC_HANDLE handle);
    static mtl::ALLOC_HANDLE getProductMem();
    static void setDebugMem(mtl::ALLOC_HANDLE handle);
    static mtl::ALLOC_HANDLE getDebugMem();
    static void setGraphicMem(mtl::ALLOC_HANDLE handle);
    static mtl::ALLOC_HANDLE getGraphicMem();
};

}  // namespace ml

#endif
