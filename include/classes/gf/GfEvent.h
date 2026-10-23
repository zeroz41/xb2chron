#ifndef CLASSES_GF_GFEVENT_H
#define CLASSES_GF_GFEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfSetupParam; }
namespace gf { class GfEvent; }
namespace gf { class IGfEvent; }
namespace gf { enum EXEC_STATE : int; }

namespace gf {
// table 0x7100B591E8
class GfEvent : public ::mm::mtl::PtrSingleton< ::gf::GfEvent> {
public:
    // the event for a driver changing its engaged blade from one slot to another
    static void callBladeChange(GF_OBJ_HANDLE* handle, int from, int to);
    static void build(const GfSetupParam& param);
    static void destroy();
    virtual ~GfEvent();  // slot 0
    static void callCameraControl(int type);
    // listener joins (leaves) the ones GfEvent's calls reach
    static void addEventCallback(IGfEvent* listener);
    static void removeEventCallback(IGfEvent* listener);
    static void callExecState(EXEC_STATE state);  // each listener's gevExecState
    static void callLoadGameTime(float time);  // each listener's gevLoadGameTime
    static void callSwapFormation(unsigned int index0, unsigned int index1);  // each listener's gevSwapFormation
};
}  // namespace gf

#endif
