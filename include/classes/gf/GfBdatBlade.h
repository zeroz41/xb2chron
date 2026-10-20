// not proven yet: its table differs from the original's (word 11: _ZN2gf11TUnk_B4625023getBladeModelListParts2ERK12CBdatWrapperj where the original has _ZN2gf6_gfbdb23getBladeModelListParts2ERK12CBdatWrapperj)
#ifndef CLASSES_GF_GFBDATBLADE_H
#define CLASSES_GF_GFBDATBLADE_H

class CBdatWrapper;

namespace gf {
// a base of gf::GfBdatBlade no evidence names yet
class TUnk_B46228 {
public:
    virtual ~TUnk_B46228();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatBlade no evidence names yet
class TUnk_B46250 {
public:
    virtual ~TUnk_B46250();
    virtual void bdatRefresh() = 0;
    virtual void vf3();
    virtual void getBladeModelListParts2(CBdatWrapper const&, unsigned int);
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void getCmnBl_CapacitySkillNum1Prob(CBdatWrapper const&, unsigned int);
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
};
// table 0x7100B46228; base at 0x0 unknown (TUnk_B46228), base at 0x8 unknown (TUnk_B46250)
class GfBdatBlade : public TUnk_B46228, public TUnk_B46250 {
public:
    virtual ~GfBdatBlade();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
