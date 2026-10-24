#ifndef CLASSES_GF_BGMBATTLEBOSS_H
#define CLASSES_GF_BGMBATTLEBOSS_H

#include "classes/gf/BgmTrack.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B51230; its PtrSingleton at 0x630 (the destructors store PtrSingleton<BgmBattleBoss>'s table there)
class BgmBattleBoss : public ::gf::BgmTrack, public ::mm::mtl::PtrSingleton< ::gf::BgmBattleBoss> {
public:
    virtual ~BgmBattleBoss();  // slot 0
    virtual const char* getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
