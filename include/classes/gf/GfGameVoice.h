#ifndef CLASSES_GF_GFGAMEVOICE_H
#define CLASSES_GF_GFGAMEVOICE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameVoice; }

namespace gf {
// table 0x7100B56B40
class GfGameVoice : public ::mm::mtl::PtrSingleton< ::gf::GfGameVoice> {
public:
    virtual ~GfGameVoice();  // slot 0
    static void gevLayerPause(unsigned int, bool);
    bool isPlayEnemyVoice() const;
};
}  // namespace gf

#endif
