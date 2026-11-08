#ifndef CLASSES_EVENT_CHARAWEIGHTITEM_H
#define CLASSES_EVENT_CHARAWEIGHTITEM_H

#include "classes/event/AnmF32.h"

namespace gf { class GfObj; enum AnimLayer : unsigned int; }

namespace event {
// table 0x7100B3FC08
class CharaWeightItem {
public:
    virtual ~CharaWeightItem();  // slot 0
    // 0x71000D3CC8: eases the named motion in on the layer (weight 0) and keeps the name and layer
    void create(gf::GfObj*, gf::AnimLayer, const char*, const char*);
    // 0x71000D3DDC: advances both curves and hands the combined weight and speed to the object's animation
    void update(gf::GfObj*, float);
    // bit 0: the motion was eased in (create), bit 1: still playing (update clears it once both curves end)
    unsigned int m_flags;  // 0x8
    gf::AnimLayer m_layer;  // 0xc: create's layer
    // the name CharaWeightPlayer's eases look the item up by (the field names here are not the original's)
    const char* m_name;  // 0x10
    // the curves the destructor tears down (last first), one per WeightLayer (easeOut indexes them)
    AnmF32 m_anm[2];  // 0x18
    float m_weight;  // 0x238: easeOut's start value
    // factors of the weight and the speed update hands on (create sets them to 1)
    float m_weightRate0;  // 0x23c
    float m_weightRate1;  // 0x240
    float m_speedRate0;  // 0x244
    float m_speedRate1;  // 0x248
};
}  // namespace event

#endif
