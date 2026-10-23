#ifndef NAVI_NVMSHACMAN_H
#define NAVI_NVMSHACMAN_H

#include "mtl/AllocHandle.h"

namespace navi { class NvmshAcObjBase; }
namespace navi { class NvmshResMan; }

namespace navi {

// the navigation mesh's access objects (no table; NvmshManager holds one at 0x58 and forwards to it)
class NvmshAcMan {
public:
    NvmshAcObjBase* createObj(mtl::ALLOC_HANDLE handle, NvmshResMan* resMan);
    void releaseObj(NvmshAcObjBase* object);
};

}  // namespace navi

#endif
