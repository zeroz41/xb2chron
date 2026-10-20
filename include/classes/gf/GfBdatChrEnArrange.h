// not proven yet: its table differs from the original's (word 5: _ZN2gf18GfBdatChrEnArrange3vf0Ev where the original has =-8)
#ifndef CLASSES_GF_GFBDATCHRENARRANGE_H
#define CLASSES_GF_GFBDATCHRENARRANGE_H

namespace gf {
// a base of gf::GfBdatChrEnArrange no evidence names yet
class TUnk_B469E8 {
public:
    virtual ~TUnk_B469E8();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatChrEnArrange no evidence names yet
class TUnk_B46A10 {
public:
    virtual ~TUnk_B46A10();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B469E8; base at 0x0 unknown (TUnk_B469E8), base at 0x8 unknown (TUnk_B46A10)
class GfBdatChrEnArrange : public TUnk_B469E8, public TUnk_B46A10 {
public:
    virtual void vf0();  // slot 0
    virtual ~GfBdatChrEnArrange();  // slot 1
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
