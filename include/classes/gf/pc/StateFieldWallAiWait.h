#ifndef CLASSES_GF_PC_STATEFIELDWALLAIWAIT_H
#define CLASSES_GF_PC_STATEFIELDWALLAIWAIT_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }

namespace gf { namespace pc {
// table 0x7100B67CD8
class StateFieldWallAiWait : public ::gf::GfStateBase {
public:
    virtual ~StateFieldWallAiWait();  // slot 0
    virtual void getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}}  // namespace gf::pc

#endif
