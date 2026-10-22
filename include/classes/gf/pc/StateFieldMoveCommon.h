#ifndef CLASSES_GF_PC_STATEFIELDMOVECOMMON_H
#define CLASSES_GF_PC_STATEFIELDMOVECOMMON_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }

namespace gf { namespace pc {
// table 0x7100B685D8
class StateFieldMoveCommon : public ::gf::GfStateBase {
public:
    virtual ~StateFieldMoveCommon();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}}  // namespace gf::pc

#endif
