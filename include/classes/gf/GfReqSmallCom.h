#ifndef CLASSES_GF_GFREQSMALLCOM_H
#define CLASSES_GF_GFREQSMALLCOM_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfReqSmallCom; }

namespace gf {
// table 0x7100B6AF20
class GfReqSmallCom : public ::mm::mtl::PtrSingleton< ::gf::GfReqSmallCom> {
public:
    virtual ~GfReqSmallCom();  // slot 0
};
}  // namespace gf

#endif
