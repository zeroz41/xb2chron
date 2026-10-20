#ifndef CLASSES_ML_ERRVIEWER_H
#define CLASSES_ML_ERRVIEWER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class ErrViewer; }

namespace ml {
// a base of ml::ErrViewer no evidence names yet
class TUnk_B77A78 {
public:
    virtual ~TUnk_B77A78();
    virtual void bkgHomeMenu(bool) = 0;
    virtual void bkgHomeMenuDenied() = 0;
};
// table 0x7100B77A30; base at 0x8 unknown (TUnk_B77A78)
class ErrViewer : public ::mm::mtl::PtrSingleton< ::ml::ErrViewer>, public TUnk_B77A78 {
public:
    virtual ~ErrViewer();  // slot 0
    virtual void setup();  // slot 2
    virtual void term();  // slot 3
    virtual void upErrViewer();  // slot 4
    virtual void bkgHomeMenu(bool);  // slot 5
    virtual void bkgHomeMenuDenied();  // slot 6
};
}  // namespace ml

#endif
