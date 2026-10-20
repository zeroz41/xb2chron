#ifndef CLASSES_ML_ERRVIEWER_H
#define CLASSES_ML_ERRVIEWER_H

namespace ml {
// a base of ml::ErrViewer no evidence names yet
class TUnk_B77A30 {
public:
    virtual ~TUnk_B77A30();
    virtual void setup() = 0;
    virtual void term() = 0;
    virtual void upErrViewer() = 0;
    virtual void bkgHomeMenu(bool) = 0;
    virtual void bkgHomeMenuDenied() = 0;
};
// a base of ml::ErrViewer no evidence names yet
class TUnk_B77A78 {
public:
    virtual ~TUnk_B77A78();
    virtual void bkgHomeMenu(bool) = 0;
    virtual void bkgHomeMenuDenied() = 0;
};
// table 0x7100B77A30; base at 0x0 unknown (TUnk_B77A30), base at 0x8 unknown (TUnk_B77A78)
class ErrViewer : public TUnk_B77A30, public TUnk_B77A78 {
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
