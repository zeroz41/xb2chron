#ifndef CLASSES_GF_GFMENUMNAGERPADREAD_H
#define CLASSES_GF_GFMENUMNAGERPADREAD_H

#include "classes/ui/UIPadRead.h"

namespace gf {
// table 0x7100B5ED18: the slot 0 destructor is ui::UIPadRead's (the class's own is trivial)
class GfMenuMnagerPadRead : public ::ui::UIPadRead {
public:
    virtual const fw::PadData& uiGetControlPad() const;  // slot 2: GfGamePad::getPadPlayer()
};
}  // namespace gf

#endif
