#ifndef CLASSES_GF_GFBDATRSC_H
#define CLASSES_GF_GFBDATRSC_H

namespace gf {
// a base of gf::GfBdatRsc no evidence names yet
class TUnk_B47288 {
public:
    virtual ~TUnk_B47288();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatRsc no evidence names yet
class TUnk_B472B0 {
public:
    virtual ~TUnk_B472B0();
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
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
};
// table 0x7100B47288; base at 0x0 unknown (TUnk_B47288), base at 0x8 unknown (TUnk_B472B0)
class GfBdatRsc : public TUnk_B47288, public TUnk_B472B0 {
public:
    virtual ~GfBdatRsc();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
