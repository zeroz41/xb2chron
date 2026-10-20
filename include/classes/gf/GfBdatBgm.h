#ifndef CLASSES_GF_GFBDATBGM_H
#define CLASSES_GF_GFBDATBGM_H

namespace gf {
// a base of gf::GfBdatBgm no evidence names yet
class TUnk_B45F90 {
public:
    virtual ~TUnk_B45F90();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatBgm no evidence names yet
class TUnk_B45FB8 {
public:
    virtual ~TUnk_B45FB8();
    virtual void bdatRefresh() = 0;
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
};
// table 0x7100B45F90; base at 0x0 unknown (TUnk_B45F90), base at 0x8 unknown (TUnk_B45FB8)
class GfBdatBgm : public TUnk_B45F90, public TUnk_B45FB8 {
public:
    virtual ~GfBdatBgm();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
