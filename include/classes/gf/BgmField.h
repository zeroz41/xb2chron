#ifndef CLASSES_GF_BGMFIELD_H
#define CLASSES_GF_BGMFIELD_H

#include "classes/gf/BgmTrack.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B512E0; its PtrSingleton at 0x630 (the destructors store PtrSingleton<BgmField>'s table there)
class BgmField : public ::gf::BgmTrack, public ::mm::mtl::PtrSingleton< ::gf::BgmField> {
public:
    virtual ~BgmField();  // slot 0
    virtual const char* getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
