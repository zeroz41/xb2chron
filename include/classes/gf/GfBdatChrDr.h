// not proven yet: its table differs from the original's (word 5: _ZN2gf11GfBdatChrDr3vf0Ev where the original has =-8)
#ifndef CLASSES_GF_GFBDATCHRDR_H
#define CLASSES_GF_GFBDATCHRDR_H

namespace gf {
// a base of gf::GfBdatChrDr no evidence names yet
class TUnk_B468F8 {
public:
    virtual ~TUnk_B468F8();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatChrDr no evidence names yet
class TUnk_B46920 {
public:
    virtual ~TUnk_B46920();
    virtual void bdatRefresh() = 0;
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
};
// table 0x7100B468F8; base at 0x0 unknown (TUnk_B468F8), base at 0x8 unknown (TUnk_B46920)
class GfBdatChrDr : public TUnk_B468F8, public TUnk_B46920 {
public:
    virtual void vf0();  // slot 0
    virtual void vf1();  // slot 1
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
