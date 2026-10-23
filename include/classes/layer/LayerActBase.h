#ifndef CLASSES_LAYER_LAYERACTBASE_H
#define CLASSES_LAYER_LAYERACTBASE_H

#include "classes/layer/LayerObj.h"

namespace layer {
// one action's record (the layout is not the original's)
struct LyrActionInfo {
    unsigned char pad_0[0x8];
    unsigned int m_id;  // LayerAccAction::actionID looks for it
    unsigned char pad_C[0xC];
    float m_sec;  // LayerAccAction::getActionSec
    unsigned char pad_1C[0x10];
};
// an object's action data (only the action count is known; the layout is not the original's)
class LyrActionData {
public:
    unsigned char pad_0[0x8];
    const LyrActionInfo* m_actions;  // m_actionMax records
    int m_actionMax;  // LayerAccAction::getActionMax
};
}  // namespace layer

namespace layer {
// table none (its derived classes')
class LayerActBase : public ::layer::LayerObj {
public:
    virtual ~LayerActBase();  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*) {}  // slot 10
    void actionEnd();
    void actionIdx(unsigned int index);

    unsigned char pad_248[0x8];
    LyrActionData* m_actionData;  // its actions, or null (LayerAccAction::isActionData; the name is not the original's)
};
}  // namespace layer

#endif
