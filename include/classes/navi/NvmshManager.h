#ifndef CLASSES_NAVI_NVMSHMANAGER_H
#define CLASSES_NAVI_NVMSHMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace navi {
// a base of navi::NvmshManager no evidence names yet
class TUnk_B7F630 {
public:
    virtual ~TUnk_B7F630();
};
// table 0x7100B7F630; base at 0x0 unknown (TUnk_B7F630)
class NvmshManager : public TUnk_B7F630, public ::ml::IWorkEvent {
public:
    virtual ~NvmshManager();  // slot 0
};
}  // namespace navi

#endif
