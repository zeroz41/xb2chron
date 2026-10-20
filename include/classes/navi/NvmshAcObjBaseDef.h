#ifndef CLASSES_NAVI_NVMSHACOBJBASEDEF_H
#define CLASSES_NAVI_NVMSHACOBJBASEDEF_H

#include "classes/navi/NvmshAcObjBase.h"

namespace navi { class NvmshResMan; }

namespace navi {
// table 0x7100B7F6C0
class NvmshAcObjBaseDef : public ::navi::NvmshAcObjBase {
public:
    virtual ~NvmshAcObjBaseDef();  // slot 0
    virtual void release();  // slot 14
    virtual void update(bool&, navi::NvmshResMan*, bool);  // slot 15
};
}  // namespace navi

#endif
