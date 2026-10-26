#ifndef EFFECT_SENDPARAM_H
#define EFFECT_SENDPARAM_H

#include "mm/Mat44.h"

namespace effect {

// what an effect is created or updated with (fw::EffectManager::create and setParam hand one to the
// SystemManager; es_set_param_pos_only copies its first 0x58 bytes and the fields up to 0xA9). The names are
// not the original's.
class SendParam {
public:
    mm::Mat44 m_mtx;  // where the effect sits (GfEffectGround::calcSwimEffectParam sets its height)
    unsigned char pad_40[0x70];
};

}  // namespace effect

#endif
