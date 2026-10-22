#ifndef CLASSES_GF_PC_STATEFIELDWALLAIADSORPTION_H
#define CLASSES_GF_PC_STATEFIELDWALLAIADSORPTION_H

#include "classes/gf/GfStateBase.h"
#include <new>
#include "gf/pc/WallAiContextField.h"

namespace fw { class UpdateInfo; }

namespace ai { class State; }

namespace gf { namespace pc {
// table 0x7100B67D78
class StateFieldWallAiAdsorption : public ::gf::GfStateBase {
public:
    // what TaskFieldWallPrepare registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWallAiAdsorption(); }
    virtual ~StateFieldWallAiAdsorption() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions (out of line, in the wall states' unit); the slots above hand them the owner
    void enter(WallAiContextField* context, ai::State* prev);
    void leave(WallAiContextField* context, ai::State* next);
    void update(WallAiContextField* context, const fw::UpdateInfo& info);
};
}}  // namespace gf::pc

#endif
