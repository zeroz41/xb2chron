#ifndef CLASSES_GF_GFEVENT_H
#define CLASSES_GF_GFEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfEvent; }
namespace gf { class IGfEvent; }

namespace gf {
// table 0x7100B591E8
class GfEvent : public ::mm::mtl::PtrSingleton< ::gf::GfEvent> {
public:
    virtual ~GfEvent();  // slot 0
    static void callCameraControl(int type);
    // listener joins (leaves) the ones GfEvent's calls reach
    static void addEventCallback(IGfEvent* listener);
    static void removeEventCallback(IGfEvent* listener);
    static void callSwapFormation(unsigned int index0, unsigned int index1);  // each listener's gevSwapFormation
};
}  // namespace gf

#endif
