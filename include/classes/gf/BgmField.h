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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfFieldBgm::fn_7100262E58 calls
    // it on BgmField's instance. What it does: takes a BGM name (asserts `pszName != 0` as it copies it into a
    // FixStr); its only caller passes GfPlayComEvent's BGM name.
    void fn_7100262E70(const char* name);
};
}  // namespace gf

#endif
