#ifndef CLASSES_GF_BGMGIMMICK_H
#define CLASSES_GF_BGMGIMMICK_H

#include "classes/gf/BgmTrack.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B51338; its PtrSingleton at 0x630 (the destructors store PtrSingleton<BgmGimmick>'s table there)
class BgmGimmick : public ::gf::BgmTrack, public ::mm::mtl::PtrSingleton< ::gf::BgmGimmick> {
public:
    explicit BgmGimmick(GfFieldBgm* fieldBgm);
    virtual ~BgmGimmick();  // slot 0
    virtual const char* getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
