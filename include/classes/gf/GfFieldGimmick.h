#ifndef CLASSES_GF_GFFIELDGIMMICK_H
#define CLASSES_GF_GFFIELDGIMMICK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf {
// static helpers of gf_field_gimmick.cpp (only the ones gf_field_locator calls are declared)
// a PtrSingleton: GfPlayComEventFade reaches it through PtrSingleton<GfFieldGimmick>::sys()
class GfFieldGimmick : public ::mm::mtl::PtrSingleton< ::gf::GfFieldGimmick> {
public:
    // the FLD_maplist id of the map an RSC_GmkSetList row belongs to
    static int getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSetId);
    unsigned char pad_8[0xF4A4];
    // an event fade is running: GfPlayComEventFade's update sets it as it starts the fade, its end() clears it
    // (the name is not the original's)
    bool m_eventFade;
};
}  // namespace gf

#endif
