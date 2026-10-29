#ifndef CLASSES_GF_BGMBATTLE_H
#define CLASSES_GF_BGMBATTLE_H

#include "classes/gf/BgmTrack.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B511D8; its PtrSingleton at 0x630 (the destructors store PtrSingleton<BgmBattle>'s table there)
class BgmBattle : public ::gf::BgmTrack, public ::mm::mtl::PtrSingleton< ::gf::BgmBattle> {
public:
    explicit BgmBattle(GfFieldBgm* fieldBgm);
    virtual ~BgmBattle();  // slot 0
    virtual const char* getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
