#ifndef CLASSES_GF_GFMENUMNAGERPADREAD_H
#define CLASSES_GF_GFMENUMNAGERPADREAD_H

namespace gf {
// table 0x7100B5ED18
class GfMenuMnagerPadRead {
public:
    virtual ~GfMenuMnagerPadRead();  // slot 0
    virtual void uiGetControlPad() const;  // slot 2
};
}  // namespace gf

#endif
