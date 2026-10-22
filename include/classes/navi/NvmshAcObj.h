#ifndef CLASSES_NAVI_NVMSHACOBJ_H
#define CLASSES_NAVI_NVMSHACOBJ_H

#include "classes/navi/NvmshAcObjBase.h"

namespace navi {
// no table or function of its own: what the managers hand out and take back (NvmshManager::releaseObj
// passes it on as its NvmshAcObjBase, at the same address); its users call NvmshAcObjBase's virtuals
class NvmshAcObj : public ::navi::NvmshAcObjBase {};
}  // namespace navi

#endif
