#ifndef CLASSES_GF_GFREQMANAGER_H
#define CLASSES_GF_GFREQMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfReqManager; }

namespace gf {
// table 0x7100B6A8A8
class GfReqManager : public ::mm::mtl::PtrSingleton< ::gf::GfReqManager> {
public:
    virtual ~GfReqManager();  // slot 0
};
}  // namespace gf

#endif
