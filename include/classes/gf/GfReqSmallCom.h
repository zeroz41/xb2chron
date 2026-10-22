#ifndef CLASSES_GF_GFREQSMALLCOM_H
#define CLASSES_GF_GFREQSMALLCOM_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfReqSmallCom; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AF20; GfReqManager makes one (0x1B078 bytes, 3.0.1's new) and updates it after its own commands
class GfReqSmallCom : public ::mm::mtl::PtrSingleton< ::gf::GfReqSmallCom> {
public:
    GfReqSmallCom();
    virtual ~GfReqSmallCom();  // slot 0
    void update(const fw::UpdateInfo& info);
    static bool isExistCommand();

    unsigned char pad_8[0x1B070];
};
}  // namespace gf

#endif
