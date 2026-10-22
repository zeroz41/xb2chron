#ifndef CLASSES_GF_GFGAMESCENE_H
#define CLASSES_GF_GFGAMESCENE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameScene; }

namespace gf {
// table 0x7100B55EF0
class GfGameScene : public ::mm::mtl::PtrSingleton< ::gf::GfGameScene> {
public:
    virtual ~GfGameScene();  // slot 0
    bool isEnableFieldBladeChange() const;
    void requestFieldBladeChange();
};
}  // namespace gf

#endif
