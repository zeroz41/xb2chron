#ifndef CLASSES_LAYER_LAYERACTDEF_H
#define CLASSES_LAYER_LAYERACTDEF_H

#include "classes/layer/LayerObjWork.h"

namespace layer { class LyrActionData; }

namespace layer {
// table none in 3.0.1 (its derived classes'). 1.0.0's LayerActDef() calls LayerObjWork's C2 constructor and its
// table (0x71011B7980) is LayerObjWork's but for slot 1 (its own destructor) and slot 10 (updatePartsAction).
class LayerActDef : public ::layer::LayerObjWork {
public:
    virtual ~LayerActDef();  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
    // the action commands s_pCallActCmd adds to LayerActBase's (each reads its command at cmd, steps cmd past it
    // and returns whether the action waits)
    bool actcmd_iconnum(const unsigned char*& cmd);
    bool actcmd_animicon(const unsigned char*& cmd);

    // The field names follow LayerAccDefObj's accessors (its objects of type 1; not the original's). They are
    // LayerActDef's: actcmd_iconnum and actcmd_animicon write m_iconNum (LayerObjMesh and LayerObjTopDef add none).
    unsigned char pad_258[0x48];
    float m_param;  // setParm
    unsigned short m_iconNum;  // setIconNum / getIconNum
    unsigned short m_iconMax;  // getIconMax
    unsigned short m_gauge;  // setGauge / getGauge (a LAYER_GAUGE)
};
}  // namespace layer

#endif
