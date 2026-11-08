#ifndef GF_MSGFXSPLASHDOWN_H
#define GF_MSGFXSPLASHDOWN_H

#include "fw/Message.h"

namespace gf {

// message 0x1000059 (1.0.0's GfComEffectCaster::procMsgFxSplashdown(fw::MessageObject*, gf::MsgFxSplashdown&) names
// it): WaterInPlugin::onEvent sends it to the effect caster as the PC lands in water; the caster emits the splash
// (GfEffectGround::emitSplashdownEffect). The field name is not the original's.
class MsgFxSplashdown : public ::fw::Message {
public:
    explicit MsgFxSplashdown(bool big) : fw::Message(0x1000059, 0x80), m_big(big) {}

    bool m_big;  // the big splash (a big-splash fall into water deeper than the sound's water threshold)
};

}  // namespace gf

#endif
